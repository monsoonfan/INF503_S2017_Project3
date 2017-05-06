#include "stdafx.h"
#include "FileReader.h"
#include "Word.h"
#include "HashMap.h"
#include <iostream>
#include <fstream>

#define READ_STATUS_LINES 1000000
#define READ_STATUS_BASES 10000000

using namespace std;

/*----------------------------------------------------------------------
  FileReader class
  4/13/17
  rmr5
-----------------------------------------------------------------------*/
FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

/*
--- PreProcessSubjects ---
- 4/28/17
- rmr5
-----------------

Method to process a file of genomic sequences (having GID and TaxID) and report the following:
  - the number of GID's we have per TaxID. This is for hash table sizing.
  - actually, what we need are number of TaxIDs and number of words per TaxID
    - probably need some sort of modulo 16 based algo to help with this


  - METHODOLOGY
  - pre-process the fasta to find out how many words will be stored for each TaxID
  - In pre-process mode, all data sctructures are initialized to NULL values

  - Then, after DS are initialized, we can read the file again and store each word
    into it's TaxID's hash.
  - Don't need to string all of the sequences together in order to know about start/stop
    Since processing the file from 1st to last char (effectively strung together), we just
    need to store the start/stop for each word in the TaxID

    This will have the effect of saving us the "string" data structure

  - Process is basically the same for storing query seeds, right?

needs:
 array of 16 words (maybe it's a stack, and each time I pop one off to store  on TaxID>word
 * hold on here, perhaps the key of the word is it's start value?
 array of each word's start
 

*/

/*
--- ReadSubjects ---
- 4/13/17
- rmr5
-----------------

Method to read the genomic sequences from a file into a hash table
Combine N number of bases from multiple genomic sequences into a single sequence

- read header information 

*/
int FileReader::ReadSubjects(char * file, char * values, long int num_bases_to_read, HashMap * map)
{
  cout << "Reading " << num_bases_to_read << " bases of FASTA file ..." << file << endl ;

  // Variables and info messages
  bool dbg = (DEBUG && 0);
  char c;
  int char_count = 0;
  int line_count = 0;
  bool stop_next_header = false;
  bool stop_now = false;
  int swap_to_N_count = 0;
  int gi_count = 0;

  int id_buffer_size = 100;
  char * gi_id = new char[id_buffer_size];
  char * tax_id = new char[id_buffer_size];

  int word_size = 16;
  Word word = Word();
  int num_words = 0; // per taxID
  int start_index = 0;
  int end_index = 0;
  char * write_buffer = new char[word_size];
  int store_return = 0;
  int val;

  bool stop_info = true;
  bool read_status = true;
  ifstream infile(file);
  
  if (! infile) {
    cerr << "Can't open input file!" << endl;
  }
  
  while (infile.get(c) && !stop_now)
    {
      /*------------- Special cases -----------------*/

      // Stop reading after this sequence if..
      if (char_count >= num_bases_to_read) {
	if (stop_info) {
	  cout << "Reached " << num_bases_to_read << " bases read, stopping at end of current sequence" << endl;
	  stop_info = false;
	}
	stop_next_header = true;
      }

      // New line triggers reset of variables and potential file reading stop
      if (c == '\n') {
	if (dbg) cout << c;
	line_count++;
	continue;
      }

      // Grab the header - need to do this before non-ACGT swap
      if (c == '>') {
	word.reset();                              // reset the word buffer to prep it for next GI

	if (stop_next_header) break;

	infile.get(gi_id, id_buffer_size, '-');    // get the GI
	infile.get(c);                             // advance past the -
	if (c != '-') {
	  cout << "ERROR: bad header on line " << line_count << endl;
	  char_count = -1;
	  break;
	}
	infile.get(tax_id, id_buffer_size, '\n');  // get the TaxID
	if (dbg) cout << "Header: " << gi_id << ", " << tax_id << endl;
	infile.get(c);                             // advance past the \n
	if (c != '\n') {
	  cout << "ERROR: bad header on line " << line_count << endl;
	  char_count = -1;
	  break;
	}
	start_index = char_count;
	gi_count++;
	line_count++;
	read_status = true;
	continue;
      }

      // Substitution if non-ACGT char
      if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
	c = 'N';
	swap_to_N_count++;
      }

      // Store a word here after reading a char, this will store only if the word is full
      if (dbg) cout << "\nDBG: storing c " << c << endl;
      store_return = word.store(c, write_buffer);
      if (dbg) cout << "DBG: write_buffer: " << write_buffer << endl;
      if (store_return) {
	val = atoi(tax_id);
	if (dbg) cout << "DBG:  val = " << val << " from tax_id: " << tax_id << endl;
	//map->addSeed(val, write_buffer, char_count); // doesn't compile
      }
      num_words += store_return;
      //cout << num_words << endl;;

      // Fail safe in case of broken file
      if (char_count > num_bases_to_read * 2) {
	printf("Stopping at fail safe, please check the file\n");
	return -1;
      }

      // Finish up cleanly if we hit EOF
      if (infile.eof()) {
	stop_now = true;
	continue;
      }
      /*------------- End Special cases -------------*/

      // If not a special case, grab the next char from the file and adjust vars
      values[char_count++] = c ;
      end_index++;
      
      if (dbg) cout << c ;

      // Some logfile info
      if ((char_count % READ_STATUS_BASES) == 0) cout << "  " << char_count << " bases..." << endl;
      if ((line_count % READ_STATUS_LINES) == 0 && read_status) {
	cout << "Info: " << line_count << " lines so far..." << endl;
	read_status = false;
      }

    }

  // Clean up
  delete[] gi_id;
  delete[] tax_id;
  delete[] write_buffer;

  // Report and return
  cout << "Done, processed " << line_count << " lines of " << file << endl;
  cout << "Total of " << char_count << " bases read from " << gi_count << " sequences" << endl;
  cout << swap_to_N_count << " were swapped from non-ACGT to 'N'" << endl;
  cout << "Total of " << num_words << " words were stored" << endl;
  cout << endl;
  return char_count;

}

/*
--- ReadQueries ---
- 4/14/17
- rmr5
-----------------

Method to read genomic sequence fragments from a file into a hash table
 
*/
int FileReader::ReadQueries(char * file, char * values, int num_queries_to_read, HashMap * map)
{
  cout << "Reading " << num_queries_to_read << " queries of FASTA file ..." << file << endl ;

  // Variables and info messages
  bool dbg = (DEBUG && 0);
  char c;
  int char_count = 0;
  int line_count = 0;
  int swap_to_N_count = 0;
  int read_count = 0;
  
  int id_buffer_size = 100;
  char * read_id = new char[id_buffer_size];

  int seed_size = 16;
  Word seed = Word();
  int num_seeds = 0; // per taxID
  int start_index = 0;
  int end_index = 0;
  char * write_buffer = new char[seed_size];
  int store_return = 0;
  int val;
  
  ifstream infile(file);
  
  if (! infile) {
    cerr << "Can't open input file!" << endl;
  }
  
  while (infile.get(c))
    {
      /*------------- Special cases -----------------*/

      // Done reading if read target number of reads
      if (read_count >= num_queries_to_read) {
	cout << "Completed reading target number of reads" << endl;
	break;
      }

      // Grab the header - need to do this before non-ACGT swap
      if (c == '>') {
	seed.reset();

	infile.get(read_id, id_buffer_size, '\n');  // get the TaxID

	if (dbg) cout << "Header: " << read_id << ", " << endl;
	infile.get(c);                             // advance past the \n
	if (c != '\n') {
	  cout << "ERROR: bad header on line " << line_count << endl;
	  char_count = -1;
	  break;
	}
	line_count++;
	continue;
      }

      // New line triggers reset of variables and potential file reading stop
      // this works because the header grab advances past it's newline
      if (c == '\n') {
	if (dbg) cout << c;
	read_count++;
	line_count++;
	continue;
      }

      // Substitution if non-ACGT char
      if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
	c = 'N';
	swap_to_N_count++;
      }

      // Store a word here after reading a char, this will store only if the word is full
      if (dbg) cout << "\nDBG: storing c " << c << endl;
      store_return = seed.store(c, write_buffer);
      if (dbg) cout << "DBG: write_buffer: " << write_buffer << endl;
      if (store_return) {
	val = atoi(read_id);
	if (dbg) cout << "DBG:  val = " << val << " from read_id: " << read_id << endl;
	map->addSeed(val, write_buffer, char_count); // doesn't compile
      }
      num_seeds += store_return;
      //cout << num_seeds << endl;;

      // Fail safe in case of broken file
      if (line_count > num_queries_to_read * 3) {
	printf("Stopping at fail safe, please check the file\n");
	return -1;
      }

      // Finish up cleanly if we hit EOF
      if (infile.eof()) {
	// TODO: store on hash right here
	cout << "Reached end of file..." << endl;
	break;
      }
      /*------------- End Special cases -------------*/

      // If not a special case, grab the next char from the file and adjust vars
      values[char_count++] = c ;
      
      if (dbg) cout << c ;
  
    }

  // Clean up
  delete[] read_id;

  // Report and return
  cout << "Done, processed " << line_count << " lines of " << file << endl;
  cout << "Total of " << char_count << " bases read from " << read_count << " reads" << endl;
  cout << swap_to_N_count << " were swapped from non-ACGT to 'N'" << endl;
  cout << "Total of " << num_seeds << " seeds were stored" << endl;
  cout << endl;
  return char_count;

}
