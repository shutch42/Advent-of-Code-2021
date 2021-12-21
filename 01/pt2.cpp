#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream input;
	int num1;
	int num2;
	int num3;
	int read;
	int sum1;
	int sum2;
	int count = 0;
	input.open("input.txt");
	if(input.is_open()) {
		input >> num1;
		input >> num2;
		input >> num3;
		sum1 = num1 + num2 + num3;
	}
	else {
		exit(1);
	}
	while(input >> read) {
		num1 = num2;
		num2 = num3;
		num3 = read;
		sum2 = num1 + num2 + num3;
		if(sum2 > sum1) {
			count++;
		}
		sum1 = sum2;
	}
	input.close();
	cout << "Total: " << count << endl;
	return 0;
}
