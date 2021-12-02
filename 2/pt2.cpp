#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream input;
	int num;
	int x = 0;
	int y = 0;
	int aim = 0;
	string direction;
	input.open("input.txt");
	if(input.is_open()) {
		while(input >> direction && input >> num) {
			if(direction == "forward") {
				x += num;
				y += aim*num;
			}
			if(direction == "down") {
				aim += num;
			}
			if(direction == "up") {
				aim -= num;
			}
		}
	}
	else {
		exit(1);
	}
	input.close();
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
	cout << "x*y: " << x*y << endl;
	return 0;
}
