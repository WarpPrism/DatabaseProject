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
	cout << "Please input the file name.(relative path)" << endl;
	cin >> filename;
	inFile.open(filename);
	if (!inFile) {
		cerr << "Error happens when open the inFile." << endl;
		exit(1);
		return;
	} else {
		cout << "\t---> Succeed in opening the inFile: " << filename << endl;
	}
}

void File::extractKeysToFile() {
	outFile.open("./temp_files/keys");
	if (!outFile) {
		cerr << "Error happens when opening the outFile." << endl;
		return;
	} else if (!inFile) {
		cerr << "Error. Without inFile.(key process)" << endl;
		return;
	} else {
		while (!inFile.eof()) {
			char row[1000] = "";
			inFile.getline(row, 1000);
			char conversearray[100][110];
			int conversecount = 0;
			/*cout << row << endl;*/
			if (strcmp(row, "[") == 0 || strcmp(row, "]") == 0 || strcmp(row, "") == 0 || strlen(row) < 5) {
				//do nothing
			} else {
				dealwithNestedobj(row);
				converse(row);
				char* pch;
				pch = strchr(row, ':');
				while (pch != NULL) {
					char key[50];
					int i = 1, j = 0;
					while (pch[i] != ' ' && pch[i] != '{') {
						if (pch[i] == '"') {
							i++;
							continue;
						}
						key[j] = pch[i];
						i++;
						j++;
					}
					key[j] = '\0';
					converse(key);
					if (strcmp("nested_obj", key) == 0) {
						// do nothing
					} else {
						strcpy(conversearray[conversecount], key);
						conversecount++;
					}
					pch = strchr(pch + 1, ':');
				}
				for (int k = conversecount - 1; k > 0; k--) {
					outFile << conversearray[k] << " ";
				}
				outFile << conversearray[0] << endl;

			}
		}
	}
	outFile.close();
}

/*ifstream File::getifstream() {
	return inFile;
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
		return;
	} else {
		
	}
}

void File::dealwithNestedobj(char *row) {
	char * lbrace;
	char * rbrace;
	rbrace = strchr(row, '}');
	lbrace = strchr(row, '{');
	lbrace = strchr(lbrace + 1, '{');
	char *quo;
	quo = strchr(lbrace, '"');
	if (rbrace - quo < 0) {
		return;
	} else {
		while (quo != NULL) {
			//puts(quo);
			char *start = quo + 1;
			shiftRAndInsert(start);
			quo = strchr(quo + 1, '"');
			rbrace = strchr(row, '}');
			if (rbrace - quo < 0) {
				return;
			}
			quo = strchr(quo + 1, '"');
			rbrace = strchr(row, '}');
			if (rbrace - quo < 0) {
				return;
			}
		}
	}
}

void File::shiftRAndInsert(char *start) {
	if (start == NULL) {
		cerr << "Pointer Error." << endl;
	} else {
		for (int i = strlen(start); i > 0; i--) {
			start[i + 10] = start[i - 1];
		}
		start[0] = 'n';
		start[1] = 'e';
		start[2] = 's';
		start[3] = 't';
		start[4] = 'e';
		start[5] = 'd';
		start[6] = '_';
		start[7] = 'o';
		start[8] = 'b';
		start[9] = 'j';
		start[10] = '.';
	}
	//puts(start);
}

void File::extractValuesToFile() {
	inFile.close();
	inFile.open(filename);
	outFile.open("./temp_files/values");
	if (!outFile) {
		cerr << "Error happens when opening the outFile." << endl;
		return;
	} else if (!inFile) {
		cerr << "Error. Without inFile.(value process)" << endl;
		return;
	} else {
		while (!inFile.eof()) {

			char row[1000];
			inFile.getline(row, 1000);
			if (strlen(row) < 5) {
				//do nothing
			} else {
				char *colon;
				colon = strchr(row, ':');
				while (colon != NULL) {
					char value[50] = "";
					colon += 2;
					if (colon[0] == '{') {
						//donothing
					} else if (colon[0] == '[') {
						// nested array
						strcpy(value, "");
						for (int i = 0, j = 0; i < strlen(colon); i++) {
							if (colon[i] == ' ') {
								//
							} else if (colon[i] != ']') {
								value[j] = colon[i];
								j++;
							} else if (colon[i] == ']') {
								value[j] = colon[i];
								value[j + 1] = '\0';
								break;
							}
						}
						outFile << value << " ";
					} else {
						strcpy(value, "");
						for (int i = 0, j = 0; i < strlen(colon); i++, j++) {
							if (colon[i] == ',' || colon[i] == '}') {
								value[j] = '\0';
								break;
							} else {
								value[j] = colon[i];
							}
						}
						outFile << value << " ";
					}

					colon = strchr(colon, ':');
				}
				outFile << endl;
			}
			
		}
	}
	inFile.close();
	outFile.close();
}