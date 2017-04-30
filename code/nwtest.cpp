#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "NeedlemanWunsch.h"
using namespace std;

int main()
{
	char* subject = new char[5];
	subject[0] = 'A';subject[1] = 'T';subject[2] = 'T'; subject[3] = 'A'; subject[4] = 'A'; 
	char* query = new char[4];
	query[0] = 'A';query[1] = 'T';query[2] = 'A';query[3] = 'A';
//	subject = {'A','A','C','A','G','T','T','A','C','C'};
//	char query[8] = {'T','A','A','G','G','T','C','A'};
	NeedlemanWunsch *nw = new NeedlemanWunsch(query,4,subject,5);
	nw->align();
	int N = nw->final_length;
	cout<<N<<endl;
	char *s = new char[N];
	char *q = new char[N];
	char *l = new char[N];
	nw->get_alignment(s,q,l);
	for(int i=0;i<N;i++){
		cout<<s[i];
	}
	cout<<endl;
	for(int i=0;i<N;i++){
		cout<<l[i];
	}
	cout<<endl;
	for(int i=0;i<N;i++){
		cout<<q[i];
	}
	cout<<endl;
	return 0;
}
