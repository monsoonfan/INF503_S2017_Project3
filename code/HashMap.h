#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>

/*
	Author: Jiaming Chen
	Date: 29/04/17 15:42
	Description: Header file for Hash Table to store all the seeds in the database
*/

unsigned int MurmurHash2 ( const void * , int, unsigned int);

class HashEntry {
	private:
	 	int taxa;
	 	unsigned int *value;
	 	unsigned int size;
	 	unsigned int cursor;
	 	
	public:
		HashEntry(int, unsigned int);
		// put a new value into hash table
		void put(int, const void *);
		int getTaxa();
		int getValue(int);
		int getSize();

};

class HashMap{
	private:
		HashEntry **table;
	public:
		HashMap();
		int get(int,int);
		void addTax(int, unsigned int);
		void addSeed(int, const void *);
		void Initialize(char *);
		~HashMap();
};
#endif

