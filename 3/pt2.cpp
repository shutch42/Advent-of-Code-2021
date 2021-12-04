#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

struct node {
	string bin;
	node* next;
};

void dispList(node* head) {
	node* curr = head;
	while(curr != nullptr) {
		cout << curr->bin << endl;
		curr = curr->next;
	}
}

node* copyList(node* head) {
	node* curr;
	node* copyHead;
	node* copy;
	curr = head;
	copy = new node;
	copy->bin = head->bin;
	copyHead = copy;
	while(curr->next != nullptr) {
		curr = curr->next;
		copy->next = new node;
		copy = copy->next;
		copy->bin = curr->bin;
	}
	copy->next = nullptr;
	return copyHead;
}

int bitsToNum(string bits) {
	int sum = 0;
	for(int i = 0; i < 12; i++) {
		sum += (bits.at(11-i) - '0') * pow(2,i);
	}
	return sum;
}

void filterOxygen(node* head) {
	node* curr;
	char key;
	for(int i = 0; i < 12 && head->next->next != nullptr; i++) {
		int zeros = 0;
		int ones = 0;
		curr = head->next;
		while(curr != nullptr) {
			(curr->bin.at(i) == '1') ? ones++ : zeros++;
			curr = curr->next;
		}
		curr = head;
		node* next = curr->next;
		(ones >= zeros) ? key = '1' : key = '0';
		while(next != nullptr && head->next->next != nullptr) {
			if(next->bin.at(i) != key) {
				curr->next = next->next;
				free(next);
				next = curr->next;
			}
			else {
				curr = curr->next;
				next = curr->next;
			}
		}
	}
}

void filterCO2(node* head) {
	node* curr;
	char key;
	for(int i = 0; i < 12 && head->next->next != nullptr; i++) {
		int zeros = 0;
		int ones = 0;
		curr = head->next;
		while(curr != nullptr) {
			(curr->bin.at(i) == '1') ? ones++ : zeros++;
			curr = curr->next;
		}
		curr = head;
		node* next = curr->next;
		(zeros <= ones) ? key = '0' : key = '1';
		while(next != nullptr && head->next->next != nullptr) {
			if(next->bin.at(i) != key) {
				curr->next = next->next;
				free(next);
				next = curr->next;
			}
			else {
				curr = curr->next;
				next = curr->next;
			}
		}
	}
}

int main() {
	char bit;
	node* head;
	node* curr;
	head = new node;
	head->bin = "";
	head->next = nullptr;
	curr = head;
	ifstream input;
	input.open("input.txt");
	if(input.is_open()) {
		while(input >> bit) {
			curr->next = new node;
			curr = curr->next;
			curr->bin = "";
			curr->next = nullptr;
			curr->bin += bit;
			for(int i = 1; i < 12; i++) {
				input >> bit;
				curr->bin += bit;
			}
		}
	}
	else {
		cerr << "Error opening file" << endl;
		exit(1);
	}
	input.close();	

	node* oxygenDataHead = copyList(head);
	node* co2DataHead = copyList(head);
	
	filterOxygen(oxygenDataHead);
	filterCO2(co2DataHead);
	
	int oxygen = bitsToNum(oxygenDataHead->next->bin);
	int co2 = bitsToNum(co2DataHead->next->bin);
	cout << "Oxygen: " << oxygen << endl;
	cout << "CO2: " << co2 << endl;
	cout << "Life Support Rating: " << oxygen * co2 << endl;

	return 0;
}
