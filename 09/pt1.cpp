#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

bool checkArr(bool arr[3][3]) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(!arr[i][j]) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	ifstream input;
	string nums;
	char num;
	stringstream line;
	vector<vector<int>> heightmap;
        vector<int> row;
	int sum = 0;
	input.open("input.txt");
	if(input.is_open()) {

		while(input >> nums) {			
			line.str(nums);
			row.push_back(9);
			while(line >> num) {
				int height = num - '0';
				row.push_back(height);
			}
			row.push_back(9);
			heightmap.push_back(row);
			row.clear();
			line.clear();
		}
		for(int i = 0; i < heightmap[0].size(); i++) {
			row.push_back(9);
		}
		heightmap.push_back(row);
		heightmap.insert(heightmap.begin(), row);
	}
	else {
		exit(1);
	}
	bool check[3][3];
	check[1][1] = 1;
	for(int i = 1; i < heightmap.size()-1; i++) {
		for(int j = 1; j < heightmap[0].size()-1; j++) {
			if(heightmap[i][j] < heightmap[i-1][j-1] &&
			   heightmap[i][j] < heightmap[i][j-1]   &&
			   heightmap[i][j] < heightmap[i-1][j]   &&
			   heightmap[i][j] < heightmap[i][j+1]   &&
			   heightmap[i][j] < heightmap[i+1][j]   &&
			   heightmap[i][j] < heightmap[i-1][j+1] &&
			   heightmap[i][j] < heightmap[i+1][j-1] &&
			   heightmap[i][j] < heightmap[i+1][j+1]  ) {
				
				//cout << heightmap[i][j] << endl;
				sum += heightmap[i][j] + 1;

			}
		}
	}
	cout << sum << endl;
	input.close();
	return 0;
}
