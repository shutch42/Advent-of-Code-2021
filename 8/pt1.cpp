#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
	ifstream input;
	string code1;
	string code2;
	string digits;
	stringstream invals;
	stringstream outvals;
	int total = 0;
	input.open("input.txt");
	if(input.is_open()) {
		while(getline(input, code1, '|') && getline(input, code2, '\n')) {
			invals.str(code1);
			outvals.str(code2);
			while(outvals >> digits) {
				int count = 0;
				stringstream segments;
				segments.str(digits);
				char letter;
				while(segments >> letter) {
					count++;
				}
				if(count == 2 || count == 4 || count == 3 || count == 7) {
					total++;
				}
				cout << count << " ";
				segments.clear();
			}
			cout << endl;
			invals.clear();
			outvals.clear();
		}
	}
	else {
		exit(1);
	}
	input.close();

	cout << endl << total << endl;
	return 0;
}
