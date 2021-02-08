#include "LedWord.h"
#include <LiquidCrystal.h>
#include <ShiftRegister74HC595.h>

ShiftRegister74HC595<1> sr (8, 10, 9);
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;


LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


const int VIEW_SIZE = 16;
const int BUFFER_LENGTH = VIEW_SIZE * 8;

float roundTripTime = .01; //// Time (Hz) for 1 cycle. 1 complete buffer push

LedWord ledWord;
boolean toggle = true;
byte values;
String toDisplay;

void configureTimer () {
  cli();
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  // Divide by the size of buffer length to get calls each time step
  //OCR1A = 15624/BUFFER_LENGTH
  // = (16*10^6) / (1*1024) - 1 (must be <65536)

  OCR1A = (16000000 / ((roundTripTime) * 1024) - 1) / BUFFER_LENGTH;


  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();

}

ISR(TIMER1_COMPA_vect) {

  digitalWrite (13, toggle);
  toggle = !(toggle);

  values = ledWord.nextCol();

  for (int i = 0; i < 8; i++) {
    sr.set(7 - i, bitRead(values, i) == 0 ? LOW : HIGH);
  }


}

void setup()
{
  lcd.begin(16, 2);

  configureTimer();
  Serial.begin(9600);

  // "clock" led so we can see each pulse of the time step
  pinMode (13, OUTPUT);



}

void loop()
{


  if (Serial.available()) {

    String c = Serial.readString();
    toDisplay = c;
    char bufferA[c.length()];
    c.toCharArray(bufferA, c.length());
    lcd.clear();


    ledWord.setWord(bufferA);

  }

  lcd.setCursor(0, 0);
  lcd.print(toDisplay.length());


}
