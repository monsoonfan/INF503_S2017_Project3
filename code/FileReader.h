#pragma once

#include "HashMap.h"

class FileReader
{
public:
	FileReader();
	~FileReader();
	int ReadSubjects(char *, char *, int, HashMap *);
	int ReadQueries(char *, char *, int);
};
