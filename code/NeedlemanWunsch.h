#ifndef NEEDLEMANWUNSCH_H
#define NEEDLEMANWUNSCH_H

#include <iostream>
#include <cstdio>
#include <cstdlib>


class NeedlemanWunsch
{
private:

		char * query;
		char * subject;
		int length_query;
		int length_subject;
		char * alignment_q;
		char * alignment_s;
		char * signs;
		
		
		int ** D_matrix;
		char ** trace_matrix;
		static const int scores[5][5];
		
		
		int radix(char);
		void find_best(int&,char&,int[3]);
		void trace_back();
		
public:
	NeedlemanWunsch(char *, int,char * ,int);
	~NeedlemanWunsch();
	
	int final_score;
	int final_length;
	
	
	void align();
	//int get_score();
	void get_alignment(char *&, char *&,char *&);
	
};

#endif

