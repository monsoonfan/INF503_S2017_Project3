#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include "FileReader.h"
#include "HashMap.h"
#include "NeedlemanWunsch.h"
//#include "ReadMatchTaxIDFunc.h"

using namespace std;

//////////////////////////
/// GLOBAL DEFINITIONS ///
//////////////////////////

////////////////////////
/// INLINE FUNCTIONS ///
////////////////////////
void help () {
  cout << "Usage: Project3Main.cpp <subject_data> <query_data> <#_of_bases_to_combine> <output_file>" << endl ;
}

////////////
/// MAIN ///
////////////
int main(int argc, char * argv[]) {
  cout << "--------------------------------------------------" << endl ;
  cout << "Project 3: Metagonomic Binning execution begins..." << endl ;
  cout << "--------------------------------------------------" << endl ;

  // Error checking and processing of inputs
  if (argc != 7) {
    help();
    return(EXIT_FAILURE);
  }
  char * subject_file = argv[1];
  char * query_file = argv[2];
  long int num_bases = atol(argv[3]);
  char * output_file = argv[4];
  char * statistic = argv[5];
  char * query_sizes = argv[6];
  if (strcmp(subject_file, output_file) == 0) {cerr << "ERROR: input and output file names the same!" << endl ; return EXIT_FAILURE;}
  if (access(subject_file, F_OK) == -1) {cerr << "ERROR: Can't open file " << subject_file << endl ; return EXIT_FAILURE;}
  if (access(query_file, F_OK) == -1) {cerr << "ERROR: Can't open file " << query_file << endl ; return EXIT_FAILURE;}
  if (access(statistic, F_OK) == -1) {cerr << "ERROR: Can't open file " << statistic << endl ; return EXIT_FAILURE;}

  // Variables for main
  long int extra_bases = 25000;
  int num_queries = 20; // 961710 total, only 20 for testing
  int num_mers_per_query = 100;
  printf ("creating new char array with %ld elements...\n",num_bases);
  char * subject_data = new char[num_bases + extra_bases];
  char * query_data = new char[num_queries * num_mers_per_query + 1];
  
  // Read the input data
  FileReader fr;
  HashMap * subject_map = new HashMap;
  subject_map->Initialize(statistic);
  fr.ReadSubjects(subject_file, subject_data, num_bases, subject_map);

  HashMap * query_map = new HashMap;
  query_map->Initialize(query_sizes);
  fr.ReadQueries(query_file, query_data, num_queries, query_map);
  
  // Process the queries against the subjects

  // Successful exit with cleanup
  delete[] subject_data;
  delete[] query_data;
  return(EXIT_SUCCESS);
}
