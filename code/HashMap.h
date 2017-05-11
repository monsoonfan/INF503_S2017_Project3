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

class node {
	public:
		node(){}
		int location;
		node* next;
		
};



class SeedEntry {
	private:
		unsigned int value; // this is the hashed value of this seed
		node * head; // the list of locations where this seed present
		
	public:
		
		SeedEntry(){head = new node;}
		SeedEntry(unsigned int,int); // input: seed value and the first occurred location
		unsigned int getSeed();
		void addLocation(int);
		void retrieve(node *&);
		void print();
		
		//int listSize();
		~SeedEntry();
		
};

class HashEntry {
	private:
	 	int taxa;
	 	SeedEntry **locTable;
	 	int size;
	 	
	public:
		HashEntry(int, int, int); // input: taxID, size of this taxID
		SeedEntry** getHead(){
			return &this->locTable[0];
		}
		void putSeed(int, const void *,int); // input taxID, seed string, location of this seed
		int getTaxa();
		void getLocations(int, const void *,node *&);
		int getSize();
		//void getHead(SeedEntry *&);
		~HashEntry();

};

class HashMap{
	private:
		HashEntry **table;
	public:
		HashMap();
		HashEntry** getHead(){
			return &this->table[0];
		}
		void get(int, const void *,node *&); // input: taxID, seed, output pointer
		void addTax(int,int,int); // input: taxaID, size of it
		void addSeed(int, const void *,int); // input taxID, seed string, location of this seed
		void Initialize(char *,int);
		//const HashEntry getHead() const {return table[0];}
		~HashMap();
};


#endif

