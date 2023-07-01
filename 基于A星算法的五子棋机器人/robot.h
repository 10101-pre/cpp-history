#pragma once
#include<easyx.h>
#include <conio.h>
#include<graphics.h>
#include<vector>
#include"Scan.h"
#include<iomanip>
#include<time.h>
class Pixel {
public:
	int x=1;
	int y=1;
	Pixel() {};
	Pixel(int x, int y);
	void copy(Pixel& pixel);
};
Pixel::Pixel(int x, int y) {
	this->x = x;
	this->y = y;
}
void Pixel::copy(Pixel& pixel) {
	x = pixel.x;
	y = pixel.y;
}
class robot {
private:
	short** pieces;
	short robotColor;
	short enemyColor;
	int PositionValue[20][20] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,9,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
	    0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
	int initPositionValue[20][20] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,9,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,7,7,7,7,7,7,7,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,1,0,
		0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
	Scan myScanner;
	Scan enemyScanner;
	int area = 5;
	int max = 10000000;
	table* myTable;
	string name;
	Pixel best;
public:
	void init(short** pieces,short robotColor, table& graph, string name);
	Pixel&getNextPiece(int x=-1,int y=-1);
	void enemyPut(int x, int y);
	void getTheBest();
	void robotPut(int x, int y);
	int Scan(int x, int y);
	void showPositionValue();
	void updatePositionValue(int x, int y);
	friend class game;
};
void robot::init(short** pieces, short robotColor,table&graph,string name) {
	this->pieces = pieces;
	this->robotColor = robotColor;
	this->name = name;
	short enemy = 2;
	short empty = 0;
	if (robotColor == 2)
		enemy = 1;
	myTable = &graph;
	myScanner.init(robotColor, empty, enemy, pieces,max);
	int enemyVal[] = { max*2,8000,5000,4000,500,200,50,max*3 };
	//FourToFive, RushFour, AliveThree, RushThree, SleepThree, AliveTwo, SleepTwo,Five 
	//max,8000,5000,4000,500,200,50,max*8
	enemyScanner.init(enemy, empty, robotColor, pieces,max, enemyVal);
	enemyColor = enemy;
}
Pixel& robot::getNextPiece(int x, int y) {
	if (x != -1 && y != -1) {
		enemyPut(x, y);
		updatePositionValue(x, y);
	}
	if (x == -1 && y == -1) {
		srand(time(NULL));
		int x = rand() % 10 + 5;
		int y = rand() % 10 + 5;
		best.x = x;
		best.y = y;
		return best;
	}
	getTheBest();
	//robotPut(best.x,best.y);
	return best;
}
void robot::enemyPut(int x, int y) {
	PositionValue[y][x] = -1;
} 
void robot::getTheBest() {
	Pixel pixel;
	pixel.x = -1;
	pixel.y = -1;
	int mymax = -1;
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j < 20; j++) {
			if (mymax < PositionValue[i][j]) {
				mymax = PositionValue[i][j];
				pixel.x = j;
				pixel.y = i;
			}
		}
	}
	best.copy(pixel);
}
void robot::robotPut(int x, int y) {
	PositionValue[y][x] = -1;
}
int robot::Scan(int x, int y) {
	int my=myScanner.scan(x, y),enemy=enemyScanner.scan(x, y);
	return my + enemy + initPositionValue[y][x];
}
void robot::showPositionValue() {
	cout << "myColor:" << -(robotColor) << endl;
	cout << "enemyColor:" <<-(enemyColor) << endl;
	cout << setw(6) << " ";
	for (int i = 1; i < 20; i++) {
		cout << setw(6) <<i << " ";
	}
	cout << endl;
	for (int i = 1; i < 20; i++) {
		cout << setw(6) << i << " ";
		for (int j = 1; j < 20; j++) {
			if (PositionValue[i][j] == -1) {
				if(pieces[i][j]==robotColor)
					cout << setw(6) << -(robotColor) << " ";
				else {
					cout << setw(6) << -(enemyColor) << " ";
				}
			}
			else
				cout << setw(6) << PositionValue[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void robot::updatePositionValue(int x, int y) {
	int val;
	for (int i = 1; i <= area && x + i < 20; i++) {//右
		if (PositionValue[y][x + i] != -1) {
			val = Scan(x + i, y);
			if (val != 0)
				PositionValue[y][x + i] = val;
			else
				PositionValue[y][x + i] = initPositionValue[y][x + i];
		}
	}
	for (int i = 1; i <= area && x + i < 20 && y - i >= 1; i++) {//右上
		if (PositionValue[y - i][x + i] != -1) {
			val = Scan(x + i, y - i);
			if (val != 0)
				PositionValue[y - i][x + i] = val;
			else
				PositionValue[y - i][x + i] = initPositionValue[y - i][x + i];
		}
	}
	for (int i = 1; i <= area && y - i >= 1; i++) {//上
		if (PositionValue[y - i][x] != -1) {
			val = Scan(x, y - i);
			if (val != 0)
				PositionValue[y - i][x] = val;
			else
				PositionValue[y - i][x] = initPositionValue[y - i][x];
		}
	}
	for (int i = 1; i <= area && x - i >= 1 && y - i >= 1; i++) {//左上
		if (PositionValue[y - i][x - i] != -1) {
			val = Scan(x - i, y - i);
			if (val != 0)
				PositionValue[y - i][x - i] = val;
			else
				PositionValue[y - i][x - i] = initPositionValue[y - i][x - i];
		}
	}
	for (int i = 1; i <= area && x - i >= 1; i++) {//左
		if (PositionValue[y][x - i] != -1) {
			val = Scan(x - i, y);
			if (val != 0)
				PositionValue[y][x - i] = val;
			else
				PositionValue[y][x - i] = initPositionValue[y][x - i];
		}
	}
	for (int i = 1; i <= area && x - i >= 1 && y + i < 20; i++) {//左下
		if (PositionValue[y + i][x - i] != -1) {
			val = Scan(x - i, y + i);
			if (val != 0)
				PositionValue[y + i][x - i] = val;
			else
				PositionValue[y + i][x - i] = initPositionValue[y + i][x - i];
		}
	}
	for (int i = 1; i <= area && y + i < 20; i++) {//下
		if (PositionValue[y + i][x] != -1) {
			val = Scan(x, y + i);
			if (val != 0)
				PositionValue[y + i][x] = val;
			else
				PositionValue[y + i][x] = initPositionValue[y + i][x];
		}
	}
	for (int i = 1; i <= area && x + i < 20 && y + i < 20; i++) {//右下
		if (PositionValue[y + i][x + i] != -1) {
			val = Scan(x + i, y + i);
			if (val != 0)
				PositionValue[y + i][x + i] = val;
			else
				PositionValue[y + i][x + i] = initPositionValue[y + i][x + i];
		}
	}
}
