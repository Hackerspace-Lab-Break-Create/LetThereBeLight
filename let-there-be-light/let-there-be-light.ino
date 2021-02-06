#include "LedWord.h"
#include <LiquidCrystal.h>
#include <ShiftRegister74HC595.h>

ShiftRegister74HC595<1> sr (8, 10, 9);
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;


LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int wordLength = 5;
int letterHeigth = 8;
int letterWidth = 8;
int viewSize = 16;
int bufferLength = viewSize * 8;
String toDisplay;

float roundTripTime = 0.01; //// Time (Hz) for 1 cycle. 1 complete buffer push

//byte letterBuffer[WORD_LENGTH];
LedWord ledWord = LedWord (wordLength, letterHeigth, letterWidth);
boolean toggle = true;
boolean* values;

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

  OCR1A = (16000000 / ((roundTripTime) * 1024) - 1) / bufferLength;


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

  values = ledWord.nextLine();

  //
  //  digitalWrite (14, values[0]);
  //  digitalWrite (15, values[1]);
  //  digitalWrite (16, values[2]);
  //  digitalWrite (17, values[3]);
  //  digitalWrite (18, values[4]);
  //  digitalWrite (19, values[5]);
  //  digitalWrite (7, values[6]);
  //  digitalWrite (8, values[7]);
  for(int i = 0; i < 7; i++){
  sr.set(7 - i, values[i] == 0 ? LOW : HIGH);
  }
 

}



void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Hello Tofu");



  configureTimer();


  // "clock" led so we can see each pulse of the time step
  pinMode (13, OUTPUT);

  //The actual output pin that will reflect what our array is
  pinMode (14, OUTPUT);
  pinMode (15, OUTPUT);
  pinMode (16, OUTPUT);
  pinMode (17, OUTPUT);
  pinMode (18, OUTPUT);
  pinMode (19, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);

}

void loop()
{

  if (Serial.available()) {

    String c = Serial.readString();

    toDisplay = c;
    lcd.clear();


    ledWord.setWord(toDisplay, toDisplay.length());

  }

  lcd.setCursor(0, 0);
  lcd.print(toDisplay);


}
