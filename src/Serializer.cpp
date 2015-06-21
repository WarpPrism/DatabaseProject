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

		while (!keyfile.eof() && !valuefile.eof()) {
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
			if (strcmp(keyrow, "") == 0) continue;
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
					} else if (isdigit(singlevalue)) {
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

				singlevalue = strtok(NULL, " ");
			}


			/*if (count == 0) {
				cout << seria.attrNum << " ";
				for (int i = 0; i < seria.attrNum; i++) {
					cout << seria.aid[i] << " " << keytype[i] << " ";
				}
				cout << endl;
				for (int i = 0; i < seria.attrNum; i++) {
					cout << seria.offs[i] << " ";
				}
				cout << seria.len << endl;
				char a[35];
				memcpy(a, seria.data + 4, 34);
				puts(a);
			}*/

			int serianumber = generateAllSeria();
			/*int a;
			memcpy(&a, allseria, 4);
			cout << a << endl;*/
			writeBufferToFile(serianumber);


			// write Single Seria To Buffer

			/*while (!writeSeriaToBuffer(serianumber)) {
				// do nothing
			}
			p_seria = 0;*/
		}
	}
	keyfile.close();
	valuefile.close();
}

int Serializer::generateAllSeria() {
	int *pattrNum = &seria.attrNum;
	int *plen = &seria.len;
	int i = 0;
	strcpy(allseria, "");
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
	/*cout << "allseria's index: " << i << endl;*/
	if (i != 8)
		return i;
}

/*bool Serializer::writeSeriaToBuffer(int& n) {

	do {
		memcpy(Buffer + p_buff, allseria + p_seria, 1);
		p_buff++;
		p_seria++;
	} while (p_buff < 8 * 1024 && p_seria < n);

	if (p_buff < 8 * 1024 && p_seria >= n) {
		return true;
	} else if (p_buff >= 8 * 1024 && p_seria < n) {
		n = n - p_seria;
		p_buff = 0;
		writeBufferToFile();
		strcpy(Buffer, "");
		return false;
	}
}*/

void Serializer::writeBufferToFile(int serianumber) {
	FILE *pFile;
	pFile = fopen("./temp_files/Serializer", "ab+");
	if (pFile == NULL) {
		//cerr << "File:Serializer.data Error." << endl;
		fprintf(stderr, "File: Serializer Error.\n");
		exit(1);
	} else {
		/*fwrite(Buffer, 8 * 1024, 1, pFile);*/
		fwrite(allseria, serianumber, 1, pFile);
	}
	fclose(pFile);
}

void Serializer::restoreSeriaInstance(FILE *pFile) {
	rseria.attrNum = 0;
	for (int i = 0; i < 100; i++) {
		rseria.aid[i] = 0;
		rseria.offs[i] = 0;
	}
	rseria.len = 0;
	strcpy(rseria.data, "");

	//fread(&rseria, sizeof(Seria), 1, pFile);
	fread(&rseria.attrNum, 4, 1, pFile);
	for (int i = 0; i < rseria.attrNum; i++) {
		fread(&rseria.aid[i], 4, 1, pFile);
	}
	for (int i = 0; i < rseria.attrNum; i++) {
		fread(&rseria.offs[i], 4, 1, pFile);
	}
	fread(&rseria.len, 4, 1, pFile);
	fread(rseria.data, rseria.len, 1, pFile);

	/*cout << rseria.attrNum << " ";
	for (int i = 0; i < rseria.attrNum; i++) {
		cout << rseria.aid[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < rseria.attrNum; i++) {
		cout << rseria.offs[i] << " ";
	}
	cout << rseria.len << endl;*/
	/*puts(rseria.data);*/
}

void Serializer::findAequalsB() {
	char key[20] = "";
	char value[70] = "";
	int keyid = -1;
	int index = -1;
	char type[20];
	cout << endl;
	cout << "Now please input the keyname A: ";
	cin >> key;
	cout << "Then input the value B: ";
	cin >> value;

	for (int i = 0; i < catalogcount; i++) {
		if (strcmp(catalog[i].name, key) == 0) {
			keyid = catalog[i]._id;
			strcpy(type, catalog[i].type);
			//cout << "keyid: " << keyid << endl;
			break;
		} else {
			continue;
		}
 	}
 	if (keyid == -1) {
 		cout << "This Key doesn't exsit." << endl;
 	}


	FILE *pFile;
	pFile = fopen("./temp_files/Serializer", "rb");
	if (pFile == NULL) {
		fprintf(stderr, "Can't read file Serializer.\n");
	} else {
		fseek(pFile,0,SEEK_SET);
		restoreSeriaInstance(pFile);

		while(!feof(pFile)) {
			// Binary Search
			for (int i = 0; i < rseria.attrNum; i++) {
				if (rseria.aid[i] == keyid) {
					index = i;
					//cout << "index: " << index << endl;
				} else {
					continue;
				}
			}

			int start = rseria.offs[index];

			int end = rseria.offs[index + 1];
			if (index == rseria.attrNum - 1) {
				end = rseria.len;
			} else {
				end = rseria.offs[index + 1];
			}
			int size = end - start;

			if (isdigit(value)) {
				int snum = atoi(value);
				int dnum;
				memcpy(&dnum, rseria.data + start, size);
				if (snum == dnum) {
					//cout << "Succeed!" << endl;
					restoreRseriaToJson();
				}
			} else if (strcmp(value, "true") == 0) {
				strcpy(value, "");
				strcpy(value, "t");
				char dest[1];
				memcpy(dest, rseria.data + start, size);
				if (strcmp(dest, value) == 0) {
					//cout << "Succeed!" << endl;
					restoreRseriaToJson();
					strcpy(value, "");
					strcpy(value, "true");
				}
			} else if (strcmp(value, "false") == 0) {
				strcpy(value, "");
				strcpy(value, "f");
				char dest[1];
				memcpy(dest, rseria.data + start, size);
				if (strcmp(dest, value) == 0) {
					cout << "Succeed!" << endl;
					restoreRseriaToJson();
					strcpy(value, "");
					strcpy(value, "false");
				}
			} else {
				if (value[0] == '"') {
				} else {
					strcat(value, "\"");
					for (int i = strlen(value) - 1; i >= 0; i--) {
						value[i + 1] = value[i];
					}
					value[0] = '"';
				}
			}
			restoreSeriaInstance(pFile); // segmentation fault!!!

		}
		fclose(pFile);
	}
}

bool Serializer::isdigit(char *str) {
	bool result = true;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] < '0' || str[i] > '9') {
			result = false;
			break;
		} else {
			continue;
		}
	}
	return result;
}

bool Serializer::recursive_binary_2(int the_vector[], const int &target, int bottom, int top, int &position) {
	if (bottom <= top) {
		int mid = (bottom + top) / 2;
		if (the_vector[mid] == target) {
			position = mid;
		    //cout << position << endl;
			return true;
		}
		if (the_vector[mid] > target) {
			return recursive_binary_2(the_vector, target, bottom, mid - 1, position);
		}
		if(the_vector[mid] < target) {
			return recursive_binary_2(the_vector, target, mid + 1, top, position);
		}
	} else {
		return false;
	}
}

void Serializer::restoreRseriaToJson() {
	cout << "{";
	for (int i = 0; i < rseria.attrNum; i++) {
		char type[20];
		for (int j = 0; j  < catalogcount; j++) {
			if (rseria.aid[i] == catalog[j]._id) {
				cout << "\"" << catalog[j].name << "\": ";
				strcpy(type, catalog[j].type);

			}
		}
		int start = rseria.offs[i];
		int end = rseria.offs[i + 1];
		if (i == rseria.attrNum - 1) {
			end = rseria.len;
		} else {
			end = rseria.offs[i + 1];
		}
		int size = end - start;
		/*if (i = rseria.attrNum - 1) {
			end = rseria.len;
		} else {
			end = rseria.offs[i + 1];
		}*/
		if (strcmp(type, "Int") == 0) {
			int dest;
			memcpy(&dest, rseria.data + start, size);
			cout << dest << ", ";
		} else if (strcmp(type, "Bool") == 0) {
			char dest[1];
			memcpy(dest, rseria.data + start, size);
			/*dest[strlen(dest)] = '\0';
			cout << dest << endl;*/
			if (strncmp(dest, "t", 1) == 0) {
				cout << "true" << ", ";
			} else if (strncmp(dest, "f", 1) == 0) {
				cout << "false" << ", ";
			}
		} else if (strcmp(type, "String") == 0) {
			char dest[100];
			strncpy(dest, rseria.data + start, size);
			for (int k = 0; k < strlen(dest); k++) {
				cout << dest[k];
				if (dest[k] == '"' && k != 0) {
					break;
				}
			}
			strcpy(dest, "");
			if (i != rseria.attrNum - 1)
				cout << ", ";
		} else if (strcmp(type, "Nested_arr") == 0) {
			char dest[150];
			strncpy(dest, rseria.data + start, size);
			for (int k = 0; k < strlen(dest); k++) {
				cout << dest[k];
				if (dest[k] == ']' && k != 0) {
					break;
				}
			}
			strcpy(dest, "");
			if (i != rseria.attrNum - 1)
				cout << ", ";
		}
		/* else if (strcmp(type, "Dynamic") == 0) {
		} else if (strcmp(type, "Unknown") == 0) {
		}*/
	}
	cout << "}" << endl;
}

void Serializer::TATfind() {
	char key[20];
	char value[100];
	int keyid = -1;
	cout << endl;
	cout << "Notice: If you want to query nested object, just using the pointer separator." << endl;
	cout << "For example: nested_obj.num, nested_obj.str " << endl;
	cout << "Now please input the keyname A: ";
	cin >> key;
	cout << "Notice: If the key is string, please include it in a pair of quotation marks." << endl;
	cout << "For example: find nested_obj.str = \"GBRDCMBQGA======\" " << endl;
	cout << "Then input the value B: ";
	cin >> value;
	/*if (value[0] == '"') {
	} else {
		strcat(value, "\"");
		for (int i = strlen(value) - 1; i >= 0; i--) {
			value[i + 1] = value[i];
		}
		value[0] = '"';
	}*/

	for (int i = 0; i < catalogcount; i++) {
		if (strcmp(catalog[i].name, key) == 0) {
			keyid = catalog[i]._id;
			break;
		}
 	}
 	if (keyid == -1) {
 		cout << "This Key doesn't exsit." << endl;
 		return;
 	}
 	ifstream keyfile;
	ifstream valuefile;
	
	keyfile.open("./temp_files/keys");
	valuefile.open("./temp_files/values");
	
	if (!keyfile) {
		//cerr << "Error happens when opening the temp_files/keys." << endl;
		return;
	} else if (!valuefile) {
		//cerr << "Error happens when opening the temp_files/values." << endl;
	} else {
		int rowindex = 1;
		int flag = 1;
		while (!keyfile.eof() && !valuefile.eof()) {
			char keyrow[500];
			char valuerow[1000];
			keyfile.getline(keyrow, 500);
			valuefile.getline(valuerow, 1000);
			if (strcmp(keyrow, "") == 0) {
				rowindex++;
				continue;
			}
			char *singlekey;
			char *singlevalue;
			char keys[90][20];
			char values[90][100];

			singlekey = strtok(keyrow, " ");
			int i = 0;
			while (singlekey != NULL) {
				strcpy(keys[i], singlekey);
				
				i++;
				singlekey = strtok(NULL, " ");
			}

			singlevalue = strtok(valuerow, " ");
			int j = 0;
			while (singlevalue != NULL) {
				strcpy(values[j], singlevalue);
				j++;
				singlevalue = strtok(NULL, " ");
			}

			for (int i = 0; i < 90; i++) {
				if (strcmp(key, keys[i]) == 0 && strcmp(value, values[i]) == 0) {
					flag = 0;
					printJson(rowindex);
					break;
				}
			}

			rowindex++;
		}
		if (flag)
			cout << "Sorry we find nothing." << endl;
	}
	keyfile.close();
	valuefile.close();
}

void Serializer::printJson(int rowindex) {
	ifstream json;
	json.open(filename);
	if (!json) {
		//cerr << "Error happens when opening json file." << endl;
		return;
	}
	int i = 1;
	while (!json.eof()) {
		char row[1200];
		json.getline(row, 1200);
		if (i == rowindex + 1) {
			puts(row);
			break;
		} else {
			i++;
		}
	}
	json.close();
}

void Serializer::getFilename(char *source) {
	strcpy(filename, source);
}