#pragma once
#include<easyx.h>
#include <conio.h>
#include<time.h>
#include<graphics.h>
#include"table.h"
#include"robot.h"
#include"Person.h"
#include<time.h>
class game {
private:
	table myTable;
	robot myRobot;
	int peopleColor = 1;
	int robotColor = 2;
	short **pieces=NULL;//0空1人2电脑
	short win = 0;
	Pixel lastPiece;
	bool run = 1;
	bool reBegin = 0;
	bool showPositionValue = 0;
	double sleepTime=0;
	bool sleep = 0;
public:
	void Init();
	bool begin();
	Pixel getPiece();
	bool noPiece(int x, int y);
	void showTheWinner();
	bool Win(int x, int y, int color);
	short getLeft(int x, int y, int color);
	short getRight(int x, int y, int color);
	short getUp(int x, int y, int color);
	short getDown(int x, int y, int color);
	short getLeftUp(int x, int y, int color);
	short getLeftDown(int x, int y, int color);
	short getRightUp(int x, int y, int color);
	short getRightDown(int x, int y, int color);
	bool peoplePlay(People&people);
	void exit();
	bool robotPlay(robot& Robot);
	~game() {
		if (pieces != NULL) {
			for (int i = 0; i < 20; i++)
				delete[]pieces[i];
			delete[]pieces;
		}
	}
	int handleMessage(MOUSEMSG m);
	MOUSEMSG getClick();
	void pvp();
	void pve();
	void eve();
	void giveColors();
	int eveClick();
	void test();
};
void game::Init() {
	int SWidth = 30;
	COLORREF bkcolor = RGB(200, 204, 38);
	pieces = new short*[20];
	for (int i = 0; i < 20; i++) {
		pieces[i] = new short[20];
		for (int j = 0; j < 20; j++) {
			pieces[i][j] = 0;
		}
	}
	lastPiece.x = -1;
	lastPiece.y = -1;
	myTable.setTable(SWidth, bkcolor,pieces);
	myTable.drawTable();
}
bool game::begin() {
	
	return 0;
}
Pixel game::getPiece() {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.mkLButton) {
			m.x += myTable.sWidth / 2;
			m.y += myTable.sWidth / 2;
			m.x /= myTable.sWidth;
			m.y /= myTable.sWidth;
			m.x -= 2;
			m.y -= 2;
			if (noPiece(m.x, m.y)) {
				break;
			}
		}
	}
	pieces[m.y][m.x] = 1;
	myTable.drawPiece(m.x, m.y, peopleColor);
	if (Win(m.x, m.y, 1)) {
		win = 1;
	}
	return Pixel(m.x, m.y);
}
bool game::noPiece(int x, int y) {
	if (x < 1 || x>19 || y < 1 || y>19) {
		return 0;
	}
	return !pieces[y][x];
}
bool game::Win(int x, int y, int color) {
	if (getLeft(x, y, color) + getRight(x, y, color) > 3)
		return 1;
	else if (getUp(x, y, color) + getDown(x, y, color) > 3)
		return 1;
	else if (getLeftUp(x, y, color) + getRightDown(x, y, color) > 3)
		return 1;
	else if (getLeftDown(x, y, color) + getRightUp(x, y, color) > 3)
		return 1;

	return 0;
}
short game::getLeft(int x, int y, int color) {
	int end = x - 4, count = 0;
	if (x - 4 < 1)
		end = 1;
	for (int i = x - 1; i >= end; i--) {
		if (pieces[y][i] == color)
			count++;
		else
			break;
	}
	return count;
}
short game::getRight(int x, int y, int color) {
	int end = x + 4, count = 0;
	if (x + 4 > 19)
		end = 19;
	for (int i = x + 1; i <= end; i++) {
		if (pieces[y][i] == color)
			count++;
		else
			break;
	}
	return count;
}
short game::getUp(int x, int y, int color) {
	int end = y - 4, count = 0;
	if (y - 4 < 1)
		end = 1;
	for (int i = y - 1; i >= end; i--) {
		if (pieces[i][x] == color)
			count++;
		else
			break;
	}
	return count;
}
short game::getDown(int x, int y, int color) {
	int end = y + 4, count = 0;
	if (y + 4 > 19)
		end = 19;
	for (int i = y + 1; i <= end; i++) {
		if (pieces[i][x] == color)
			count++;
		else
			break;
	}
	return count;
}
short game::getLeftUp(int x, int y, int color) {
	int endx = x - 4, count = 0, endy = y - 4;
	if (x - 4 < 1)
		endx = 1;
	if (endy < 1)
		endy = 1;
	for (int i = x - 1, j = y - 1; i >= endx && j >= endy; i--, j--) {
		if (pieces[j][i] == color)
			count++;
		else
			break;
	}
	return count;
}
short game::getLeftDown(int x, int y, int color) {
	int endx = x - 4, count = 0, endy = y + 4;
	if (x - 4 < 1)
		endx = 1;
	if (endy > 19)
		endy = 19;
	for (int i = x - 1, j = y + 1; i >= endx && j <= endy; i--, j++) {
		if (pieces[j][i] == color)
			count++;
		else
			break;
	}
	return count;
}
short game::getRightUp(int x, int y, int color) {
	int endx = x + 4, count = 0, endy = y - 4;
	if (endx > 19)
		endx = 19;
	if (endy < 1)
		endy = 1;
	for (int i = x + 1, j = y - 1; i <= endx && j >= endy; i++, j--) {
		if (pieces[j][i] == color)
			count++;
		else
			break;
	}
	return count;
}
short game::getRightDown(int x, int y, int color) {
	int endx = x + 4, count = 0, endy = y + 4;
	if (endx > 19)
		endx = 19;
	if (endy > 19)
		endy = 19;
	for (int i = x + 1, j = y + 1; i <= endx && j <= endy; i++, j++) {
		if (pieces[j][i] == color)
			count++;
		else
			break;
	}
	return count;
}
void game::showTheWinner() {
	if (win == 0) {
		myTable.noWinner();
	}
	else if (win == 1) {
		myTable.peopleWin();
	}
	else if (win == 2) {
		myTable.computerWin();
	}

}
bool game::peoplePlay(People& people) {
	Pixel pixel;
	pixel = people.getNextPiece();
	if (pixel.x != -1) {
		pieces[pixel.y][pixel.x] = people.peopleColor;
		myTable.drawPiece(pixel.x, pixel.y, people.peopleColor);
		lastPiece.copy(pixel);
		return Win(pixel.x, pixel.y, people.peopleColor);
	}
	else {
		lastPiece.copy(pixel);
		return 0;
	}
}
bool game::robotPlay(robot& Robot) {
	if (sleep);
	Sleep(1000 * sleepTime);
	Pixel pixel;
	pixel.copy(Robot.getNextPiece(lastPiece.x,lastPiece.y));
	if (showPositionValue) {
		Robot.showPositionValue();
		cout << "next" << pixel.x << " " << pixel.y << endl;
	}
	pieces[pixel.y][pixel.x] = Robot.robotColor;
	Robot.robotPut(pixel.x, pixel.y);
	myTable.drawPiece(pixel.x, pixel.y, Robot.robotColor);
	Robot.updatePositionValue(pixel.x, pixel.y);
	if(showPositionValue)
	Robot.showPositionValue();
	lastPiece.copy(pixel);
	return Win(pixel.x, pixel.y, Robot.robotColor);
}
void game::exit() {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.mkLButton) {
			break;
		}
	}
}
int game::handleMessage(MOUSEMSG m) {
	return myTable.handleMessage(m);
}
MOUSEMSG game::getClick() {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.mkLButton) {
			m.x += myTable.sWidth / 2;
			m.y += myTable.sWidth / 2;
			m.x /= myTable.sWidth;
			m.y /= myTable.sWidth;
			m.x -= 2;
			m.y -= 2;
			if (noPiece(m.x, m.y)||handleMessage(m)) {
				break;
			}
		}
	}
	return m;
}
void game::pvp() {
	run = 1;
	int re;
	while (run) {
		Init();
		myTable.drawButtons();
		giveColors();
		bool peopleTime = 1;
		if (peopleColor == 2) {
			peopleTime = 0;
		}
		int maxTime = 19 * 19;
		People people0;
		people0.init(pieces, peopleColor, &myTable, "玩家一");
		People people1;
		people1.init(pieces, robotColor, &myTable, "玩家二");
		int num = 0;
		MOUSEMSG m;
		while (maxTime) {
			num++;
			cout << num << endl;
			myTable.showNum(num);
			if (peopleTime) {
				if (peoplePlay(people0)) {
					myTable.showWinner(people0.name.c_str());
					break;
				}
				else if (lastPiece.x==-1) {
					if (lastPiece.y == 1)
						run = 0;
					break;
				}
			}
			else {
				if (peoplePlay(people1)) {
					myTable.showWinner(people1.name.c_str());
					break;
				}
				else if (lastPiece.x == -1) {
					if (lastPiece.y == 1)
						run = 0;
					break;
				}

			}
			peopleTime = !peopleTime;
			maxTime--;
		}
		if (maxTime == 0) {
			myTable.showWinner("NO ONE");
		}
		if (lastPiece.x != -1) {
			while ((re = eveClick()) == 0);
			if (re == 1) {
				run = 0;
			}
		}
	}
}
void game::pve() {
	run = 1;
	int re;
	while (run) {
		Init();
		showPositionValue = 0;
		myTable.drawButtons();
		giveColors();
		bool peopleTime = 1;
		if (peopleColor == 2) {
			peopleTime = 0;
		}
		int maxTime = 19 * 19;
		People people0;
		people0.init(pieces, peopleColor, &myTable, "玩家");
		robot Robot1;
		Robot1.init(pieces, robotColor, myTable, "机器人");
		int num = 0;
		MOUSEMSG m;
		while (maxTime) {
			num++;
			if(showPositionValue)
			cout << num << endl;
			myTable.showNum(num);
			if (peopleTime) {
				if (peoplePlay(people0)) {
					myTable.showWinner(people0.name.c_str());
					break;
				}
				else if (lastPiece.x == -1) {
					if (lastPiece.y == 1)
						run = 0;
					break;
				}
			}
			else {
				if (robotPlay(Robot1)) {
					myTable.showWinner(Robot1.name.c_str());
					break;
				}

			}
			peopleTime = !peopleTime;
			maxTime--;
		}
		if (maxTime == 0) {
			myTable.showWinner("NO ONE");
		}
		if (lastPiece.x != -1){
			while ((re = eveClick()) == 0);
			if (re == 1) {
				run = 0;
			}
		}
	}
}
void game::eve() {
	run = 1;
	int re;
	int firstSrand = -1;
	while (run) {
		Init();
		lastPiece.y = firstSrand;
		sleepTime = 0.01;
		giveColors();
		bool peopleTime = 1;
		if (peopleColor == 2) {
			peopleTime = 0;
		}
		int maxTime = 19 * 19;
		robot Robot1;
		Robot1.init(pieces, robotColor, myTable, "1号");
		robot Robot2;
		Robot2.init(pieces, peopleColor, myTable, "2号");
		int num = 0;
		MOUSEMSG m;
		while (maxTime) {
			num++;
			re = 0;
			if(showPositionValue)
			cout << num << endl;
			myTable.showNum(num);
			if (peopleTime) {
				if (robotPlay(Robot2)) {
					myTable.showWinner(Robot2.name.c_str());
					break;
				}
			}
			else {
				if (robotPlay(Robot1)) {
					myTable.showWinner(Robot1.name.c_str());
					break;
				}

			}
			peopleTime = !peopleTime;
			maxTime--;
		}
		if (maxTime == 0) {
			myTable.showWinner("NO ONE");
		}
		myTable.drawButtons();
	    while ((re = eveClick()) == 0);
		if (re == 1) {
			run = 0;
		}
	}
}
void game::test() {
	run = 1;
	int re;
	while (run) {
		Init();
		myTable.drawButtons();
		giveColors();
		bool peopleTime = 1;
		if (peopleColor == 2) {
			peopleTime = 0;
		}
		int maxTime = 19 * 19;
		People people0;
		people0.init(pieces, peopleColor, &myTable, "玩家一");
		People people1;
		people1.init(pieces, robotColor, &myTable, "玩家二");
		int num = 0;
		MOUSEMSG m;
		while (maxTime) {
			num++;
			cout << num << endl;
			myTable.showNum(num);
			if (peopleTime) {
				if (peoplePlay(people0)) {
					myTable.showWinner(people0.name.c_str());
					break;
				}
				else if (lastPiece.x == -1) {
					if (lastPiece.y == 1)
						run = 0;
					break;
				}
			}
			else {
				if (peoplePlay(people1)) {
					myTable.showWinner(people1.name.c_str());
					break;
				}
				else if (lastPiece.x == -1) {
					if (lastPiece.y == 1)
						run = 0;
					break;
				}

			}
			peopleTime = !peopleTime;
			maxTime--;
		}
		if (maxTime == 0) {
			myTable.showWinner("NO ONE");
		}
		if (lastPiece.x != -1) {
			while ((re = eveClick()) == 0);
			if (re == 1) {
				run = 0;
			}
		}
	}
}
void game::giveColors() {
	srand(time(NULL));
	peopleColor = rand() % 2 + 1;
	if (peopleColor == 1)
		robotColor = 2;
	else
		robotColor = 1;
}
int game::eveClick() {
	 MOUSEMSG m;
     m = GetMouseMsg();
     if (m.mkLButton) {
		 return myTable.handleMessage(m);
     }
	 return 0;
}
