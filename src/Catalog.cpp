#include <iostream>
#include <string.h>
#include <cstdio>
#include <fstream>
#include "Catalog.h"

using namespace std;

Catalog::Catalog() {
	keycount = 0;
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
					if (strcmp(catalogitem[i].name, singlekey) == 0) {
						/*addCount(singlekey);*/
						catalogitem[i].count += 1;
						exist = 1;
					} else {
						continue;
					}
				}
				if (!exist) {
					strcpy(catalogitem[keycount].name, singlekey);
					/*strcpy(catalogitem[id].name, singlekey);*/
					catalogitem[id]._id = id;
					catalogitem[id].count += 1;
					char ktype[20];
					strcpy(catalogitem[id].type, getKeyType(singlekey, ktype));
					id++;
					keycount++;
				}

				singlekey = strtok(NULL, " ");
			}
		}
	}
	inFile.close();
}


char* Catalog::getKeyType(const char *key, char *ktype) {
	if (strncmp("num", key, sizeof("num") - 1) == 0) {
		strcpy(ktype, "Int");
		return ktype;
	} else if (strncmp("bool", key, sizeof("bool") - 1) == 0) {
		strcpy(ktype, "Bool");
		return ktype;
	} else if (strncmp("nested_obj.num", key, sizeof("nested_obj.num") - 1) == 0) {
		strcpy(ktype, "Int");
		return ktype;
	} else if (strncmp("nested_obj.str", key, sizeof("nested_obj.str") - 1) == 0) {
		strcpy(ktype, "String");
		return ktype;
	} else if (strncmp("nested_arr", key, sizeof("nested_arr") - 1) == 0) {
		strcpy(ktype, "Nested_arr");
		return ktype;
	} else if (strncmp("dyn", key, sizeof("dyn") - 1) == 0) {
		strcpy(ktype, "Dynamic");
		return ktype;
	} else if (strncmp("str", key, sizeof("str") - 1) == 0) {
		strcpy(ktype, "String");
		return ktype;
	} else if (strncmp("thousandth", key, sizeof("thousandth")- 1) == 0) {
		strcpy(ktype, "Int");
		return ktype;
	} else if (strncmp("sparse", key, sizeof("sparse") - 1) == 0) {
		strcpy(ktype, "String");
		return ktype;
	} else {
		strcpy(ktype, "Unknown");
		return ktype;
	}
}


void Catalog::outputTheCatalog() {
	ofstream outFile;
	outFile.open("./temp_files/catalog");
	if (!outFile) {
		cerr << "Can not open the outFile." << endl;
		return;
	} else {
		for (int i = 0; i < keycount; i++) {
			outFile << catalogitem[i]._id << " \t" << catalogitem[i].name << " \t"
					<< catalogitem[i].type << " \t"<< catalogitem[i].count << endl;
 		}
	}
	outFile.close();

}

Key* Catalog::returnCatalogitem() {
	return catalogitem;
}

int Catalog::returnkeyCount() {
	return keycount;
}