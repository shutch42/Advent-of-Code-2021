#include <iostream>
#include <fstream>
using namespace std;

int loadFish(ifstream& file, long arr[9]) {
	string num;
	file.open("input.txt");
	if(file.is_open()) {
		while(getline(file, num, ',')) {
			arr[stoi(num)]++;
		}
	}
	else {
		return 0;
	}
	file.close();
	return 1;
}

void passDay(long arr[9]) {
	long newFish = arr[0];
	arr[0] = arr[1];
	arr[1] = arr[2];
	arr[2] = arr[3];
	arr[3] = arr[4];
	arr[4] = arr[5];
	arr[5] = arr[6];
	arr[6] = arr[7] + newFish;
	arr[7] = arr[8];
	arr[8] = newFish;
}	

long countFish(long arr[9]) {
	long total = 0;
	for(int i = 0; i < 9; i++) {
		total += arr[i];
	}
	return total;
}

int main() {
	long fishTimers[9] = {0,0,0,0,0,0,0,0,0};
	ifstream input;
	if(loadFish(input, fishTimers)) {
		for(int i = 0; i < 256; i++) {
			passDay(fishTimers);
		}
		cout << "Total fish: " << countFish(fishTimers) << endl;

	}
	else {
		exit(1);
	}
	return 0;
}
