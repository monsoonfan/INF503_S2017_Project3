#pragma once

#include "HashMap.h"

class FileReader
{
public:
	FileReader();
	~FileReader();
	int ReadSubjects(char *, char *, long int, HashMap *);
	int ReadQueries(char *, char *, int);
};
