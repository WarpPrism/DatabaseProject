#include <iostream>
#include <string>
#include <fstream>
#include "File.h"

using namespace std;

void Introduction();
void help();
char inputCommand();
void executeCommand(char c);

int main() {
	Introduction();
	help();
	cout << "Now Please input your command.(one character)" << endl;
	char command = inputCommand();
	while (command != 'Q' && command != 'q') {
		executeCommand(command);
		command = inputCommand();
	}
	cout << endl;
	cout << "Program exits normally." << endl;
	cout << endl;
	return 0;
}

void Introduction() {
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "This is the UI of our project." << endl;
	cout << "And ..." << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl;
}

void help() {
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~Help Screen~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Available Commands:" << endl;
	cout << "'I'or'i':                    Insert Filename." << endl;
	cout << "'C'or'c':                    Check Catalog." << endl;
	cout << "'F'or'f':                    Find A = B." << endl;
	cout << "'H'or'h':                    This Help Screen" << endl;
	cout << "'Q'or'q':                    Quit The Program." << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl;
}

char inputCommand() {
	char c;
	cout << endl;
	cout << "> ";
	cin >> c;
	return c;
}

void executeCommand(char c) {
	File fileobj;

	switch (c) {
		case 'I':
		case 'i':
			cout << "OK" << endl;
			fileobj.insertFilename();
			fileobj.extractKeysToFile();
			break;
		case 'C':
		case 'c':
			cout << "OK" << endl;
			break;
		case 'F':
		case 'f':
			cout << "OK" << endl;
			break;
		case 'H':
		case 'h':
			cout << "OK" << endl;
			help();
			break;
		default:
			cout << "Command Error. ";
			cout << "Please Input Again." << endl;
			break;
	}
}
