#include "stdafx.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>

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
--- ReadSubjects ---
- 4/13/17
- rmr5
-----------------

Method to read the genomic sequences from a file into a hash table
Combine N number of bases from multiple genomic sequences into a single sequence

- read header information 

*/
int FileReader::ReadSubjects(char * file, char * values, int num_bases_to_read)
{
  cout << "Reading " << num_bases_to_read << " of FASTA file ..." << file << endl ;

  // Variables and info messages
  char c;
  int char_count = 0;
  int line_count = 0;
  int fail_safe = 0;
  bool stop_next_header = false;
  bool stop_now = false;
  int swap_to_N_count = 0;
  int gi_count = 0;

  int id_buffer_size = 100;
  char * gi_id = new char[id_buffer_size];
  char * tax_id = new char[id_buffer_size];
  int start_index = 0;
  int end_index = 0;
  
  ifstream infile(file);
  
  if (! infile) {
    cerr << "Can't open input file!" << endl;
  }
  
  while (infile.get(c) && !stop_now)
    {
      /*------------- Special cases -----------------*/

      // Stop reading after this sequence if..
      if (char_count >= num_bases_to_read) {
	stop_next_header = true;
      }

      // New line triggers reset of variables and potential file reading stop
      if (c == '\n') {
	if (DEBUG) cout << c;
	line_count++;
	continue;
      }

      // Grab the header - need to do this before non-ACGT swap
      if (c == '>') {
	// TODO: store on the hash right here, along with 4 NNNNs (4 N only if gi_count > 0
	//       and potentially not if stop_next_header)
	// for (int i = 0; i < 4; i++) {values[char_count++] = 'N''}
	if (stop_next_header) break;
	infile.get(gi_id, id_buffer_size, '-');    // get the GI
	infile.get(c);                             // advance past the -
	if (c != '-') {
	  cout << "ERROR: bad header on line " << line_count << endl;
	  char_count = -1;
	  break;
	}
	infile.get(tax_id, id_buffer_size, '\n');  // get the TaxID
	if (DEBUG) cout << "Header: " << gi_id << ", " << tax_id << endl;
	infile.get(c);                             // advance past the \n
	if (c != '\n') {
	  cout << "ERROR: bad header on line " << line_count << endl;
	  char_count = -1;
	  break;
	}
	start_index = char_count;
	gi_count++;
	line_count++;
	continue;
      }

      // Substitution if non-ACGT char
      if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
	c = 'N';
	swap_to_N_count++;
      }

      // Fail safe in case of broken file
      if (char_count > num_bases_to_read * 2) {
	printf("Stopping at fail safe, please check the file\n");
	return NULL;
      }

      // Finish up cleanly if we hit EOF
      if (infile.eof()) {
	// TODO: store on hash right here
	stop_now = true;
	continue;
      }
      /*------------- End Special cases -------------*/

      // If not a special case, grab the next char from the file and adjust vars
      values[char_count++] = c ;
      end_index++;
      
      if (DEBUG) cout << c ;
  
    }

  // Clean up
  delete[] gi_id;
  delete[] tax_id;

  // Report and return
  cout << "Done, processed " << line_count << " lines of " << file << endl;
  cout << "Total of " << char_count << " bases read from " << gi_count << " sequences" << endl;
  cout << swap_to_N_count << " were swapped from non-ACGT to 'N'" << endl;
  cout << endl;
  return char_count;

}
