#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct line {
	int start[2];
	int end[2];
	line* next;
};

int loadPts(ifstream& file, line* head) {
	line* curr = head;
	int x1, x2, y1, y2;
	string num;
	file.open("input.txt");
	if(file.is_open()) {
		while(getline(file, num, ',')) {
			x1 = stoi(num);
			getline(file, num, ' ');
			y1 = stoi(num);
			getline(file, num, ' ');
			getline(file, num, ',');
			x2 = stoi(num);
			getline(file, num, '\n');
			y2 = stoi(num);
			curr->start[0] = x1;
			curr->start[1] = y1;
			curr->end[0] = x2;
			curr->end[1] = y2;
			curr->next = new line;
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

void dispPts(line* head) {
	line* curr = head;
	while(curr->next != nullptr) {
		cout << curr->start[0] << ", " << curr->start[1] << " -> ";
		cout << curr->end[0] << ", " << curr->end[1] << endl;
		curr = curr->next;
	}
}

int getMaxX(line* head) {
	line* curr = head;
	int max = 0;
	while(curr->next != nullptr) {
		if(curr->start[0] > max) {
			max = curr->start[0];
		}
		if(curr->end[0] > max) {
			max = curr->end[0];
		}
		curr = curr->next;
	}
	return max;
}

int getMaxY(line* head) {
	line* curr = head;
	int max = 0;
	while(curr->next != nullptr) {
		if(curr->start[1] > max) {
			max = curr->start[1];
		}
		if(curr->end[1] > max) {
			max = curr->end[1];
		}
		curr = curr->next;
	}
	return max;
}

int** loadMap(line* head) {
	int x = getMaxX(head)+1;
	int y = getMaxY(head)+1;
	int** map;
	map = new int*[x];
	for(int i = 0; i < x; i++) {
		map[i] = new int[y];
		for(int j = 0; j < y; j++) {
			map[i][j] = 0;
		}
	}
	line* curr = head;
	while(curr->next != nullptr) {
		if(curr->start[0] == curr->end[0]) {
			//vertical line
		//	cout << curr->start[0] << "," << curr->start[1] << " -> " << curr->end[0] << "," << curr->end[1] << endl;
			if(curr->start[1] < curr->end[1]) {
				for(int i = curr->start[1]; i <= curr->end[1]; i++) {
		//			cout << curr->start[0] << "," << i << endl;
					map[curr->start[0]][i]++;
				}
			}
			else {
				for(int i = curr->start[1]; i >= curr->end[1]; i--) {
		//			cout << curr->start[0] << "," << i << endl;
					map[curr->start[0]][i]++;
				}
			}
		}
		if(curr->start[1] == curr->end[1]) {
			//horizontal line
		//	cout << curr->start[0] << "," << curr->start[1] << " -> " << curr->end[0] << "," << curr->end[1] << endl;
			if(curr->start[0] < curr->end[0]) {
				for(int i = curr->start[0]; i <= curr->end[0]; i++) {
		//			cout << i << "," << curr->start[1] << endl;
					map[i][curr->start[1]]++;
				}
			}
			else {
				for(int i = curr->start[0]; i >= curr->end[0]; i--) {
		//			cout << i << "," << curr->start[1] << endl;
					map[i][curr->start[1]]++;
				}
			}
		}
		curr = curr->next;
	}
	return map;
}

int getNumOverlap(int** map, int x, int y) {
	int total = 0;
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			if(map[i][j] > 1) {
			//	cout << map[i][j] << endl;
				total++;
			}
		}
	}
	return total;
}	

int main() {

	ifstream input;
	line* head = new line;

	if(loadPts(input, head)) {
		//dispPts(head);
		int** map = loadMap(head);
		int x = getMaxX(head)+1;
		int y = getMaxY(head)+1;
		cout << "There are " << getNumOverlap(map, x, y) << " points of overlap" << endl;
	}
	else {
		exit(1);
	}

	return 0;
}
