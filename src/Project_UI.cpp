#include <iostream>
#include <string>
#include <fstream>
#include "File.h"
#include "Catalog.h"
#include "Serializer.h"

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
	cout << "> Hello. Welcome to our DB Project." << endl;
	cout << "> And the first thing you should do is to insert a file." << endl;
	cout << "> And if you want to insert a new file, please make clean first." << endl;
	cout << "> You can type command 'i' to start inserting a file. eg: nobench_data.json." << endl;
	cout << "> After that you can check the catalog or find A = B." << endl;
	cout << "> And if you find some bugs during using this program, just forgive us." << endl;
	cout << "> We feel sorry for our mistakes." << endl;
	cout << "> Hope you enjoy using it! :)" << endl;
	cout << ">" << endl;
	cout << "         niwe            gpod            " << endl;
	cout << "      sqstruesdq      jvswarmqwe         " << endl;
	cout << "     ogivemepassideslonmayigetint        " << endl;
	cout << "     woyourheartbewygarlsrigndokw        " << endl;
	cout << "     eijustwanttobeyoursideandgir        " << endl;
	cout << "      rvemewhatihaveletusstepint         " << endl;
	cout << "       jtusdfcvghjdfgasdfgvfert          " << endl;
	cout << "        vsasdwvbcaniowwyourhea           " << endl;
	cout << "         byouarebeautifulrigh            " << endl;
	cout << "          dtvbhfransfesgniet             " << endl;
	cout << "            cdqwesdvfgansd               " << endl;
	cout << "              eswasdwssd                 " << endl;
	cout << "                 ader                    " << endl;
	cout << "                  y                      " << endl;
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
	Catalog catalogobj;
	Serializer serializerobj;

	switch (c) {
		case 'I':
		case 'i':
			cout << "Command OK" << endl;
			fileobj.insertFilename();
			/*cout << endl << "\tInformation:" << endl;*/
			cout << "\t---> Insert File Completed!" << endl;
			fileobj.extractKeysToFile();
			cout << "\t---> Extract Keys To File Completed!" << endl;
			fileobj.extractValuesToFile();
			cout << "\t---> Extract Values To File Completed!" << endl;

			catalogobj.generateCatalogDatas();
			cout << "\t---> Generate Catalog Datas Completed!" << endl;
			catalogobj.outputTheCatalog();
			cout << "\t---> Output Catalog Completed!" << endl;

			serializerobj.getTheCatalogitem(catalogobj.returnCatalogitem());
			serializerobj.getCatlogcount(catalogobj.returnkeyCount());
			cout << "\t---> Serializer Gets The Catalog Completed!" << endl;
			serializerobj.generateSeria();
			serializerobj.getFilename(fileobj.returnFilename());
			cout << "\t---> Generate Serialized Data Completed!" << endl;
			cout << "Now you can check the catalog or find A = B." << endl;
			break;
		case 'C':
		case 'c':
			cout << "Command OK" << endl;
			cout << "You can open \"./temp_files/catalog\" to check the Catalog." << endl;
			cout << "Also you can see it in the terminal." << endl;
			cout << "Show On Screen? Y/N? " << endl;
			char show;
			cin >> show;
			if (show == 'y' || show == 'Y')
				catalogobj.printCatalogOnScreen();
			else if (show == 'n' || show == 'N')
				cout << "OK, The screen will not show catalog. Please check the file." << endl;
			cout << "Thank you!" << endl;
			break;
		case 'F':
		case 'f':
			cout << "Command OK" << endl;
			//serializerobj.findAequalsB();
			serializerobj.TATfind();
			break;
		case 'H':
		case 'h':
			cout << "Command OK" << endl;
			help();
			break;
		default:
			cout << "Command Error. ";
			cout << "Please Input Again." << endl;
			break;
	}
}
