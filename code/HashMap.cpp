#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>

const int TABLE_SIZE = 128;

using namespace std;

class HashEntry {
	private:
	 	int key;
	 	int *value;
	 	unsigned int size;
	 	unsigned int cursor;
	 	
	public:
		HashEntry(int key, unsigned int size){
			this->key = key;
			this->size = size; //use &head
			value = new int[size];
			cursor = 0;
		}
		// put a new value into hash table
		put(int key, int seed) {
			if (this->key  == key) {
				value[cursor] = seed;
				cursor++;
			}
		}
		
		int getKey(){
			return key;
		}
		
		int getValue(int n) {
			return value[n];  //we're returning the address of value[0]
		}
		
		int getSize() {
			return size;
		}

};

class HashMap{
	private:
		HashEntry **table;
	public:
		HashMap() {
			table = new HashEntry * [TABLE_SIZE];
			for (int i=0; i<TABLE_SIZE;i++) table[i] = NULL;
		}
		
		int get(int key,int position) {
			int hash = (key% TABLE_SIZE);
			while (table[hash] != NULL && table[hash]->getKey() != key){
				hash = (hash+1)% TABLE_SIZE; // re-hash
			}
			if (table[hash] == NULL) {
				return -1;
			}
			else{
				return table[hash]->getValue(position);
			}
		}
		
		void addTax(int key, unsigned int size){
			int hash = (key% TABLE_SIZE);
			while (table[hash] != NULL && table[hash]->getKey() != key){
				hash = (hash+1)% TABLE_SIZE; // re-hash
			}
			if (table[hash] != NULL) {
				delete table[hash];
			}
			table[hash] = new HashEntry(key,size);
		}
		
		void addSeed(int key, int seed) {
			int hash = (key% TABLE_SIZE);
			while (table[hash] != NULL && table[hash]->getKey() != key){
				hash = (hash+1)% TABLE_SIZE; // re-hash
			}
			
			if (table[hash] != NULL) {
				table[hash]->put(key,seed);
			}
		}
		
		~HashMap() {
			for(int i=0;i<TABLE_SIZE;i++){
				if(table[i] != NULL) delete table[i];
			delete[] table;
			}
		}
};

int main(){
	int debug = 1;
	HashMap *Map = new HashMap;
	int taxID1 = 12345;
	int taxID2 = 67890;
	int	seed1[3] = {11,12,13};
	int	seed2[3] = {14,15,16};
	Map->addTax(taxID1,3);
	Map->addSeed(taxID1,seed1[0]);
	Map->addSeed(taxID1,seed1[1]);
	Map->addTax(taxID2,3);
	Map->addSeed(taxID2,seed2[0]);
	Map->addSeed(taxID1,seed1[2]);
	if (debug){
		cout<<Map->get(taxID1,2)<<endl<<Map->get(taxID2,0)<<endl;
	}
	
	
}
