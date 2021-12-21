#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int round = 0;
const int square = 1;
const int curly = 2;
const int pointy = 3;

struct chunk {
	char opens;
	char closes;
	int type;
	chunk* contains;
	chunk* inside;
};

int findType(char c) {
	switch(c) {
		case '(':
			return round;
		case ')':
			return round;
		case '[':
			return square;
		case ']':
			return square;
		case '{':
			return curly;
		case '}':
			return curly;
		case '<':
			return pointy;
		case '>':
			return pointy;
		default:
			return -1;
	}
}

bool opens(char c) {
	switch(c) {
		case '(':
		case '{':
		case '[':
		case '<':
			return true;
		default:
			return false;
	}
}

bool matches(chunk* a, char c) {
	if( (a->type == round && c == ')') ||
	    (a->type == square && c == ']') ||
	    (a->type == curly && c == '}') ||
	    (a->type == pointy && c == '>')) {

		return true;
	}
	else {
		return false;
	}
}

int getScore(char c) {
	switch(c) {
		case ')':
			return 3;
		case ']':
			return 57;
		case '}':
			return 1197;
		case '>':
			return 25137;
		default:
			return 0;
	}
}

int main() {
	ifstream input;
	string a;
	input.open("input.txt");
	if(input.is_open()) {
	int count = 1;
	int score = 0;
	while(getline(input, a)) {
		stringstream line;
		line.str(a);
		char b;
		chunk* outer = new chunk();
		line >> b;
		outer->type = findType(b);
		outer->opens = b;
		outer->closes = '\n';
		outer->inside = nullptr;
		chunk* curr = outer;
		int currScore = 0;
		while(line >> b) {
			if(opens(b)) {
				curr->contains = new chunk();
				curr->contains->type = findType(b);
				curr->contains->opens = b;
				curr->contains->closes = '\n';
				curr->contains->inside = curr;
				curr = curr->contains;
			}
			else {
				if(matches(curr, b)) {
					if(curr->inside != nullptr) {
						curr = curr->inside;
					}
					else {
						currScore = 0;
						break;
					}
				}
				else {
					currScore += getScore(b);
					curr = curr->inside;
				}
			}
		}
		score += currScore;
		count++;
		line.clear();
	}
	cout << "Final score: " << score << endl;
	}
	else {
		cout << "Error opening file" << endl;
		exit(1);
	}
	input.close();
	return 0;
}
