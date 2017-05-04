#pragma once

#include "HashMap.h"

class FileReader
{
public:
	FileReader();
	~FileReader();
	int ReadSubjects(char *, char *, unsigned int, HashMap *);
	int ReadQueries(char *, char *, int);
};
