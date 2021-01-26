#include "LedWord.h"

const int WORD_LENGTH = 4;
const int LETTER_HEIGHT = 8;
const int LETTER_WIDTH = 8;
const int VIEW_SIZE = 16;
const int BUFFER_LENGTH = VIEW_SIZE * 8;

float roundTripTime = .01; //// Time (Hz) for 1 cycle. 1 complete buffer push

//byte letterBuffer[WORD_LENGTH];
LedWord ledWord = LedWord (WORD_LENGTH, LETTER_HEIGHT, LETTER_WIDTH);
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

  values = ledWord.nextLine();


  digitalWrite (12, values[0]);
  digitalWrite (11, values[1]);
  digitalWrite (10, values[2]);
  digitalWrite (9, values[3]);
  digitalWrite (8, values[4]);
  digitalWrite (7, values[5]);
  digitalWrite (6, values[6]);
  digitalWrite (5, values[7]);
 
}

void setup()
{
  configureTimer();
  Serial.begin(9600);

  // "clock" led so we can see each pulse of the time step
  pinMode (13, OUTPUT);

  //The actual output pin that will reflect what our array is
  pinMode (12, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (9, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (5, OUTPUT);

  char toDisplay[] = "ZACD";
  ledWord.setWord(toDisplay, 4);


}

void loop()
{

}
