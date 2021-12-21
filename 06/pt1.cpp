#include <iostream>
#include <fstream>
using namespace std;

struct lanternFish {
	int timer;
	lanternFish* next;
};

void printFish(lanternFish* head) {
	lanternFish* curr = head;
	while(curr->next != nullptr) {
		cout << curr->timer << " ";
		curr = curr->next;
	}
	cout << endl;
}

int loadFish(ifstream& file, lanternFish* head) {
	lanternFish* curr = head;
	string num;
	file.open("input.txt");
	if(file.is_open()) {
		while(getline(file, num, ',')) {
			curr->timer = stoi(num);
			curr->next = new lanternFish;
			curr = curr->next;
		}
		curr = nullptr;
	}
	else {
		return 0;
	}
	file.close();
	return 1;
}

void passDay(lanternFish* head) {
	lanternFish* curr = head;
	lanternFish* prev = head;
	int addFish = 0;
	while(curr->next != nullptr) {
		if(curr->timer == 0) {
			addFish++;
			curr->timer = 6;
		}
		else {
			curr->timer--;
		}
		curr = curr->next;
	}
	while(prev->next != curr) {
		prev = prev->next;
	}

	for(int i = 0; i < addFish; i++) {
		lanternFish* newFish = new lanternFish;
		newFish->timer = 8;
		prev->next = newFish;
		newFish->next = curr;
		prev = prev->next;
	}
}

int countFish(lanternFish* head) {
	int total = 0;
	lanternFish* curr = head;
	while(curr->next != nullptr) {
		total++;
		curr = curr->next;
	}
	return total;
}

int main() {
	lanternFish* head = new lanternFish;
	ifstream input;
	if(loadFish(input, head)) {
		for(int i = 0; i < 80; i++) {
			passDay(head);
		}
		cout << "Total fish: " << countFish(head) << endl;

	}
	else {
		exit(1);
	}
	return 0;
}
