#include <iostream>
#include <cstring>
using namespace std;

int main() {
	char name[20];
	char str[] = "zhu";
	cin >> name;
	if (strncmp(name, str, sizeof(str) - 1) == 0) {
		cout << "good" << endl;
	}
	return 0;
}