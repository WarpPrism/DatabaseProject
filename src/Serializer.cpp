#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Serializer.h"

using namespace std;

Serializer::Serializer() {}

Serializer::~Serializer() {}

void Serializer::getTheCatalogitem(Key* source) {
	catalog = source; 
}

void Serializer::getCatlogcount(int source) {
	catalogcount = source;
}

void Serializer::generateSeria() {
	ifstream inFile;
	inFile.open("./temp_files/keys");
	if (!inFile) {
		cerr << "Error happens when opening the temp_files/keys." << endl;
		return;
	} else {
		while (!inFile.eof()) {
			seria->attrNum = 0;
			char row[500];
			inFile.getline(row, 500);
			char *singlekey;
			singlekey = strtok(row, " ");
			while (singlekey != NULL) {
				for (int i = 0; i < catalogcount; i++) {
					if (strcmp(catalog[i].name, singlekey) == 0) {
						seria->aid[seria->attrNum] = catalog[i]._id;
						seria->attrNum++;
					} else {
						continue;
					}
 				}

 				singlekey = strtok(NULL, " ");
			}
		}
	}
}
