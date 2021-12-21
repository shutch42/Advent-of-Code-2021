#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct crab {
	int position;
	crab* next;
};

struct fuelTotal {
	int total;
	fuelTotal* next;
};

void dispCrabs(crab* head) {
	crab* curr = head;
	while(curr->next != nullptr) {
		cout << curr->position << endl;
		curr = curr->next;
	}
}

int getMin(crab* head) {
	crab* curr = head;
	int min = curr->position;
	curr = curr->next;
	while(curr->next != nullptr) {
		if(curr->position < min) {
			min = curr->position;
		}
		curr = curr->next;
	}
	return min;
}

int getMax(crab* head) {
	crab* curr = head;
	int max = curr->position;
	curr = curr->next;
	while(curr->next != nullptr) {
		if(curr->position > max) {
			max = curr->position;
		}
		curr = curr->next;
	}
	return max;
}

void dispTotals(fuelTotal* head) {
	fuelTotal* curr = head;
	while(curr->next != nullptr) {
		cout << curr->total << endl;
		curr = curr->next;
	}
}

int getMinTotal(fuelTotal* head) {
	fuelTotal* curr = head;
	int min = curr->total;
	while(curr->next != nullptr) {
		if(curr->total < min) {
			min = curr->total;
		}
		curr = curr->next;
	}
	return min;
}

int summation(int num) {
	int sum = 0;
	for(int i = num; i > 0; i--) {
		sum += i;
	}
	return sum;
}

int bruteForce(crab* head) {
	fuelTotal* fHead = new fuelTotal;
	fuelTotal* fCurr = fHead;
	for(int i = getMin(head); i <= getMax(head); i++) {
		crab* curr = head;
		int totalFuel = 0;
		while(curr->next != nullptr) {
			totalFuel += summation(abs(curr->position - i));
			curr = curr->next;
		}
		fCurr->total = totalFuel;
		fCurr->next = new fuelTotal;
		fCurr = fCurr->next;
	}
	return getMinTotal(fHead);	
}

int main() {
	ifstream input;
	string num;
	input.open("input.txt");
	crab* head = new crab;
	crab* curr = head;
	if(input.is_open()) {
		while(getline(input, num, ',')) {
			curr->position = stoi(num);
			curr->next = new crab;
			curr = curr->next;
		}
		curr = nullptr;
		cout << bruteForce(head) << endl;
	}
	else {
		return 1;
	}
	input.close();
	return 0;
}
