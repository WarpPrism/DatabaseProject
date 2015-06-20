#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "Serializer.h"

using namespace std;

Serializer::Serializer() {
	p_seria = 0;
	p_buff = 0;
}

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

			// key process, attrNum, _id
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

			
			// value process, offs, len, data
			int offindex = 0;
			seria.len = 0;
			singlevalue = strtok(valuerow, " ");
			int j = 0;
			typeindex = 0;
			while (singlevalue != NULL) {
				seria.offs[offindex] = seria.len;
				offindex++;

				if (strcmp(keytype[typeindex], "Int") == 0) {
					int num;
					num = atoi(singlevalue);
					int *pnum = &num;
					seria.len += 4;
					memcpy(seria.data + j, pnum, sizeof(int));
					j += 4;
				} else if (strcmp(keytype[typeindex], "Bool") == 0) {
					seria.len += 1;
					memcpy(seria.data + j, singlevalue + 0, 1);
					j += 1;
				} else if (strcmp(keytype[typeindex], "String") == 0) {
					seria.len += strlen(singlevalue);
					memcpy(seria.data + j, singlevalue, strlen(singlevalue));
					j += strlen(singlevalue);
				} else if (strcmp(keytype[typeindex], "Nested_arr") == 0) {
					seria.len += strlen(singlevalue);
					memcpy(seria.data + j, singlevalue, strlen(singlevalue));
					j += strlen(singlevalue);
				} else if (strcmp(keytype[typeindex], "Dynamic") == 0) {
					if (strcmp(singlevalue, "true") == 0 || strcmp(singlevalue, "false") == 0) {
						seria.len += 1;
						memcpy(seria.data + j, singlevalue + 0, 1);
						j += 1;
					} else if (singlevalue[0] == '"') {
						seria.len += strlen(singlevalue);
						memcpy(seria.data + j, singlevalue, strlen(singlevalue));
						j += strlen(singlevalue);
					} else {
						int num;
						num = atoi(singlevalue);
						int *pnum = &num;
						seria.len += 4;
						memcpy(seria.data + j, pnum, sizeof(int));
						j += 4;
					}
				} else if (strcmp(keytype[typeindex], "Unknown") == 0) {
					seria.len += strlen(singlevalue);
					memcpy(seria.data + j, singlevalue, strlen(singlevalue));
					j += strlen(singlevalue);
				}
				typeindex++;


				/*for (int i = 0; i < strlen(singlevalue); i++, j++) {
					if (strcmp(singlevalue, "true") == 0) {
						seria.data[j] = 't';
						j++;
						break;
					} else if (strcmp(singlevalue, "false") == 0) {
						seria.data[j] = 'f';
						j++;
						break;
					}
					seria.data[j] = singlevalue[i];
				}*/
				singlevalue = strtok(NULL, " ");
			}
			/*seria.data[j] = '\0';*/


			/*if (count == 2) {
				cout << seria.attrNum << " ";
				for (int i = 0; i < seria.attrNum; i++) {
					cout << seria.aid[i] << " " << keytype[i] << " ";
				}
				cout << endl;
				for (int i = 0; i < seria.attrNum; i++) {
					cout << seria.offs[i] << " ";
				}
				cout << seria.len << endl;
				puts(seria.data);
			}*/

			int serianumber = generateAllSeria();

			// write Single Seria To Buffer
			
			if(writeSeriaToBuffer(serianumber)) {
				p_seria = 0;
			} else {
				continue;
			}
count++;
		}
	}
}

int Serializer::generateAllSeria() {
	int *pattrNum = &seria.attrNum;
	int *plen = &seria.len;
	int i = 0;
	memcpy(allseria + i, pattrNum, sizeof(int));
	i += sizeof(int);
	for (int j = 0; j < seria.attrNum; j++) {
		int *pid = &seria.aid[j];
		memcpy(allseria + i, pid, sizeof(int));
		i += sizeof(int);
	}
	for (int j = 0; j < seria.attrNum; j++) {
		int *poffs = &seria.offs[j];
		memcpy(allseria + i, poffs, sizeof(int));
		i += sizeof(int);
	}
	memcpy(allseria + i, plen, sizeof(int));
	i += sizeof(int);
	memcpy(allseria + i, seria.data, seria.len);
	i += seria.len;
	return i;
	//cout << "allseria's index: " << i << endl;}
}

bool Serializer::writeSeriaToBuffer(int n) {
	do {
		memcpy(Buffer + p_buff, allseria + p_seria, 1);
		p_buff++;
		p_seria++;
	} while (p_buff < 8 * 1024 && p_seria < n);
	if (p_buff < 8 * 1024) {
		return true;
	} else {
		p_buff = 0;
		writeBufferToFile();
		return false;
	}
}

void Serializer::writeBufferToFile() {
	FILE *pFile;
	pFile = fopen("./temp_files/Serializer", "ab+");
	if (pFile == NULL) {
		//cerr << "File:Serializer.data Error." << endl;
		fprintf(stderr, "File: Serializer Error.\n");
		exit(1);
	} else {
		fwrite(Buffer, 8 * 1024, 1, pFile);
	}
	fclose(pFile);
}
