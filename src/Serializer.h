#ifndef SERIALIZER_H
#define SERIALIZER_H
#include "Catalog.h"

typedef struct {
	int attrNum;
	int aid[100];
	int offs[100];
	int len;
	char data[2048];
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
	// write the first part of seria to file
	void writeFirstPartToFile();
	// write the second part of seria to file
	void writeSecondPartToFile();
	

private:
	Seria seria;
	Key* catalog;
	int catalogcount;
	char Buffer[page_size + 1];
};

#endif
