#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include "FileReader.h"
#include "HashMap.h"
#include "NeedlemanWunsch.h"

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
  if (argc != 6) {
    help();
    return(EXIT_FAILURE);
  }
  char * subject_file = argv[1];
  char * query_file = argv[2];
  unsigned int num_bases = atoi(argv[3]);
  char * output_file = argv[4];
  char * statistic = argv[5];
  if (strcmp(subject_file, output_file) == 0) {cerr << "ERROR: input and output file names the same!" << endl ; return EXIT_FAILURE;}
  if (access(subject_file, F_OK) == -1) {cerr << "ERROR: Can't open file " << subject_file << endl ; return EXIT_FAILURE;}
  if (access(query_file, F_OK) == -1) {cerr << "ERROR: Can't open file " << query_file << endl ; return EXIT_FAILURE;}
  if (access(statistic, F_OK) == -1) {cerr << "ERROR: Can't open file " << statistic << endl ; return EXIT_FAILURE;}
  // Variables for main
  int extra_bases = 25000;
  //int num_queries = 961710;
  unsigned int num_queries = num_bases;
  int num_mers_per_query = 100;
  char * subject_data = new char[num_bases + extra_bases];
  char * query_data = new char[num_queries * num_mers_per_query + 1];

  // Read the input data
  //start tesing hash table
  

    HashMap * Map = new HashMap;
    Map->Initialize(statistic);
    delete Map;
  /*
  //Map->addTax(449400,10);// just for test, it's the first taxID we have 
  //Map->addTax(1714570,4);
  cout<<"starting adding seeds"<<endl;
  // Map->addLocation(<seed_num>,"SEED",<int: start_loc>)

  //const char * test_string = "ACGGTAGCTGCTGAGT"; // this works, but not sure how to generate this from the Word class
  char test_string[16];
  for (int i = 0; i < 16; i++) {
    test_string[i] = 'A';
  }
  //Map->addSeed(663559,"ACGGTAGCTGCTGAGT",8);
  Map->addSeed(663559,test_string,8);

  node *head = new node;
  //Map->get(169865,"ACGGTAGCTGCTGAGT",head);
  //Map->get(169865,test_string,head);
  //char * test_string = "
  /*
  Map->addSeed(663559,"ACGGTAGCTGCTGAGT",15);
  Map->addSeed(663559,"ACGGTAGCTGCTGAGT",25);
  Map->addSeed(169865,"ACGGTAGCTGCTGAGT",5);
  
  cout<<"end adding seeds"<<endl;
  Map->get(169865,"ACGGTAGCTGCTGAGT",head);
  cout<<head->location;
  //printList(head);
  //cout<<Map->get(449400,0)<<endl;
  //cout<<Map->get(31600,0)<<endl;
  //end 
  */
  
  FileReader fr;
  cout << "DBG reading subjects..." << endl;
  fr.ReadSubjects(subject_file, subject_data, num_bases, Map);
  //  fr.ReadQueries(query_file, query_data, num_queries);

  // Successful exit with cleanup
  delete[] subject_data;
  delete[] query_data;
  return(EXIT_SUCCESS);
}
