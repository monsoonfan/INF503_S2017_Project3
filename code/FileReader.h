#pragma once

class FileReader
{
public:
	FileReader();
	~FileReader();
	int nextC(FILE* fa);
	int PreProcessSubjects(char*, char*, int);
	int PreProcessQueries(char*, char*, int);
	int ReadSubjects(char *, char *, int);
	int ReadQueries(char *, char *, int);
};
