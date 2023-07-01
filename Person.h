#pragma once
#include"robot.h"
#include"table.h"
#include<string.h>
using namespace std;
class People {
private:
	short** pieces;
	short peopleColor;
	table* myTable;
	string name;
public:
	void init(short** pieces, short peopleColor,table* myTable,string name);
	Pixel getNextPiece();
	friend class game;
};
void People::init(short** pieces, short peopleColor, table* myTable, string name){
	this->pieces = pieces;
	this->peopleColor = peopleColor; 
	this->myTable = myTable;
	this->name = name;
}
Pixel People::getNextPiece() {
	MOUSEMSG m;
	int x, y;
	while (1) {
		m = GetMouseMsg();
		if (m.mkLButton) {
			if ((y=myTable->handleMessage(m))!=0) {
				m.y = y;
				m.x = -1;
				break;
			}
			m.x += myTable->sWidth / 2;
			m.y += myTable->sWidth / 2;
			m.x /= myTable->sWidth;
			m.y /= myTable->sWidth;
			m.x -= 2;
			m.y -= 2;
			if (myTable->noPiece(m.x, m.y)) {
				break;
			}
		}
	}
	return Pixel(m.x, m.y);
}