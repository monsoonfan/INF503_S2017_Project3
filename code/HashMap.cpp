#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include "HashMap.h"

const int TABLE_SIZE = 265000;
const int seed_len = 16;
const unsigned int hash_seed= 1481986944;

using namespace std;

unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed )
{
	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.

	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	// Initialize the hash to a 'random' value

	unsigned int h = seed ^ len;

	// Mix 4 bytes at a time into the hash

	const unsigned char * data = (const unsigned char *)key;

	while(len >= 4)
	{
		unsigned int k = *(unsigned int *)data;

		k *= m; 
		k ^= k >> r; 
		k *= m; 
		
		h *= m; 
		h ^= k;

		data += 4;
		len -= 4;
	}
	
	// Handle the last few bytes of the input array

	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
} 


struct node {
	int location;
	node* next;
};

SeedEntry::SeedEntry(unsigned int value,int loc0){
	this->value = value;
	(this->head)->location = loc0;
	(this->head)->next = NULL;
}

void SeedEntry::addLocation(int loc){
	node *ptr = head;
	while(ptr != NULL){
		ptr = ptr->next;
	}
	ptr->location = loc;
	ptr->next = NULL;
}

void SeedEntry::retrieve(node *&output){
	output = head;
}

SeedEntry::~SeedEntry(){
	node *temp;
	temp = head;
	while( temp->next!=NULL)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
   free(temp);
}




///////////////////////////////////////////

HashEntry::HashEntry(int taxa, unsigned int size){
	this->taxa = taxa;
	this->locTable = new SeedEntry * [size];
}

// add seed to this taxID entry
void HashEntry::putSeed(int taxa, const void * key,int location) {
	unsigned int seed;
	if (this->taxa == taxa) {
		seed = MurmurHash2 (key, seed_len, hash_seed );
	}
	else {
		cout<<"The tax ID does not correspond to this hash entry"<<endl;
	}
	
	unsigned int hash = (seed% size);
	while (locTable[hash] != NULL && locTable[hash]->getSeed() != seed){
		hash = (hash+1)% size; // re-hash
	}
	// if this seed already present in the previous locations
	if (locTable[hash] != NULL) {
		locTable[hash]->addLocation(location);
	}
	// if this is the first time we observe this seed
	locTable[hash] = new SeedEntry(seed,location);
}

int HashEntry::getTaxa(){
	return taxa;
}
void HashEntry::getLocations(int taxa, const void * key,node *&output) {
	unsigned int seed;
	if (this->taxa == taxa) {
		seed = MurmurHash2 (key, seed_len, hash_seed );
	}
	else {
		cout<<"The tax ID does not correspond to this hash entry"<<endl;
	}
	
	unsigned int hash = (seed% size);
	while (locTable[hash] != NULL && locTable[hash]->getSeed() != seed){
		hash = (hash+1)% size; // re-hash
	}
	// if this seed already present in the previous locations
	if (locTable[hash] == NULL) {
		return NULL;
	}
	else {
		return locTable[hash]->retrieve(node *&output);
	}
}

unsigned int HashEntry::getSize() {
	return size;
}

HashEntry::~HashEntry() {
	for(int i=0;i<size;i++){
		if(locTable[i] != NULL) delete locTable[i];
	delete[] locTable;
	}
}


////////////////////////////////////////////

HashMap::HashMap() {
	table = new HashEntry * [TABLE_SIZE];
	for (int i=0; i<TABLE_SIZE;i++) table[i] = NULL;
}


void HashMap::get(int taxa, const void * seed,node *&output) {
	int hash = (taxa% TABLE_SIZE);
	while (table[hash] != NULL && table[hash]->getTaxa() != taxa){
		hash = (hash+1)% TABLE_SIZE; // re-hash
	}
	if (table[hash] == NULL) {
		output = NULL;
	}
	else{
		table[hash]->getLocations(taxa,seed,output);
	}
}

void HashMap::addTax(int taxa, unsigned int size){
	int hash = (taxa% TABLE_SIZE);
	while (table[hash] != NULL && table[hash]->getTaxa() != taxa){
		hash = (hash+1)% TABLE_SIZE; // re-hash
	}
	if (table[hash] != NULL) {
		delete table[hash];
	}
	table[hash] = new HashEntry(taxa,size);
}

void HashMap::addSeed(int taxa, const void * seed,int location) {
	int hash = (taxa% TABLE_SIZE);
	while (table[hash] != NULL && table[hash]->getTaxa() != taxa){
		hash = (hash+1)% TABLE_SIZE; // re-hash
	}
	
	if (table[hash] != NULL) {
		table[hash]->putSeed(taxa,seed,location);
	}
}

void HashMap::Initialize(char * file) {
	ifstream infile(file);
	int buffer_size = 100;
	char c;
	if (! infile) {
		cerr << "Fail to open table size file!" << endl;
	 }
	 
	int newID = 1;
	bool stop_now;
	int line_count = 0;
	char * taxa= new char[buffer_size];
	char * num_seeds = new char[buffer_size];
	int counter = 0;
	while (infile.get(c) && !stop_now)
	{
		if(c == '\n'){
			newID = 1;
			line_count ++;
			continue;
		 }

		if (c != ' '){
			taxa[0] = c;
			infile.get(&taxa[1], buffer_size-1, ':');
			infile.get(c);
			if (c != ':') {
				 cout << "ERROR: bad data on line " << line_count << endl;
				break;
			}
			infile.get(c);
			infile.get(num_seeds, buffer_size, '\n'); 
			counter ++;
			if(counter<5) cout<<atoi(taxa)<<": "<<atoi(num_seeds)<<endl;
		}
		  
		addTax(atoi(taxa),atoi(num_seeds));
		
		if (infile.eof()) {
			stop_now = true;
			continue;
		}
	 }
	
}

HashMap::~HashMap() {
	for(int i=0;i<TABLE_SIZE;i++){
		if(table[i] != NULL) delete table[i];
	delete[] table;
	}
}
//
//int main(){
//	int debug = 1;
//	HashMap *Map = new HashMap;
//	int taxID1 = 12345;
//	int taxID2 = 67890;
//	int	seed1[3] = {11,12,13};
//	int	seed2[3] = {14,15,16};
//	Map->addTax(taxID1,3);
//	Map->addSeed(taxID1,seed1[0]);
//	Map->addSeed(taxID1,seed1[1]);
//	Map->addTax(taxID2,3);
//	Map->addSeed(taxID2,seed2[0]);
//	Map->addSeed(taxID1,seed1[2]);
//	if (debug){
//		cout<<Map->get(taxID1,2)<<endl<<Map->get(taxID2,0)<<endl;
//	}
//	
//	
//}
