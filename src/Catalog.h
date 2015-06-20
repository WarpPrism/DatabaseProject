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
	// generate catalog datas rely on ./temp_files/keys
	void generateCatalogDatas();
	// get key type according to the original data.
	char* getKeyType(const char *key, char *ktype);
	// check catalog, print the catalog on the screen in table.
	// Also output it to temp_files/catalog
	void outputTheCatalog();
	void printCatalogOnScreen();
	// return catalogitem for the serializer
	Key* returnCatalogitem();
	// return keycount
	int returnkeyCount();


private:
	Key catalogitem[2000];
	/*Keymap keymap[200];*/
	int keycount;
};

#endif
