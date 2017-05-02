/*
--- Word.cpp ---
- 4/29/17
- rmr5
-------------

Custom data structure for the Project3 preprocessor

*/
#include "stdafx.h"

#include "Word.h"
#include <iostream>
#include <string>

using namespace std;

/*
--- Word ---
- 4/29/17
- rmr5
-------------

This is the default constructor, could easily add an overloaded constructor in
which the word_size is passed to the constructor instead of the default 16

*/
Word::Word()
{
	cout << "Initializing word..." << endl;

	// Initialize variables and the array
	head = 0;
	count = 0;
	is_full = false;
	for (int i = 0; i < word_size - 1; i++) {
		array[i] = 'Z';
	}
}

Word::~Word()
{
	// Delete this if final implementation has no memory allocation
}

/*
--- store ---
- 4/29/17
- rmr5
-------------

Given a character, write the current 16-char word (if full), and store
the new character in the word.

This method manages head, write will only manage the characters in relation to head.

*/
int Word::store(char c)
{
  // Variables
  int write_val = 0;

	// First step is to write out the current buffer
  write_val = write(word_size);

	// Second is to store the new char at the head
	array[head] = c;
	count++;
	if (count >= word_size) is_full = true;

	// Third is to adjust head, wrap around if at last char
	if (head == word_size - 1) {
		head = 0; // wrap-around
	}
	else {
		head++;
	}

	return write_val;
}


/*
--- write ---
- 4/29/17
- rmr5
-------------

Will write word_size chars from the buffer array at the current head location

*/
unsigned int Word::write(int s)
{
	// Variables
	int index = head;

	// Write only if the word is full
	if (is_full) {
	  if (DEBUG && debug) cout << "DBG: write from head: " << index << endl;
		// Write word_size chars starting from head
		for (int i = 0; i < word_size; i++) {
			if (DEBUG && debug) cout << array[index];
			// TODO: how to write the values, I'm thinking that a pointer to 
			//       hash element where this will go gets passed in and we write
			//       one char at a time, incrementing the pointer with ++
			if (index >= word_size - 1) {
				index = 0;
			}
			else {
				index++;
			}
		}
		if (DEBUG && debug) cout << endl;
		return 1;
	}
	else {
		return 0;
	}
}

/*
char Word::buildString()
{
	return 'Z';
}
*/


/*
--- reset ---
- 5/1/17
- rmr5
-------------

Resets the values for a word object an re-initializes the array to all 'Z'

*/
void Word::reset()
{
	// Reset all values to Z so that bugs will be recognizable
	for (int i = 0; i < word_size - 1; i++) {
		array[i] = 'Z';
	}

	// Now reset the variables
	head = 0;
	count = 0;
	is_full = false;
}

/*
--- main ---
- 4/29/17
- rmr5
-------------

Used for testing of the Word class, basically a unit test

*/
/*
int main()
{
	cout << "Testing Word class..." << endl;
	// Test the Word class
	Word W = Word();
	W.store('A');
	W.store('C');
	W.store('T');
	W.store('G');
	W.store('G');
	W.store('T');
	W.store('G');
	W.store('A');
	W.store('C');
	W.store('C');
	W.store('C');
	W.store('T');
	W.store('A');
	W.store('T');
	W.store('G');
	W.store('C');
	W.store('T');
	W.store('T');

	cout << "Done" << endl;
    return 0;
}
*/
