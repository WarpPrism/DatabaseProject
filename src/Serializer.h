#ifndef SERIALIZER_H
#define SERIALIZER_H
#include "Catalog.h"

typedef struct {
	int attrNum;
	int aid[100];
	int offs[100];
	int len;
	char data[4096];
} Seria;

const int page_size = 8 * 1024;

class Serializer {

public:
	Serializer();
	~Serializer();
	// get the catalog data
	void getTheCatalogitem(Key* source);
	// get the count of catalog items
	void getCatlogcount(int source);
	// generate serialized data
	void generateSeria();
	// generate allseria
	int generateAllSeria();
	// write Single Seria To Buffer
	bool writeSeriaToBuffer(int& n);
	// write Buffer to ./temp_files/Serializer.data
	void writeBufferToFile(int serianumber);
	// restore and generate a Seria instance
	void restoreSeriaInstance(FILE *pFile); 
	// find A = B
	void findAequalsB();
	// judge if a string is a number
	bool isdigit(char *str);

	bool recursive_binary_2(int the_vector[], const int &target, int bottom, int top, int &position);

	// restore rseria to json
	void restoreRseriaToJson();
	
	// TAT find
	void TATfind();
	void printJson(int rowindex);
	void getFilename(char *source);

private:
	Seria seria;
	Seria rseria;
	Key* catalog;
	char filename[70];
	int catalogcount;
	char allseria[1500];
	char Buffer[page_size];
	int p_seria;
	int p_buff;
};

#endif
