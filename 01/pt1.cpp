#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream input;
	int num1;
	int num2;
	int count = 0;
	input.open("input.txt");
	if(input.is_open()) {
		input >> num1;
	}
	else {
		exit(1);
	}
	while(input >> num2) {
		if(num2 > num1) {
			count++;
		}
		num1 = num2;
	}
	input.close();
	cout << "Total: " << count << endl;
	return 0;
}
