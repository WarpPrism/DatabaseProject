#ifndef CATALOG_H
#define CATALOG_H

using namespace std;

typedef struct key {
	int _id;
	char name[20];
	char type[20];
	int count;
} Key;

class Catalog {
public:
	Catalog();
	void printTableOnScreen();

private:
	Key keysarray[200];
};

#endif
