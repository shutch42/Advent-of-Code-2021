#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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

int getScore(chunk* a) {
	switch(a->type) {
		case round:
			return 1;
		case square:
			return 2;
		case curly:
			return 3;
		case pointy:
			return 4;
		default:
			return 0;
	}
}

long int findMedian(vector<long int> scores) {
	sort(scores.begin(), scores.end());
	int i = scores.size() / 2;
	return scores[i];
}

int main() {
	ifstream input;
	string a;
	input.open("input.txt");
	if(input.is_open()) {
	int count = 1;
	int score = 0;
	vector<long int> scores;
	while(getline(input, a)) {
		//cout << "Row " << count << endl;
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
		long int currScore = 0;
		int discard = 0;	//I shouldn't use control bits, but it works in this case
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
				if(curr != outer) {
					if(matches(curr, b)) {
						curr->closes = b;
						curr = curr->inside;
					}
					else {
						discard = 1;
						break;
					}
				}
				else {
					curr->closes = b;
					line >> b;
					outer = new chunk();
					outer->opens = b;
					outer->closes = '\n';
					outer->inside = nullptr;
					curr = outer;
				}
			}
		}
		if(discard) {
			discard = 0;
		}
		else {
		//	cout << "Incomplete line found" << endl;
			while(curr != outer) {
				currScore *= 5;
				currScore += getScore(curr);
				curr = curr->inside;
			}
			currScore *= 5;
			currScore += getScore(curr);
			scores.push_back(currScore);
		//	cout << "Score: " << currScore << endl;
		}
		count++;
		line.clear();
	}

	cout << "Median: " << findMedian(scores) << endl;

	}
	else {
		cout << "Error opening file" << endl;
		exit(1);
	}
	input.close();
	return 0;
}
