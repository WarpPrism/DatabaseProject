#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
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
	ifstream keyfile;
	ifstream valuefile;
	keyfile.open("./temp_files/keys");
	valuefile.open("./temp_files/values");
	if (!keyfile) {
		cerr << "Error happens when opening the temp_files/keys." << endl;
		return;
	} else if (!valuefile) {
		cerr << "Error happens when opening the temp_files/values." << endl;
	} else {
int count = 0;

		while (!keyfile.eof() && !valuefile.eof()) {
/*cout << "^_^" << endl;
cout << count << endl;*/
			seria.attrNum = 0;
			for (int i = 0; i < 100; i++) {
				seria.aid[i] = 0;
				seria.offs[i] = 0;
			}
			seria.len = 0;
			strcpy(seria.data, "");

			char keyrow[500];
			char valuerow[1000];
			keyfile.getline(keyrow, 500);
			valuefile.getline(valuerow, 1000);
			char *singlekey;
			char *singlevalue;
			// keytype temp array.
			char keytype[70][20];
			int typeindex = 0;


			singlekey = strtok(keyrow, " ");
			while (singlekey != NULL) {
				for (int i = 0; i < catalogcount; i++) {
					if (strcmp(catalog[i].name, singlekey) == 0) {
						seria.aid[seria.attrNum] = catalog[i]._id;
						seria.attrNum++;
						strcpy(keytype[typeindex], catalog[i].type);
						typeindex++;
					} else {
						continue;
					}
 				}
 				singlekey = strtok(NULL, " ");
			}

			
			int offindex = 0;
			seria.len = 0;
			singlevalue = strtok(valuerow, " ");
			int j = 0;
			while (singlevalue != NULL) {
				seria.offs[offindex] = seria.len;

				offindex++;
				
				seria.len += strlen(singlevalue);

				for (int i = 0; i < strlen(singlevalue); i++, j++) {
					seria.data[j] = singlevalue[i];
				}
				singlevalue = strtok(NULL, " ");
			}
			/*seria.data[j] = '\0';*/


			if (count == 2) {
				cout << seria.attrNum << " ";
				for (int i = 0; i < typeindex; i++) {
					cout << seria.aid[i] << " ";
				}
				cout << endl;
				for (int i = 0; i < typeindex; i++) {
					cout << seria.offs[i] << " ";
				}
				cout << seria.len << endl;
				puts(seria.data);
			}

			writeSeriaToBuffer();
count++;
		}
	}
}

void Serializer::writeSeriaToBuffer() {
	char *pbuff = Buffer;

}

void writeBufferToFile() {
	FILE *pFile;
	pFile = fopen("./temp_files/Serializer.data", "wb");
	if (pFile == NULL) {
		//cerr << "File:Serializer.data Error." << endl;
		fprintf(stderr, "File: Serializer.data Error.\n");
		exit(1);
	} else {

	}	
}
