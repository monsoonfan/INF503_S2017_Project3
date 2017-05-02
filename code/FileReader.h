#pragma once

class FileReader
{
public:
	FileReader();
	~FileReader();
	int ReadSubjects(char *, char *, int);
	int ReadQueries(char *, char *, int);
};
