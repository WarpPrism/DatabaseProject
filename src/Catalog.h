#ifndef CATALOG_H
#define CATALOG_H

using namespace std;

typedef struct {
	int _id;
	char name[20];
	char type[20];
	int count;
} Key;

/*typedef struct {
	char name[20];
} Keymap;*/

class Catalog {
public:
	Catalog();
	~Catalog();
	void generateCatalogDatas();
	char* getKeyType(char* key);
	void printTableOnScreen();
	void addCount(char *singlekey);


private:
	Key keystructarray[200];
	/*Keymap keymap[200];*/
	int keycount;
};

#endif
