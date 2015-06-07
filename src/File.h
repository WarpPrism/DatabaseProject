#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

using namespace std;

class File {
public:
	File();
	~File();
	void insertFilename();
	void extractKeysToFile();
	void extractNestedToFile();
	ifstream getifstream();

	char* converse(char *str);

private:
	ifstream inFile;
	ofstream outFile;
};

#endif
