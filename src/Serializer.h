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
	bool writeSeriaToBuffer(int n);
	// write Buffer to ./temp_files/Serializer.data
	void writeBufferToFile();
	

private:
	Seria seria;
	Key* catalog;
	int catalogcount;
	char allseria[1500];
	char Buffer[page_size];
	int p_seria;
	int p_buff;
};

#endif
