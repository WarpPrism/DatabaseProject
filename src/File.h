#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

using namespace std;

class File {
public:
	File();
	~File();
	// Open the file to be delalt with
	void insertFilename();
	// extract all keys in .json to temp_files/keys
	void extractKeysToFile();
	// extract all nested things to /temp_files/nested
	void extractNestedArrToFile();
	// deal with nested obj
	void dealwithNestedobj(char *row);
	// shift
	void shiftRAndInsert(char *start);
	// conver a string
	char* converse(char *str);
	// extract values to /temp_files/values
	void extractValuesToFile();

	char* returnFilename();

private:
	char filename[70];
	ifstream inFile;
	ofstream outFile;
};

#endif
