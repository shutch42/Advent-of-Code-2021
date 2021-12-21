#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct node {
	int num;
	node* next;
};
struct board {
	int nums[5][5];
	bool mark[5][5];
	board* next;
};

void printNodes(node* head) {
	node* curr = head;
	while(curr != nullptr) {
		cout << curr->num << endl;
		curr = curr->next;
	}
}

void printBoards(board* head) {
	board* curr = head;
	while(curr->next != nullptr) {
		for(int y = 0; y < 5; y++) {
			for(int x = 0; x < 5; x++) {
				cout << curr->nums[x][y];
				if(curr->mark[x][y]) {
					cout << "* ";
				}
				else {
					cout << "  ";
				}
			}
			cout << endl;
		}
		cout << endl;
		curr = curr->next;
	}
}

void markBoards(board* head, int num) {
	board* curr = head;
	while(curr->next != nullptr) {
		for(int y = 0; y < 5; y++) {
			for(int x = 0; x < 5; x++) {
				if(curr->nums[x][y] == num) {
					curr->mark[x][y] = true;
				}
			}
		}
		curr = curr->next;
	}
}

void clearTestArr(bool test[]) {
	for(int i = 0; i < 5; i++) {
		test[i] = false;
	}
}

board* checkBoards(board* head) {
	board* curr = head;
	bool found = false;
	while(curr->next != nullptr && !found) {
		bool t[5] = {0,0,0,0,0};
		//test rows
		for(int y = 0; y < 5 && !found; y++) {
			for(int x = 0; x < 5 && !found; x++) {
				t[x] = curr->mark[x][y];
			}
			if(t[0] && t[1] && t[2] && t[3] && t[4]) {
				found = true;
				//Match found
			}
		}
		//test columns
		clearTestArr(t);
		for(int x = 0; x < 5 && !found; x++) {
			for(int y = 0; y < 5 && !found; y++) {
				t[y] = curr->mark[x][y];
			}
			if(t[0] && t[1] && t[2] && t[3] && t[4]) {
				found = true;
				//Match found
			}
		}

/*
		//test diagonal
		clearTestArr(t);
		for(int i = 0; i < 5 && !found; i++) {
			t[i] = curr->mark[i][i];
		}
		if(t[0] && t[1] && t[2] && t[3] && t[4]) {
			found = true;//Match found
		}

		//test other diagonal
		clearTestArr(t);
		for(int i = 0; i < 5 && !found; i++) {
			t[i] = curr->mark[4-i][i];
		}
		if(t[0] && t[1] && t[2] && t[3] && t[4]) {
			found = true;//Match found
		}
*/		
		if(!found) {
			curr = curr->next;
		}
	}
	if(found) {
		return curr;
	}
	else {
		return nullptr;
	}
}

int main() {
	ifstream input;
	string s;
	istringstream ss;
	input.open("input.txt");
	node* head = new node;
	node* curr = head;
	board* boardHead = new board;
	board* currBoard = boardHead;
	int num;
	if(input.is_open()) {
		while(getline(input, s, ',')) {
			if(s.length() <= 2) {
				curr->num = stoi(s);
				curr->next = new node;
				curr = curr->next;
			}
			else {
				ss.str(s);
				ss >> num;
				curr->num = num;
				curr->next = nullptr;
			}
		}
		while(ss) {
			for(int y = 0; y < 5; y++) {
				for(int x = 0; x < 5; x++) {
					ss >> num;
					currBoard->nums[x][y] = num;
					currBoard->mark[x][y] = false;
				}
			}
			if(ss) {
				currBoard->next = new board;
				currBoard = currBoard->next;
			}
		}
		currBoard = nullptr;
	}
	else {
		exit(1);
	}
	input.close();

//	printBoards(boardHead);	
	curr = head;
	board* solution = nullptr;
	int winningNum = 0;
	while(curr != nullptr && solution == nullptr) {
		markBoards(boardHead, curr->num);
//		printBoards(boardHead);
		solution = checkBoards(boardHead);
		if(solution != nullptr) {
			winningNum = curr->num;
		}
		curr = curr->next;
	}
	
	int sum = 0;	
	if(solution != nullptr) {
		for(int y = 0; y < 5; y++) {
			for(int x = 0; x < 5; x++) {
				cout << solution->nums[x][y];
				if(solution->mark[x][y]) {
					cout << "* ";
				}
				else {
					cout << "  ";
					sum += solution->nums[x][y];
				}
			}
			cout << endl;
		}
	}
	cout << "Sum: " << sum << endl;
	cout << "Winning Number: " << winningNum << endl;
	cout << "Solution: " << sum*winningNum << endl;

	return 0;
}
