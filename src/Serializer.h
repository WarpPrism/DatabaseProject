#ifndef SERIALIZER_H
#define SERIALIZER_H
#include "Catalog.h"

typedef struct {
	int attrNum;
	int aid[100];
	int offs[100];
	int len;
	char data[1000];
} Seria;


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
	void writeSeriaToFile();
	

private:
	Seria* seria;
	Key* catalog;
	int catalogcount;
};

#endif
