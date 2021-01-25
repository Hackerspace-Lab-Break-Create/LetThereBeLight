#ifndef _LED_WORD_
#define _LED_WORD_

#include "PovAlphabet8x8.h"
class LedWord {

  public:
    int wordLength, letterHeight, letterWidth;
    
    byte *letters; 
    
    LedWord(byte *lettersBuffer, int wordLength, const int letterHeight, int letterWidth) {
      letters = lettersBuffer;
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
    boolean *ret;
};

void LedWord::setLetter (int letterIndex, char letter) {
  char index;

  // Force uppercase
  if (letter >=97 && letter <= 122){
    index = letter - 32;
  }else{
    index = letter;
  }

  //Check for special characters
  switch (letter){
    case '$':
        index = 26;
        break;
        
    case ' ':
        index = 27;
        break;
  }

  letters[letterIndex] = *ALPHABET[(index-65)];

}

void LedWord::setWord (char *word, int length) {
  int i;

  for (i = 0; i < length; i++) {
    setLetter(i, word[i]);
  }

  //for the future when there is more than 2 letters, blank out the remaining letters in the lettersBuffer
  for (; i < wordLength; i++) {
    setLetter(i, ' ');
  }

}

boolean* LedWord::nextLine () {

  byte letter = letters[currentLetter];
  for (int i=0;i<letterHeight;i++){
    ret[i] = bitRead(letter, currentIndex);
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
