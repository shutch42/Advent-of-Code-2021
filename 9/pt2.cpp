#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int checkBasin(int x, int y, vector<vector<int>>& heightmap) {
	if(heightmap[x][y] < 9) {
		heightmap[x][y] = 9;
		return 1 + checkBasin(x+1, y, heightmap) + checkBasin(x-1, y, heightmap) + checkBasin(x, y+1, heightmap) + checkBasin(x, y-1, heightmap);
	}
	else {
		return 0;
	}
}

int main() {
	ifstream input;
	string nums;
	char num;
	stringstream line;
	vector<vector<int>> heightmap;
        vector<int> row;
	int largest[3] = {0,0,0};
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
			
				vector<vector<int>> copy;
				copy = heightmap;
				int min = 0;
				for(int minIndex = 1; minIndex < 3; minIndex++) {
					if(largest[minIndex] < largest[min]) {
						min = minIndex;
					}
				}
				int basin = checkBasin(i, j, copy);
				if(basin > largest[min]) {
					largest[min] = basin;
				}
				copy.clear();
//				cout << heightmap[i][j] << endl;
				//sum += heightmap[i][j] + 1;

			}
		}
	}

	cout << largest[0] * largest[1] * largest[2] << endl;
	input.close();
	return 0;
}
