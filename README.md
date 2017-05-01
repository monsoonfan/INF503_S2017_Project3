# INF503_S2017_Project3
Project 3 repository for spring 2017 semester


HashTable.cpp & HashTable.h:
1. To initialize the Hash Table, I used the output file of CountBins.pl. I saved the txt file in /home/jc3464/INF503/INF503_S2017_Project3/docs/TableSize.txt
2. The arguments of main function becomes 6 values -> the last one is the TableSize.txt file
3. I assume that in TableSize file "449400: 10" represents "taxID:number of seeds in this ID"
4. to add seed into a taxID entry, just use
    Map->addSeed(449400,"ACGGTAGCTGCTGAGT");
5. I added some debug printout in the main function, comment it when you are about the implement your function

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
  
