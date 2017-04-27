#include <iostream>
#include <cstdio>
#include <cstdlib>

//#include "NeedlemanWunsch.h"
using namespace std;
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
		int scores[5][5] = {
			{0,-3,-3,-3,-3},
			{-3,2,-1,-1,-1},
			{-3,-1,2,-1,-1},
			{-3,-1,-1,2,-1},
			{-3,-1,-1,-1,2}
		};
		
		
		int radix(char);
		//void find_best(int&,char&,int[3]);
		void trace_back();
		
public:
	NeedlemanWunsch(char * query, int length_query,char * subject,int length_subject);
	~NeedlemanWunsch();
	
	int final_score;
	int final_length;
	
	
	void align();
	//int get_score();
	void get_alignment(char *&, char *&,char *&);
	
};

NeedlemanWunsch::NeedlemanWunsch(char * query, int length_query,char * subject,int length_subject)
{
	this->query = query;
	this->subject = subject;
	this->length_query = length_query;
	this->length_subject = length_subject;
	
	
	this->final_score = 0;
	this->D_matrix = new int*[this->length_subject+1];
	this->trace_matrix = new char*[this->length_subject+1];
	
	for (int i = 0; i < (this->length_subject + 1); i++)
	{
		this->D_matrix[i] = new int[this->length_query + 1];
		this->trace_matrix[i] = new char[this->length_query + 1];
	}

	for (int i = 0; i < length_subject; i++)
	{
		for (int j = 0; j < length_subject; j++)
		{
			D_matrix[i][j] = 0;
			trace_matrix[i][j] = NULL;
		}
	}
	
}

NeedlemanWunsch::~NeedlemanWunsch()
{
	for (int i = 0; i < (length_subject + 1); i++)
	{
		delete[] this->D_matrix[i];
		delete[] this->trace_matrix[i];
	}
	delete[] this->D_matrix;
	delete[] this->trace_matrix;
}

int NeedlemanWunsch::radix(char base)
{
	int sum;
		switch(base) {
			case ' ':
				sum = 0;
				break;
			case 'A' :
				sum = 1;
				break;
			case 'C' :
				sum = 2;
				break;
			case 'G' :
				sum = 3;
				break;
			case 'T' :
				sum = 4;
				break;
		}
	return sum;
}

//void NeedlemanWunsch::find_best(int &d,char &t,int choices[3])
//{
//	d = max(choices);
//	if(choices[0] == d) t = 'm';
//	else if (choices[1] == d) t = 'd';
//	else t = 'i';
//}

void NeedlemanWunsch::trace_back()
{
	int l;
	if(length_subject>=length_query) l =length_subject;
	else l = length_query;
	final_length = l;
	alignment_s = new char[l];
	alignment_q = new char[l];
	signs = new char[l];
	int i = length_subject;
	int j = length_query;
	while (i > 0 || j > 0)
	{
		if(trace_matrix[i][j] == NULL) break;
		// Going to S(i-1, j-1)
		if (i > 0 && j > 0 && trace_matrix[i][j] == 'm')
		{
			alignment_s[l-1] = subject[i - 1] ;
			alignment_q[l-1] = query[j - 1];
			if (subject[i - 1] != query[j - 1])
			{
				signs[l-1] = 'x';
			}
			else
			{
				signs[l-1] = '|';
			}
			i -= 1;
			j -= 1;
			l -= 1;
		}
		// Going to S(i-1, j)
		else if(i > 0 && trace_matrix[i][j] == 'd')
		{
			alignment_s[l-1] = subject[i - 1] ;
			alignment_q[l-1] = '-' ;
			signs[l-1] = 'x';
			i -= 1;
			l -= 1;
		}
		// Going to S(i, j-1)
		else
		{
			alignment_s[l-1] = '-' ;
			alignment_q[l-1] = query[j-1] ;
			signs[l-1] = 'x';
			l -= 1;
			j -= 1;
		}
		
	}
}


void NeedlemanWunsch::align()
{
	int gap_penalty = -3;
	
	for (int i = 0; i < (length_subject + 1); i++)
	{
		D_matrix[i][0] = i * gap_penalty;
	}
	
	for (int j = 0; j < (length_subject + 1); j++)
	{
		D_matrix[0][j] = j * gap_penalty;
	}
	
	int match = 0, insert = 0, del = 0 , max = 0, selected = 0;
	//int *choices = new int[3];
	for (int i = 1; i < length_subject + 1; i++)
	{
		for (int j = 1; j < length_query + 1; j++)
		{
			match = D_matrix[i - 1][j - 1] + 
				D_matrix[radix(subject[i - 1])] [radix(query[j - 1])];
			del = D_matrix[i - 1][j] + gap_penalty;
			insert = D_matrix[i][j - 1] + gap_penalty;

			//choices[0]=match; choices[1]=del;choices[2]=insert;
			//int d = max(choices);
			
			if(match>del&&match>insert) {
				trace_matrix[i][j] = 'm';
				D_matrix[i][j] = match;
			}
			else if (del>match&&del>insert){
				trace_matrix[i][j] = 'd';
				D_matrix[i][j] = del;
			} 
			else{
				trace_matrix[i][j] = 'i';
				D_matrix[i][j] = insert;
			} 
		}
	}
	
	trace_back();
	final_score = D_matrix[length_subject][length_query];
	
}

//int NeedlemanWunsch::get_score()
//{
//	return final_score;
//}

void NeedlemanWunsch::get_alignment(char *&s1, char *&s2, char *&l)
{
	for(int i=0;i<final_length;i++){
		s1[i] = alignment_s[i];
		s2[i] = alignment_q[i];
		l[i] = signs[i];
	}
}



