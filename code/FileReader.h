#pragma once

class FileReader
{
public:
	FileReader();
	~FileReader();
	int nextC(FILE* fa);
	int ReadSubjects(char *, char *, int);
	int ReadQueries(char *, char *, int);
};
