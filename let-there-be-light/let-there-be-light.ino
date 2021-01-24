#include <LinkedList.h>

const int WORD_LENGTH = 4;
const int LETTER_HEIGHT = 8;
const int LETTER_WIDTH = 8;
const int VIEW_SIZE = 16;
const int BUFFER_LENGTH = VIEW_SIZE * 8;

float roundTripTime = .05; //// Time (Hz) for 1 cycle. 1 complete buffer push

  
class Letter{
  public:
    boolean *line0;
    boolean *line1;
    boolean *line2;
    boolean *line3;
    boolean *line4;
    boolean *line5;
    boolean *line6;
    boolean *line7;


    boolean* getLine (int line){
      if (line == 0){
          return line0;
      }else if (line == 1){
        return line1;
      }else if (line == 2){
        return line2;
      }else if (line == 3){
        return line3;
      }else if (line == 4){
        return line4;
      }else if (line == 5){
        return line5;
      }else if (line == 6){
        return line6;
      }else if (line == 7){
        return line7;
      }

    }
};


struct LetterA {
  boolean line0[8] = {0,1,1,1,0,0,0,0};
  boolean line1[8] = {1,0,0,0,1,0,0,0};
  boolean line2[8] = {1,0,0,0,1,0,0,0};
  boolean line3[8] = {1,1,1,1,1,0,0,0};
  boolean line4[8] = {1,0,0,0,1,0,0,0};
  boolean line5[8] = {1,0,0,0,1,0,0,0};
  boolean line6[8] = {1,0,0,0,1,0,0,0};
  boolean line7[8] = {0,0,0,0,0,0,0,0};

} letterA;

   
   struct LetterB {
  boolean line0[8] = {1,1,1,1,0,0,0,0};
  boolean line1[8] = {1,0,0,0,1,0,0,0};
  boolean line2[8] = {1,0,0,0,1,0,0,0};
  boolean line3[8] = {1,1,1,1,0,0,0,0};
  boolean line4[8] = {1,0,0,0,1,0,0,0};
  boolean line5[8] = {1,0,0,0,1,0,0,0};
  boolean line6[8] = {1,1,1,1,0,0,0,0};
  boolean line7[8] = {0,0,0,0,0,0,0,0};

} letterB;

struct LetterC {
  boolean line0[8] = {0,1,1,1,0,0,0,0};
  boolean line1[8] = {1,0,0,0,1,0,0,0};
  boolean line2[8] = {1,0,0,0,0,0,0,0};
  boolean line3[8] = {1,0,0,0,0,0,0,0};
  boolean line4[8] = {1,0,0,0,0,0,0,0};
  boolean line5[8] = {1,0,0,0,1,0,0,0};
  boolean line6[8] = {0,1,1,1,0,0,0,0};
  boolean line7[8] = {0,0,0,0,0,0,0,0};

} letterC;


struct LetterO {
  boolean line0[8] = {0,1,1,1,0,0,0,0};
  boolean line1[8] = {1,0,0,0,1,0,0,0};
  boolean line2[8] = {1,0,0,0,1,0,0,0};
  boolean line3[8] = {1,0,0,0,1,0,0,0};
  boolean line4[8] = {1,0,0,0,1,0,0,0};
  boolean line5[8] = {1,0,0,0,1,0,0,0};
  boolean line6[8] = {0,1,1,1,0,0,0,0};
  boolean line7[8] = {0,0,0,0,0,0,0,0};
} letterO;

struct LetterBlank {
  boolean line0[8] = {0,0,0,0,0,0,0,0};
  boolean line1[8] = {0,0,0,0,0,0,0,0};
  boolean line2[8] = {0,0,0,0,0,0,0,0};
  boolean line3[8] = {0,0,0,0,0,0,0,0};
  boolean line4[8] = {0,0,0,0,0,0,0,0};
  boolean line5[8] = {0,0,0,0,0,0,0,0};
  boolean line6[8] = {0,0,0,0,0,0,0,0};
  boolean line7[8] = {0,0,0,0,0,0,0,0};
} letterBlank;

   
   struct LetterFull{
    boolean line0[8] = {1,1,1,1,1,1,1,1};
    boolean line1[8] = {1,1,1,1,1,1,1,1};
    boolean line2[8] = {1,1,1,1,1,1,1,1};
    boolean line3[8] = {1,1,1,1,1,1,1,1};
    boolean line4[8] = {1,1,1,1,1,1,1,1};
    boolean line5[8] = {1,1,1,1,1,1,1,1};
    boolean line6[8] = {1,1,1,1,1,1,1,1};
    boolean line7[8] = {1,1,1,1,1,1,1,1};
} letterFull;


class LedWord {

    public:
                LinkedList<Letter> *letters;
               

        boolean* nextLine();
                void setWord(char *word, int length);
                void setLetter (int letterIndex, char letter);

    private:
        int currentIndex = 0;
        int currentLetter = 0;
                boolean ret[LETTER_HEIGHT];

};

void LedWord::setLetter (int letterIndex, char letter){

  Letter newLetter;
  
  if (letter == 'a' || letter == 'A'){
  
    newLetter.line0 = letterA.line0;
    newLetter.line1 = letterA.line1;
    newLetter.line2 = letterA.line2;
    newLetter.line3 = letterA.line3;
    newLetter.line4 = letterA.line4;
    newLetter.line5 = letterA.line5;
    newLetter.line6 = letterA.line6;
    newLetter.line7 = letterA.line7;
    
      letters->set(letterIndex, newLetter);

  }else if (letter == 'b' || letter == 'B'){
    newLetter.line0 = letterB.line0;
    newLetter.line1 = letterB.line1;
    newLetter.line2 = letterB.line2;
    newLetter.line3 = letterB.line3;
    newLetter.line4 = letterB.line4;
    newLetter.line5 = letterB.line5;
    newLetter.line6 = letterB.line6;
    newLetter.line7 = letterB.line7;
    
      letters->set(letterIndex, newLetter);
      
    }else if (letter == 'c' || letter == 'C'){
    newLetter.line0 = letterC.line0;
    newLetter.line1 = letterC.line1;
    newLetter.line2 = letterC.line2;
    newLetter.line3 = letterC.line3;
    newLetter.line4 = letterC.line4;
    newLetter.line5 = letterC.line5;
    newLetter.line6 = letterC.line6;
    newLetter.line7 = letterC.line7;
    
      letters->set(letterIndex, newLetter);

  }else if (letter == 'o' || letter == 'O'){
 newLetter.line0 = letterO.line0;
    newLetter.line1 = letterO.line1;
    newLetter.line2 = letterO.line2;
    newLetter.line3 = letterO.line3;
    newLetter.line4 = letterO.line4;
    newLetter.line5 = letterO.line5;
    newLetter.line6 = letterO.line6;
    newLetter.line7 = letterO.line7;
    
      letters->set(letterIndex, newLetter);

  }else if (letter == '$' || letter == '$'){
    newLetter.line0 = letterFull.line0;
    newLetter.line1 = letterFull.line1;
    newLetter.line2 = letterFull.line2;
    newLetter.line3 = letterFull.line3;
    newLetter.line4 = letterFull.line4;
    newLetter.line5 = letterFull.line5;
    newLetter.line6 = letterFull.line6;
    newLetter.line7 = letterFull.line7;
    
      letters->set(letterIndex, newLetter);
    }else{
         newLetter.line0 = letterBlank.line0;
    newLetter.line1 = letterBlank.line1;
    newLetter.line2 = letterBlank.line2;
    newLetter.line3 = letterBlank.line3;
    newLetter.line4 = letterBlank.line4;
    newLetter.line5 = letterBlank.line5;
    newLetter.line6 = letterBlank.line6;
    newLetter.line7 = letterBlank.line7;
    
      letters->set(letterIndex, newLetter);
  }
}

void LedWord::setWord (char *word, int length){
  int i;

  for (i =0; i < length; i++){
    setLetter(i, word[i]);
  }

  //for the future when there is more than 2 letters, blank out the remaining letters in the lettersBuffer
  for (;i < WORD_LENGTH; i++){
    setLetter(i,' ');
  }

}

boolean* LedWord::nextLine (){

  Letter theLetter = letters->get(currentLetter);
  
  ret[0] = theLetter.line0[currentIndex];
  ret[1] = theLetter.line1[currentIndex];
  ret[2] = theLetter.line2[currentIndex];
  ret[3] = theLetter.line3[currentIndex];
  ret[4] = theLetter.line4[currentIndex];
  ret[5] = theLetter.line5[currentIndex];
  ret[6] = theLetter.line6[currentIndex];
  ret[7] = theLetter.line7[currentIndex];

  currentIndex++;

  if (currentIndex >= LETTER_HEIGHT){
    currentIndex = 0;

    currentLetter++;
    if (currentLetter >= WORD_LENGTH){
      currentLetter = 0;
    }
  }
  return ret;
}


/////////////////////////////////
//
//
//
/////////////////////////////////
LedWord ledWord;
boolean toggle = true;

void configureTimer (){
    cli();
    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    // Divide by the size of buffer length to get calls each time step
    //OCR1A = 15624/BUFFER_LENGTH
    // = (16*10^6) / (1*1024) - 1 (must be <65536)

    OCR1A = (16000000 / ((roundTripTime) * 1024)-1)/BUFFER_LENGTH;

    
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei();

}

ISR(TIMER1_COMPA_vect){

  digitalWrite (13, toggle);
  toggle = !(toggle);

  boolean* values = ledWord.nextLine();

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
    pinMode (13,OUTPUT);

    //The actual output pin that will reflect what our array is
    pinMode (12, OUTPUT);
    pinMode (11, OUTPUT);
    pinMode (10, OUTPUT);
    pinMode (9, OUTPUT);
    pinMode (8, OUTPUT);
    pinMode (7, OUTPUT);
    pinMode (6, OUTPUT);
    pinMode (5, OUTPUT);

        ledWord.setWord("A$CAOA",6);


}

void loop()
{

}
