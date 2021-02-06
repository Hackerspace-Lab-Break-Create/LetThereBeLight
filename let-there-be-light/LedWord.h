#ifndef _LED_WORD_
#define _LED_WORD_

#include "PovAlphabet8x8.h"

class LedWord {

  public:

    int wordLength, letterHeight, letterWidth;
    byte **letters;
    int i;
    LedWord (int wordLength, const int letterHeight, int letterWidth) {

      this->letters = new byte *[50];
      for (int i = 0; i < 50; i++) {
        letters[i] = new byte[letterHeight];
      }

      this->wordLength = wordLength;
      this->letterHeight = letterHeight;
      this->letterWidth = letterWidth;
      this->ret = new bool[letterHeight];

      currentIndex = letterWidth - 1;
    }

    ~LedWord () {
      for (int i = 0; i < 50; i++) {
        delete[] letters[i];
      }
      delete[] letters;
      delete[] ret;
    }

    bool* nextLine();
    void setWord(String word, int length);
    void setLetter (int letterIndex, char letter);

  private:

    //bitRead reads a bit starting on the LSB (right-most bit) and we want to start from the left (MSB)
    int currentIndex;
    // The letters are read as normal from left to right
    int currentLetter = 0;
    bool* ret;

};

void LedWord::setLetter (int letterIndex, char letter) {
  char index = letter;


  // Force uppercase
  if (letter >= 97 && letter <= 122) {
    index = letter - 32;
  } else {
    index = letter;
  }

  //Check for special characters
  switch (letter) {
    case '$':
      index = 27 + 65;
      break;

    case ' ':
      index = 26 + 65;
      break;
  }

  for (int i = 0; i < letterHeight; i++) {
    letters[letterIndex][i] = ALPHABET[(index - 65)][i];

  }

}

void LedWord::setWord (String word, int newWordLength) {
  int i;
  wordLength = newWordLength;

  for (i = 0; i < wordLength; i++) {
    setLetter(i, word[i]);
  }

  //for the future when there is more than 2 letters, blank out the remaining letters in the lettersBuffer
  for (; i < 50; i++) {
    setLetter(i, ' ');
  }

}

bool* LedWord::nextLine () {


  byte *letter = letters[currentLetter];
  
    for (int i = 0; i < letterHeight; i++) {
      ret[i] = bitRead(letter[i], currentIndex);
    }
  
  
    currentIndex--;
  
    if (currentIndex < 0) {
      currentIndex = letterWidth - 1;

//  ret = letter[i];
//
//   i++;
//   
//  if (i > 7) {
//    i = 0;

    currentLetter++;

    if (currentLetter >= wordLength) {
      currentLetter = 0;
    }
  }
 

  return ret;
}
#endif
