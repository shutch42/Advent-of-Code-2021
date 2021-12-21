#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

int bitsToNum(string bits) {
	int sum = 0;
	for(int i = 0; i < 12; i++) {
		sum += (bits.at(11-i) - '0') * pow(2,i);
	}
	return sum;
}

int main() {
	char bit;
	int count1s[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	int count0s[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	int total = 0;
	string gamma = "";
	string epsilon = "";
	ifstream input;
	input.open("input.txt");
	if(input.is_open()) {
		while(input >> bit) {
			(bit == '1') ? count1s[0] += 1 : count0s[0] += 1;
			for(int i = 1; i < 12; i++) {
				input >> bit;
				(bit == '1') ? count1s[i] += 1 : count0s[i] += 1;
			}
			total++;
		}
	}
	else {
		cerr << "Error opening file" << endl;
		exit(1);
	}
	input.close();
	for(int i = 0; i < 12; i++) {
		cout << i << ": " << count1s[i] << " ones, " << count0s[i] << " zeros" << endl;
	}
	for(int i = 0; i < 12; i++) {
		if(count1s[i] > total/2) {
		       gamma += "1";
		       epsilon += "0";
		}
	        else {
			gamma += "0";
			epsilon += "1";
		}
	}
	int gammaNum = bitsToNum(gamma);
	int epsilonNum = bitsToNum(epsilon);
	cout << "Gamma: " << gamma << ", " << gammaNum << endl;
	cout << "Epsilon: " << epsilon << ", " << epsilonNum << endl;
	cout << "Power Consumption: " << gammaNum * epsilonNum << endl;
	return 0;
}
