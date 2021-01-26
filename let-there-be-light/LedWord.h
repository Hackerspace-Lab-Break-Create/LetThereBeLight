#ifndef _LED_WORD_
#define _LED_WORD_

#include "PovAlphabet8x8.h"

class LedWord {

  public:

    int wordLength, letterHeight, letterWidth;

    byte letters[4][8];
   
    LedWord (int wordLength, const int letterHeight, int letterWidth) {

      //letters = lettersBuffer;

      this->wordLength = wordLength;
      this->letterHeight = letterHeight;
      this->letterWidth = letterWidth;
      this->ret = new boolean [letterHeight];

      for (int i = 0; i < wordLength; i++) {
        setLetter(i, 'A');
      }
    }

    boolean* nextLine();
    void setWord(char *word, int length);
    void setLetter (int letterIndex, char letter);

  private:

    //bitRead reads a bit starting on the LSB (right-most bit) and we want to start from the left (MSB)
    int currentIndex = letterWidth;
    // The letters are read as normal from left to right
    int currentLetter = 0;
    boolean* ret;

};

void LedWord::setLetter (int letterIndex, char letter) {
  char index = letter;

  Serial.print("Setting letter at index: ");
  Serial.println(letterIndex);
  Serial.print("Setting letter: ");
  Serial.println(letter);

//  // Force uppercase
//  if (letter >= 97 && letter <= 122) {
//    index = letter - 32;
//  } else {
//    index = letter;
//  }
//
//  //Check for special characters
//  switch (letter) {
//    case '$':
//      index = 27;
//      break;
//
//    case ' ':
//      index = 26;
//      break;
//  }


  for (int i=0;i <letterHeight; i++){
    letters[letterIndex][i] = ALPHABET[(index - 65)][i];
  }
  
  Serial.println("Alphabet:");
  Serial.println(ALPHABET[(index - 65)][0]);
  Serial.println(ALPHABET[(index - 65)][1]);
  Serial.println(ALPHABET[(index - 65)][2]);
  Serial.println(ALPHABET[(index - 65)][3]);

Serial.println("Letter saved: ");

  for(int i = 0; i <wordLength; i++){
  Serial.print(letters[letterIndex][i]);
  }

}

void LedWord::setWord (char *word, int wordlength) {


  int i;

  for (i = 0; i < wordlength; i++) {
    setLetter(i, word[i]);
  }

  //for the future when there is more than 2 letters, blank out the remaining letters in the lettersBuffer
  for (; i < wordLength; i++) {
    setLetter(i, ' ');
  }

}

boolean* LedWord::nextLine () {

  byte *letter = letters[currentLetter];
  Serial.println("Next line: ");
 

  for (int i = 0; i < letterHeight; i++) {
    Serial.println (letter[i]);
    ret[i] = bitRead(letter[i], currentIndex);


  }

  currentIndex--;

  if (currentIndex <= 0) {
    currentIndex = letterWidth;

    currentLetter++;

    if (currentLetter >= wordLength) {
      currentLetter = 0;
    }
  }
  return ret;
}
#endif
