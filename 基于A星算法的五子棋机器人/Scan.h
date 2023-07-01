#pragma once
#include<vector>
using namespace std;
class Scan {
private:
	short** pieces;
	short myColor;
	short emptyColor;
	short enemyColor;
	vector<int>*row;
	vector<int>*col;
	vector<int>*leftSlash;
	vector<int>*rightSlash;
	int max = 1000000;
	int area = 5;
	int fiveArea = 4;
	int fourToFiveArea=4;
	int rushFourArea=4;
	int aliveThreeArea;
	int rushThreeArea;
	int sleepThreeArea;
	int aliveTwoArea;
	int sleepTwoArea;
	int timeScore[8] = {max,8000,5000,4000,500,200,50,max*10};
	enum scoreType { FourToFive, RushFour, AliveThree, RushThree, SleepThree, AliveTwo, SleepTwo,Five };
public:
    void scanRow(int x, int y, int area);
	void scanCol(int x, int y, int area);
	void scanLeftSlash(int x, int y, int area);
	void scanRightSlash(int x, int y, int area);
	bool matching(int* arr, vector<int>* res, int length, bool show = 0);
	int fourToFive(int x, int y);
	int rushFour(int x, int y);
	int aliveThree(int x, int y);
	int rushThree(int x, int y);
	int sleepThree(int x, int y);
	int aliveTwo(int x, int y);
	int sleepTwo(int x, int y);
	int five(int x, int y);
	void init(short my,short empty,short enemy, short** table,int max,int*val=NULL);
	int scan(int x,int y);
};
void Scan::scanRow(int x, int y,int area) {
	row->push_back(1);
	int dis = 0;
	if (x == 1) {
		row->insert(row->begin(), 2);
		dis++;
	}
	for (int i = 1; i <= area && x - i >= 1; i++,dis++) {
		if (pieces[y][x - i] == myColor) {
			row->insert(row->begin(), 1);
		}
		else if (pieces[y][x - i] == emptyColor) {
			row->insert(row->begin(), 0);
		}
		else {
			row->insert(row->begin(), 2);
		}
		if (x - i == 1) {
			row->insert(row->begin(), 2);
			dis++;
		}
	}
	if (x == 19) {
		row->push_back(2);
	}
	for (int i = 1; i <= area && x + i <= 19; i++) {
		if (y&&pieces[y][x + i] == myColor) {
			row->push_back(1);
		}
		else if (pieces[y][x + i] == emptyColor) {
			row->push_back(0);
		}
		else {
			row->push_back(2);
		}
		if (x + i == 19) {
			row->push_back(2);
		}
	}
	row->push_back(dis);
}
void Scan::scanCol(int x, int y, int area) {
	int dis = 0;
	col->push_back(1);
	if (y  == 1) {
		col->insert(col->begin(), 2);
		dis++;
	}
	for (int i = 1; i <= area && y - i >= 1; i++,dis++) {
		if (pieces[y - i][x] == myColor) {
			col->insert(col->begin(), 1);
		}
		else if (pieces[y - i][x] == emptyColor) {
			col->insert(col->begin(), 0);
		}
		else {
			col->insert(col->begin(), 2);
			break;
		}
		if (y - i == 1) {
			col->insert(col->begin(), 2);
			dis++;
		}
	}
	if (y  == 19) {
		col->push_back(2);
	}
	for (int i = 1; i <= area && y + i <= 19; i++) {
		if (pieces[y + i][x] == myColor) {
			col->push_back(1);
		}
		else if (pieces[y + i][x] == emptyColor) {
			col->push_back(0);
		}
		else {
			col->push_back(2);
			break;
		}
		if (y + i == 19) {
			col->push_back(2);
		}
	}
	col->push_back(dis);
}
void Scan::scanLeftSlash(int x, int y, int area) {
	int dis = 0;
	leftSlash->push_back(1);
	if (x  == 1 || y == 1) {
		leftSlash->insert(leftSlash->begin(), 2);
		dis++;
	}
	for (int i = 1; i <= area && x - i >= 1 && y - i >= 1; i++,dis++) {
		if (pieces[y - i][x - i] == myColor) {
			leftSlash->insert(leftSlash->begin(), 1);
		}
		else if (pieces[y - i][x - i] == emptyColor) {
			leftSlash->insert(leftSlash->begin(), 0);
		}
		else {
			leftSlash->insert(leftSlash->begin(), 2);
			break;
		}
		if (x - i == 1 || y - i == 1) {
			leftSlash->insert(leftSlash->begin(), 2);
			dis++;
		}
	}
	if (y  == 19 || x  == 19) {
		leftSlash->push_back(2);
	}
	for (int i = 1; i <= area && y + i <= 19 && x + i <= 19; i++) {
		if (pieces[y + i][x + i] == myColor) {
			leftSlash->push_back(1);
		}
		else if (pieces[y + i][x + i] == emptyColor) {
			leftSlash->push_back(0);
		}
		else {
			leftSlash->push_back(2);
			break;
		}
		if (y + i == 19 || x + i == 19) {
			leftSlash->push_back(2);
		}
	}
	leftSlash->push_back(dis);
}
void Scan::scanRightSlash(int x, int y, int area) {
	int dis = 0;
	rightSlash->push_back(1);
	if (x == 19 || y == 1) {
		rightSlash->insert(rightSlash->begin(), 2);
		dis++;
	}
	for (int i = 1; i <= area && x + i <= 19 && y - i >= 1; i++,dis++) {
		if (pieces[y - i][x + i] == myColor) {
			rightSlash->insert(rightSlash->begin(), 1);
		}
		else if (pieces[y - i][x + i] == emptyColor) {
			rightSlash->insert(rightSlash->begin(), 0);
		}
		else {
			rightSlash->insert(rightSlash->begin(), 2);
			break;
		}
		if (x + i == 19 || y - i == 1) {
			rightSlash->insert(rightSlash->begin(), 2);
			dis++;
		}
	}
	if (x == 1 || y == 19) {
		rightSlash->push_back(2);
	}
	for (int i = 1; i <= area && y + i <= 19 && x - i >= 1; i++) {
		if (pieces[y + i][x - i] == myColor) {
			rightSlash->push_back(1);
		}
		else if (pieces[y + i][x - i] == emptyColor) {
			rightSlash->push_back(0);
		}
		else {
			rightSlash->push_back(2);
			break;
		}
		if (y + i == 19 || x - i == 1) {
			rightSlash->push_back(2);
		}
	}
	rightSlash->push_back(dis);
}
bool Scan::matching(int* arr, vector<int>* res, int length,bool show) {
	int i = 0; 
	int j = 1;
	int k;
	int vectorLength = res->size() - length;
	int dis = (*res)[res->size() - 1];
	while (i < vectorLength) {
		if (arr[0] == (*res)[i]) {
			k = i+1;
			for (j = 1; j < length; j++,k++) {
				if (arr[j] != (*res)[k]) {
					break;
				}
				else {
					if (j == length - 1&&dis>=i&&dis<=k)
						return 1;/*	*/
				}	
				
			}
			
		}
		i++;
	}
	return 0;
}
int Scan::fourToFive(int x, int y) {//活四
	int length = 6;
	int arr1[] = { 0,1,1,1,1,0 };
	int score = 0;
	int time = timeScore[FourToFive];
	if (matching(arr1, row, length)) {
		score += time;
	}
	if (matching(arr1, col, length))
	{
		score += time;
	}
	if (matching(arr1, leftSlash, length))
	{
		score += time;
	}
	if (matching(arr1,rightSlash, length))
	{
		score += time;
	}
	return score;
}
int Scan::rushFour(int x, int y) {//冲四
	int score = 0;
	int time = timeScore[RushFour];
	int length = 6;
	int length1 = 5;
	int arr1[] = { 2,1,1,1,1,0 };
	int arr2[] = { 0,1,1,1,1,2 };
	int arr3[] = { 1,0,1,1,1 };
	int arr4[] = { 1,1,0,1,1 };
	int arr5[] = { 1,1,1,0,1 };

	if (matching(arr1, row,length))
		score += time;
	else if (matching(arr2, row, length))
		score += time;
	else if (matching(arr3, row, length1))
		score += time;
	else if (matching(arr4, row, length1))
		score += time;
	else if (matching(arr5, row, length1))
		score += time;
	if (matching(arr1, col, length))
		score += time;
	else if (matching(arr2, col, length))
		score += time;
	else if (matching(arr3, col, length1))
		score += time;
	else if (matching(arr4, col, length1))
		score += time;
	else if (matching(arr5, col, length1))
		score += time;
	if (matching(arr1, leftSlash, length))
		score += time;
	else if (matching(arr2, leftSlash, length))
		score += time;
	else if (matching(arr3, leftSlash, length1))
		score += time;
	else if (matching(arr4, leftSlash, length1))
		score += time;
	else if (matching(arr5, leftSlash, length1))
		score += time;
	if (matching(arr1, rightSlash, length))
		score += time;
	else if (matching(arr2, rightSlash, length))
		score += time;
	else if (matching(arr3, rightSlash, length1))
		score += time;
	else if (matching(arr4, rightSlash, length1))
		score += time;
	else if (matching(arr5, rightSlash, length1))
		score += time;
	return score;
}
int Scan::aliveThree(int x, int y) {//活三
	int score = 0;
	int time = timeScore[AliveThree];
	int length = 6;
	int arr1[] = { 0,1,1,1,0,0 };
	int arr2[] = { 0,0,1,1,1,0 };
	if (matching(arr1, row, length))
		score += time;
	else if (matching(arr2, row, length))
		score += time;
	if (matching(arr1, col, length))
		score += time;
	else if (matching(arr2, col, length))
		score += time;
	if (matching(arr1, leftSlash, length))
		score += time;
	else if (matching(arr2, leftSlash, length))
		score += time;
	if (matching(arr1, rightSlash, length))
		score += time;
	else if (matching(arr2, rightSlash, length))
		score += time;
	return score;
}
int Scan::rushThree(int x, int y) {//跳三
	int score = 0;
	int time = timeScore[RushThree];
	int length = 6;
	int arr1[] = { 0,1,0,1,1,0 };
	int arr2[] = { 0,1,1,0,1,0 };
	if (matching(arr1, row, length))
		score += time;
	else if (matching(arr2, row, length))
		score += time;
	if (matching(arr1, col, length))
		score += time;
	else if (matching(arr2, col, length))
		score += time;
	if (matching(arr1, leftSlash, length))
		score += time;
	else if (matching(arr2, leftSlash, length))
		score += time;
	if (matching(arr1, rightSlash, length))
		score += time;
	else if (matching(arr2, rightSlash, length))
		score += time;
	return score;
}
int Scan::sleepThree(int x, int y) {//眠三
	int score = 0;
	int time = timeScore[SleepThree];
	int length = 6;
	int arr1[] = { 2,1,1,0,1,0 };
	int arr2[] = { 0,1,0,1,1,2 };
	int arr3[] = { 2,1,1,1,0,0 };
	int arr4[] = { 0,0,1,1,1,2 };
	int arr5[] = { 2,1,0,1,1,0 };
	int arr6[] = { 0,1,1,0,1,2 };
	if (matching(arr1, row, length))
		score += time;
	else if (matching(arr2, row, length))
		score += time;
	else if (matching(arr3, row, length))
		score += time;
	else if (matching(arr4, row, length))
		score += time;
	else if (matching(arr5, row, length))
		score += time;
	else if (matching(arr6, row, length))
		score += time;
	if (matching(arr1, col, length))
		score += time;
	else if (matching(arr2, col, length))
		score += time;
	else if (matching(arr3, col, length))
		score += time;
	else if (matching(arr4, col, length))
		score += time;
	else if (matching(arr5, col, length))
		score += time;
	else if (matching(arr6, col, length))
		score += time;
	if (matching(arr1, leftSlash, length))
		score += time;
	else if (matching(arr2, leftSlash, length))
		score += time;
	else if (matching(arr3, leftSlash, length))
		score += time;
	else if (matching(arr4, leftSlash, length))
		score += time;
	else if (matching(arr5, leftSlash, length))
		score += time;
	else if (matching(arr6, leftSlash, length))
		score += time;
	if (matching(arr1, rightSlash, length))
		score += time;
	else if (matching(arr2, rightSlash, length))
		score += time;
	else if (matching(arr3, rightSlash, length))
		score += time;
	else if (matching(arr4, rightSlash, length))
		score += time;
	else if (matching(arr5, rightSlash, length))
		score += time;
	else if (matching(arr6, rightSlash, length))
		score += time;
	return score;
}
int Scan::aliveTwo(int x, int y) {//活二
	int score = 0;
	int time = timeScore[AliveTwo];
	int length = 6;
	int arr1[] = { 0,0,1,1,0,0 };
	int arr2[] = { 0,1,0,1,0,0 };
	int arr3[] = { 0,1,1,0,0,0 };
	int arr4[] = { 0,0,0,1,1,0 };
	int arr5[] = { 0,0,1,0,1,0 };
	if (matching(arr1, row, length))
		score += time;
	else if (matching(arr2, row, length))
		score += time;
	else if (matching(arr3, row, length))
		score += time;
	else if (matching(arr4, row, length))
		score += time;
	else if (matching(arr5, row, length))
		score += time;
	if (matching(arr1, col, length))
		score += time;
	else if (matching(arr2, col, length))
		score += time;
	else if (matching(arr3, col, length))
		score += time;
	else if (matching(arr4, col, length))
		score += time;
	else if (matching(arr5, col, length))
		score += time;
	if (matching(arr1, leftSlash, length))
		score += time;
	else if (matching(arr2, leftSlash, length))
		score += time;
	else if (matching(arr3, leftSlash, length))
		score += time;
	else if (matching(arr4, leftSlash, length))
		score += time;
	else if (matching(arr5, leftSlash, length))
		score += time;
	if (matching(arr1, rightSlash, length))
		score += time;
	else if (matching(arr2, rightSlash, length))
		score += time;
	else if (matching(arr3, rightSlash, length))
		score += time;
	else if (matching(arr4, rightSlash, length))
		score += time;
	else if (matching(arr5, rightSlash, length))
		score += time;
	return score;
}
int Scan::sleepTwo(int x, int y) {//眠二
	int score = 0;
	int time = timeScore[SleepTwo];
	int length = 6;
	int arr1[] = { 2,0,1,0,1,0 };
	int arr2[] = { 2,1,0,0,1,0 };
	int arr3[] = { 2,1,1,0,0,0 };
	int arr4[] = { 0,0,0,1,1,2 };
	int arr5[] = { 0,1,0,0,1,2 };
	int arr6[] = { 0,1,0,1,0,2 };
	int arr7[] = { 2,0,1,1,0,0 };
	int arr8[] = { 2,1,0,1,0,0 };
	int arr9[] = { 0,0,1,0,1,2 };
	int arr10[] = { 0,0,1,1,0,2 };
	int arr11[] = { 2,0,0,1,1,0 };
	int arr12[] = { 0,1,1,0,0,2 };
	if (matching(arr1, row, length))
		score += time;
	else if (matching(arr2, row, length))
		score += time;
	else if (matching(arr3, row, length))
		score += time;
	else if (matching(arr4, row, length))
		score += time;
	else if (matching(arr5, row, length))
		score += time;
	else if (matching(arr6, row, length))
		score += time;
	else if (matching(arr7, row, length))
		score += time;
	else if (matching(arr8, row, length))
		score += time;
	else if (matching(arr9, row, length))
		score += time;
	else if (matching(arr10, row, length))
		score += time;
	else if (matching(arr11, row, length))
		score += time;
	else if (matching(arr12, row, length))
		score += time;
	if (matching(arr1, col, length))
		score += time;
	else if (matching(arr2, col, length))
		score += time;
	else if (matching(arr3, col, length))
		score += time;
	else if (matching(arr4, col, length))
		score += time;
	else if (matching(arr5, col, length))
		score += time;
	else if (matching(arr6, col, length))
		score += time;
	else if (matching(arr7, col, length))
		score += time;
	else if (matching(arr8, col, length))
		score += time;
	else if (matching(arr9, col, length))
		score += time;
	else if (matching(arr10, col, length))
		score += time;
	else if (matching(arr11, col, length))
		score += time;
	else if (matching(arr12, col, length))
		score += time;
	if (matching(arr1, leftSlash, length))
		score += time;
	else if (matching(arr2, leftSlash, length))
		score += time;
	else if (matching(arr3, leftSlash, length))
		score += time;
	else if (matching(arr4, leftSlash, length))
		score += time;
	else if (matching(arr5, leftSlash, length))
		score += time;
	else if (matching(arr6, leftSlash, length))
		score += time;
	else if (matching(arr7, leftSlash, length))
		score += time;
	else if (matching(arr8, leftSlash, length))
		score += time;
	else if (matching(arr9, leftSlash, length))
		score += time;
	else if (matching(arr10, leftSlash, length))
		score += time;
	else if (matching(arr11, leftSlash, length))
		score += time;
	else if (matching(arr12, leftSlash, length))
		score += time;
	
	if (matching(arr1, rightSlash, length))
		score += time;
	else if (matching(arr2, rightSlash, length))
		score += time;
	else if (matching(arr3, rightSlash, length))
		score += time;
	else if (matching(arr4, rightSlash, length))
		score += time;
	else if (matching(arr5, rightSlash, length))
		score += time;
	else if (matching(arr6, rightSlash, length))
		score += time;
	else if (matching(arr7, rightSlash, length))
		score += time;
	else if (matching(arr8, rightSlash, length))
		score += time;
	else if (matching(arr9, rightSlash, length))
		score += time;
	else if (matching(arr10, rightSlash, length))
		score += time;
	else if (matching(arr11, rightSlash, length))
		score += time;
	else if (matching(arr12, rightSlash, length))
		score += time;
	return score;
}
int Scan::five(int x, int y) {
	int length = 5;
	int arr1[] = { 1,1,1,1,1};
	int time = timeScore[Five];
	if (matching(arr1, row, length))
		return time;
	if (matching(arr1, col, length))
		return time;
	if (matching(arr1, leftSlash, length))
		return time;
	if (matching(arr1, rightSlash, length))
		return time;
	return 0;
}
void Scan::init(short my, short empty, short enemy,short** table,int max,int *val) {
	myColor = my;
	emptyColor = empty;
	enemyColor = enemy;
	pieces = table;
	this->max = max;
	if (val != NULL)
		for (int i = 0; i < 8; i++) {
			timeScore[i] = val[i];
		}
}
int Scan::scan(int x,int y) {
	row = new vector<int>;
	col = new vector<int>;
	leftSlash = new vector<int>;
	rightSlash = new vector<int>;
	scanRow(x, y, area);
	scanCol(x, y, area);
	scanLeftSlash(x, y, area);
	scanRightSlash(x, y, area);
	int res;
    res=fourToFive(x,y)+rushFour(x,y)+five(x, y)+aliveThree(x,y)+rushThree(x,y)+sleepThree(x,y)+aliveTwo(x,y)+ sleepTwo(x,y);
	delete row;
	delete col;
	delete leftSlash;
	delete rightSlash;
	return res;
}
