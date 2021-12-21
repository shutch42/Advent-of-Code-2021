#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//8 Step Algorithm to Find Segment Key:
//
//1. Find shared segment between 2 character and 3 character code. This is segment a.
//2. Find segments b and c using 2 character and 4 character code.
//3. Use b and c to narrow down b in a 5 character code
//4. Deduce c now that b is found
//5. Find segment d using 2 character and 6 character code.
//6. Find segment g as the remaining segment in the 2 character code.
//7. Find segment e as the remaining segment in the 6 character code.
//8. The last remaining segment is g.

char twos[2];
char threes[3];
char fours[4];
char fives[3][5];
char sixes[3][6];
char sevens[7];
char key[7];
int numFives;
int numSixes;

bool compArr(bool arr1[7], bool arr2[7]) {
	for(int i = 0; i < 7; i++) {
		if(arr1[i] != arr2[i]) {
			return false;
		}
	}
	return true;
}

int findNum(bool code[7]) {
	bool zero[7] = {1,1,0,1,1,1,1};
	bool one[7] = {0,0,0,1,0,0,1};
	bool two[7] = {1,0,1,1,1,1,0};
	bool three[7] = {1,0,1,1,0,1,1};
	bool four[7] = {0,1,1,1,0,0,1};
	bool five[7] = {1,1,1,0,0,1,1};
	bool six[7] = {1,1,1,0,1,1,1};
	bool seven[7] = {1,0,0,1,0,0,1};
	bool eight[7] = {1,1,1,1,1,1,1};
	bool nine[7] = {1,1,1,1,0,1,1};
	if(compArr(code, zero)) {
		return 0;
	}
	if(compArr(code, one)) {
		return 1;
	}
	if(compArr(code, two)) {
		return 2;
	}
	if(compArr(code, three)) {
		return 3;
	}
	if(compArr(code, four)) {
		return 4;
	}
	if(compArr(code, five)) {
		return 5;
	}
	if(compArr(code, six)) {
		return 6;
	}
	if(compArr(code, seven)) {
		return 7;
	}
	if(compArr(code, eight))  {
		return 8;
	}
	if(compArr(code, nine)) {
		return 9;
	}
	//Code should never reach here
	cout << "Error in findNum" << endl;
	exit(1);
}

void assignCode(char letters[7], int count) {
	switch(count) {
		case 2:
			twos[0] = letters[0];
			twos[1] = letters[1];
			break;
		case 3:
			threes[0] = letters[0];
			threes[1] = letters[1];
			threes[2] = letters[2];
			break;
		case 4:
			for(int i = 0; i < 4; i++) {
				fours[i] = letters[i];
			}
			break;
		case 5:
			for(int i = 0; i < 5; i++) {
				fives[numFives][i] = letters[i];
			}
			numFives++;
			break;
		case 6:
			for(int i = 0; i < 6; i++) {
				sixes[numSixes][i] = letters[i];
			}
			numSixes++;
			break;
		case 7:
			for(int i = 0; i < 7; i++) {
				sevens[i] = letters[i];
			}
			break;
		}
}

void solveCode() {
	char a;
	char b;
	char c;
	char d;
	char e;
	char f;
	char g;
	char bc[2];
	int bcCount = 0;
	char shared5[3];
	int share5Count = 0;
	char rem5[4] = {'\n', '\n', '\n', '\n'};
	int rem5Count = 0;
	char shared6[4];
	int share6Count = 0;
	char rem6[3] = {'\n', '\n', '\n'};
	int rem6Count = 0;

	for(int i = 0; i < 3; i++) {
		if(threes[i] != twos[0] && threes[i] != twos[1]) {
			a = threes[i];
		}
	}

	for(int i = 0; i < 4; i++) {
		if(fours[i] != twos[0] && fours[i] != twos[1]) {
			bc[bcCount] = fours[i];
			bcCount++;
		}
	}
	
	//A very inefficient way to find shared characters
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			for(int k = 0; k < 5; k++) {
				if(fives[0][i] == fives[1][j] && fives[0][i] == fives[2][k]) {
					shared5[share5Count] = fives[0][i];
					share5Count++;
				}
			}
		}
	}

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 5; j++) {
			if(fives[i][j] != shared5[0] && fives[i][j] != shared5[1] && fives[i][j] != shared5[2]) {
				if(fives[i][j] != rem5[0] && fives[i][j] != rem5[1] && fives[i][j] != rem5[2] && fives[i][j] != rem5[3]) {
					rem5[rem5Count] = fives[i][j];
					rem5Count++;
				}
			}
		}
	}

	for(int i = 0; i < 4; i++) {
		if(bc[0] == rem5[i]) {
			b = bc[0];
			c = bc[1];
		}
		if(bc[1] == rem5[i]) {
			b = bc[1];
			c = bc[0];
		}
	}

	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 6; j++) {
			for(int k = 0; k < 6; k++) {
				if(sixes[0][i] == sixes[1][j] && sixes[0][i] == sixes[2][k]) {
					shared6[share6Count] = sixes[0][i];
					share6Count++;
				}
			}
		}
	}

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 6; j++) {
			if(sixes[i][j] != shared6[0] && sixes[i][j] != shared6[1] && sixes[i][j] != shared6[2] && sixes[i][j] != shared6[3]) {
				if(sixes[i][j] != rem6[0] && sixes[i][j] != rem6[1] && sixes[i][j] != rem6[2]) {
					rem6[rem6Count] = sixes[i][j];
					rem6Count++;
				}
			}
		}
	}

	if(twos[0] == rem6[0] || twos[0] == rem6[1] || twos[0] == rem6[2]) {
		d = twos[0];
		g = twos[1];
	}
	if(twos[1] == rem6[0] || twos[1] == rem6[1] || twos[1] == rem6[2]) {
		d = twos[1];
		g = twos[0];
	}

	for(int i = 0; i < 3; i++) {
		if(rem6[i] != c && rem6[i] != d) {
			e = rem6[i];
		}
	}

	for(int i = 0; i < 7; i++) {
		if(sevens[i] != a && sevens[i] != b && sevens[i] != c && sevens[i] != d && sevens[i] != e && sevens[i] != g) {
			f = sevens[i];
		}
	}
	key[0] = a;
	key[1] = b;
	key[2] = c;
	key[3] = d;
	key[4] = e;
	key[5] = f;
	key[6] = g;
}

int main() {
	ifstream input;
	string code1;
	string code2;
	string digits;
	stringstream invals;
	stringstream outvals;
	//arrays to store characters based on number of segments
	int countnum[7] = {0,0,0,0,0,0,0};
	int total = 0;
	input.open("input.txt");
	if(input.is_open()) {
		while(getline(input, code1, '|') && getline(input, code2, '\n')) {
			invals.str(code1);
			numFives = 0;
			numSixes = 0;
			while(invals >> digits) {
				int count = 0;
				stringstream segments;
				segments.str(digits);
				char letter;
				char letters[7];
				for(int i = 0; segments >> letter; i++) {
					letters[i] = letter;
					count++;
				}
				assignCode(letters, count);
			}
			solveCode();
			outvals.str(code2);
			int place = 3;
			int multiplier = 1000;
			while(outvals >> digits) {
				stringstream segments;
				segments.str(digits);
				char letter;
				bool soln[7] = {0,0,0,0,0,0,0};
				while(segments >> letter) {
					for(int i = 0; i < 7; i++) {
						if(letter == key[i]) {
							soln[i] = 1;
						}
					}
				}
				total += findNum(soln)*multiplier;
				place--;
				multiplier = 1;
				for(int i = 0; i < place; i++) {
					multiplier *= 10;
				}
			}
			invals.clear();
			outvals.clear();
		}
	}
	else {
		exit(1);
	}
	input.close();
	cout << total << endl;
	return 0;
}
