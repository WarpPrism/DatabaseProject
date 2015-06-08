#include <iostream>
#include <string.h>
#include <cstdio>
#include <fstream>
#include "Catalog.h"

using namespace std;

Catalog::Catalog() {
	keycount = 0;
	//initial keymap
/*	keycount = 0;
	for (int i = 0; i < 200; i++) {
		strcpy(keymap[i].name, "");
	}*/

}
Catalog::~Catalog() {}

void Catalog::generateCatalogDatas() {


	ifstream inFile;
	inFile.open("temp_files/keys");

	if (!inFile) {
		cerr << "Error happens when open the inFile." << endl;
		return;
	} else {
		int id = 0;
		while (!inFile.eof()) {
			char row[500];
			inFile.getline(row, 500);
			char *singlekey;
			
			singlekey = strtok(row, " ");
			//puts(singlekey);
			while (singlekey != NULL) {
				int exist = 0;
				for (int i = 0; i < keycount; i++) {
					if (strcmp(keystructarray[i].name, singlekey) == 0) {
						/*addCount(singlekey);*/
						keystructarray[i].count += 1;
						exist = 1;
					} else {
						continue;
					}
				}
				if (!exist) {
					strcpy(keystructarray[keycount].name, singlekey);
					/*strcpy(keystructarray[id].name, singlekey);*/
					keystructarray[id]._id = id;
					keystructarray[id].count += 1;
					//type
					id++;
					keycount++;
				}

				singlekey = strtok(NULL, " ");
			}
		}
	}
	inFile.close();
}

char* Catalog::getKeyType(char* key) {

}

void Catalog::printTableOnScreen() {
	ofstream outFile;
	outFile.open("./temp_files/catalog");
	if (!outFile) {
		cerr << "Can not open the outFile." << endl;
		return;
	} else {
		for (int i = 0; i < keycount; i++) {
			outFile << keystructarray[i]._id << " \t\t" << keystructarray[i].name << " \t\t"
					<< keystructarray[i].count << endl;
 		}
	}
	outFile.close();

}

/*void Catalog::addCount(char *singlekey) {
	for (int i = 0; i < keycount; i++) {
		if (strcpy(keystructarray[i].name, singlekey) == 0) {
			keystructarray[i].count += 1;
		} else {
			continue;
		}
	}
}*/