---------------------------------------------------------
# README - INF503_S2017_Project3
#
# Metagenomic Binning
# -------------------
# Project 3 repository for spring 2017 semester
#
---------------------------------------------------------

---------------------------------------------------------
# Application
---------------------------------------------------------
     usage: Project3 <subject_data> <query_data> <num_bases_to_read> <output> <subject_table_size> <query_table_size> <load_factor>
     
     example: (See Makefile for example usages)

     Description of inputs:
     <subject_data>       = Subject data to be read (FASTA format)
     <query_data>         = Query data to be read (FASTA format)
     <num_bases_to_read>  = Number of bases to read form the query data
     <output>             = Text file for output form the program
     <subject_table_size> = This file contains each TaxID in the subject data and # of words per TaxID
                            (for sizing the hash tables precisely)
     <query_table_size>   = Contains the number of each query and number of seeds that it has
                            (very simplified for Project 3 case, 85 seeds exist for each query read)
			    (this file is used to preserve direct use of the same HashMap for S/Q)
     <load_factor>        = This gives the user control over memory footprint/time to read data
     			    A load factor of 3 would yield a load on the hash tables of 0.33
                            A load factor of 2 would yield a load on the hash tables of 0.5

---------------------------------------------------------
# Makefile targets of interest
---------------------------------------------------------
       make build           (compile the program only)
       make build_and_run   (compile the program and run under a small test configuration)
       make run_v.%         (run the viruses for the specified number of bases)
       make run_b.%         (run the bacteria for the specified number of bases)
       make br.%            (compile and run the viruses for the specified number of bases)

---------------------------------------------------------
# File Reader details
---------------------------------------------------------
       The file reader is the pre-processer and loads the data into memory. The current implementation
       will read the table_size files and size the hashes accordingly. The final implementation would
       not require the use of those intermediate files.
       - Hash table sizing is the major feature of the pre-processor. A user can configure a lower load
         to decrease the time it takes to load the data, or a higher load to reduce the memory consumption
	 By pre-processing, re-sizing of the hash is not necessary.

       LIMITAIONS:
       - The current code can only store 2.13 giga-bases. This is the limitation of char arrays on the
         monsoon systems. A larger data structure would be needed in the final implementation. Would
	 try vectors first. Since we were only sub-setting the data for proof of concept, 2.13 G-bases
	 seemed sufficient.
       - The current pre-processing (to create the table size files) is done by misc_scripts/CountBins.pl
         The final implementation would do all pre-processing within FileReader.cpp

---------------------------------------------------------
# Hash Table details
---------------------------------------------------------
       HashTable.cpp & HashTable.h:
       1. To initialize the Hash Table, I used the output file of CountBins.pl. I saved the txt file in /home/jc3464/INF503/INF503_S2017_Project3/docs/TableSize.txt
       2. The arguments of main function becomes 6 values -> the last one is the TableSize.txt file
       3. I assume that in TableSize file "449400: 10" represents "taxID:number of seeds in this ID"
       4. to add seed into a taxID entry, just use
           Map->addSeed(449400,"ACGGTAGCTGCTGAGT");
       5. I added some debug printout in the main function, comment it when you are about the implement your function

---------------------------------------------------------
# Seed-based searching details
---------------------------------------------------------
	AlignmentAlgorithm.c
	1.Input: A) 2D array  ReadTaxStarting[ nof_readseed][ nof_startings]$ 
		contains starting points of each seed (out of nof_readseed)$ 
		of quary. nof_startings is the required columns to save this$
		 data.
		B)Input:MaxMM is maximum missmatch (example: 3)
		C)seed_size: size of each seed (example: 16)
	2.First column of ReadTaxStarting is -1 means null, i.e. no seed match$
	 found
	3.AlignmentRound0: Search to find first row, penalties added and if it$
	 pass threshold then giveup.  Threshold = MaxMM*seed_size;   
  
---------------------------------------------------------
# Comparison/alignment details
---------------------------------------------------------
       NeedlemanWunsch.cpp & NeedlemanWunsch.h
       1. the test function of NW is nwtest.cpp
       2. To initialize:
         NeedlemanWunsch 
          *nw = new NeedlemanWunsch(query,4,subject,5);
         where 4 and 5 is the length of query and subject
         
       3. To get the result of NW, you need to get the length of matched result first, using 
           int N = nw->final_length;
  
         and then set up the container for the result:
  
       char *s = new char[N];
       char *q = new char[N];
       char *l = new char[N];
    
       finally, use
       nw->get_alignment(s,q,l);
        
       to fill the container with new result.
 
