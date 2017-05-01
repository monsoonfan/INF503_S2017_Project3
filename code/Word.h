#pragma once

#include <string>

class Word
{
 public:
  // Variables
  int head;
  int count; // thought about capping this at word_size, but let it go over, could be useful
  static const int word_size = 16;
  bool is_full;
  //char * array = new char[16];
  char array[word_size];
  bool DEBUG = true;
  
  // Methods
  Word();
  ~Word();
  int store (char);
  unsigned int write(int); // TODO: add hash as input here
//  char buildString();    // last 16 chars to hash function
  void reset();
  
};
