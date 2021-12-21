#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int total;

void display(int octopi[10][10][2]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			cout << octopi[i][j][0];
		}
		cout << endl;
	}
}

void iterate(int octopi[10][10][2]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			(octopi[i][j][0])++;
		}
	}
}

void flash(int octopi[10][10][2]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			if(octopi[i][j][0] > 9 && octopi[i][j][1] == 0) {
				octopi[i][j][1] = 1;
				total++;
				//Top-Left
				if(i > 0 && j > 0) {
					(octopi[i-1][j-1][0])++;
				}
				//Above
				if(i > 0) {
					(octopi[i-1][j][0])++;
				}
				//Top-Right
				if(i > 0 && j < 9) {
					(octopi[i-1][j+1][0])++;
				}
				//Left
				if(j > 0) {
					(octopi[i][j-1][0])++;
				}
				//Right
				if(j < 9) {
					(octopi[i][j+1][0])++;
				}
				//Bottom-Left
				if(i < 9 && j > 0) {
					(octopi[i+1][j-1][0])++;
				}
				//Below
				if(i < 9) {
					(octopi[i+1][j][0])++;
				}
				//Bottom-Right
				if(i < 9 && j < 9) {
					(octopi[i+1][j+1][0])++;
				}
			}
		}
	}
}

void reset(int octopi[10][10][2]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			if(octopi[i][j][0] > 9) {
				octopi[i][j][0] = 0;
				octopi[i][j][1] = 0;
			}
		}
	}
}

void timestep(int octopi[10][10][2]) {
	iterate(octopi);
	//Making sure that the flashing octopi chain reactions play out
	for(int i = 0; i < 100; i++) {
		flash(octopi);
	}
	reset(octopi);
}

bool checkSync(int octopi[10][10][2]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			if(octopi[i][j][0] != 0) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	total = 0;
	string a;
	char b;
	int octopi[10][10][2];
	ifstream input;
	input.open("input.txt");
	if(input.is_open()) {
		istringstream s;
		int i = 0;
		while(getline(input, a)) {
			s.str(a);
			int j = 0;
			while(s >> b) {
				int num = b - '0';
				octopi[i][j][0] = num;
				octopi[i][j][1] = 0;
				j++;
			}
			s.clear();
			i++;
		}
	}
	else {
		exit(1);
	}
	
	int count = 0;
	while(!checkSync(octopi)) {
		count++;
		timestep(octopi);
	}
	display(octopi);
	
	cout << endl << "Timestep: " << count << endl;
	cout << checkSync(octopi) << endl;

	return 0;
}
