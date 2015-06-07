// Insert Filename Function
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include "File.h"

using namespace std;

File::File() {}

File::~File() {
	inFile.close();
	outFile.close();
}

void File::insertFilename() {
	char filename[70] = "";
	cout << "Please input the file name.(relative path)" << endl;
	cin >> filename;
	inFile.open(filename);
	if (!inFile) {
		cerr << "Error happens when open the inFile." << endl;
		return;
	} else {
		cout << "Succeed in opening the inFile: " << filename << endl;
	}
}

void File::extractKeysToFile() {
	outFile.open("./temp_files/keys");
	if (!outFile) {
		cerr << "Error happens when open the outFile." << endl;
		return;
	} else if (!inFile) {
		cerr << "Error. Without inFile." << endl;
	} else {
		while (!inFile.eof()) {
			char row[1000] = "";
			/*char c;
			int index = 0;
			inFile >> c;
			while (c != '\n') {
				row[index] = c;
				index++;
				inFile >> c;
			}*/
			inFile.getline(row, 1000);
			/*cout << row << endl;*/
			if (strcmp(row, "[") == 0 || strcmp(row, "]") == 0) {
				//do nothing
			} else {

				/*char *pch;
				pch = strtok(row, "{}\"");
				
				while (pch != NULL) {
					pch = strtok(NULL, " :");
				}*/
				converse(row);
				char* pch;
				pch = strchr(row, ':');
				while (pch != NULL) {
					char key[50];
					int i = 1, j = 0;
					while (pch[i] != ' ' && pch[i] != '{') {
						key[j] = pch[i];
						i++;
						j++;
					}
					key[j] = '\0';
					converse(key);
					outFile << key << " ";
					pch = strchr(pch + 1, ':');
				}
				outFile << endl;

			}
		}
	}
}

/*ifstream File::getifstream() {
	return inFile;
}*/

/*char* File::strrev(char* str) {
	char *temp;
	int j = 0;
	for (int i = strlen(str) - 1; i >= 0; i--, j++) {
		temp[j] = str[i];
	}
	/*temp[j] = '\0';
	return temp;
}*/

char* File::converse(char *str) {
	if (*str != '\0') {
		char temp;
		char *s1 = str;
		char *s2 = str+strlen(str)-1;
		for(;s1 < s2;s1++,s2--) {
			temp = *s1;
			*s1 = *s2;
			*s2 = temp;
		}
	}
	return str;   
}

void File::extractNestedToFile() {
	outFile.open("./temp_files/nested");

	if (!outFile) {
		cerr << "Error happens when open the outFile." << endl;
		return;
	} else if (!inFile) {
		cerr << "Error. Without inFile." << endl;
	} else {


	}
}