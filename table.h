#pragma once
#include<easyx.h>
#include <conio.h>
#include<graphics.h>
struct ButtonPlace {
	int left;
	int top;
	int right;
	int bottom;
	COLORREF color;
	char name[20];
	
};
using namespace std;
class table {
protected:
	int height;
	int width;
	int sWidth;
	int reButtonWidth;
	int exitButtonWidth;
	ButtonPlace reButton;
	ButtonPlace exitButton;
	COLORREF bkcolor;
	short **pieces;
	string reName = "重新开始";
	string exitName = "结束游戏";
public:
	void drawTable();
	void drowButton(int x, int y, int Width, string name);
	void setTable(int sWidth, COLORREF bkcolor,short** pieces);
	void drawPiece(int x, int y, int color);//1为黑，2为白
	void peopleWin();
	void showWinner(string name);
	void computerWin();
	void noWinner();
	bool noPiece(int x, int y);
	void showValue(int x, int y, int value);
	void showNum(int num);
	void showString(int x,int y,string str);
	int handleMessage(MOUSEMSG m);//没有消息为0，退出为1，重新开始为2
	bool reButtonClicked(MOUSEMSG m);
	bool exitButtonClicked(MOUSEMSG m);
	void drawButtons();
	friend class game;
	friend class People;
};
void table::drawTable() {
	initgraph(width, height);
	setfillcolor(bkcolor);
	fillrectangle(0, 0, width, height);
	setlinecolor(BLACK);
	for (int i = 1; i <= 19; i++) {
		line(sWidth * 2, sWidth * i + sWidth * 2, sWidth * 22, sWidth * i + sWidth * 2);
		line(sWidth * i + sWidth * 2, sWidth * 2, sWidth * i + sWidth * 2, sWidth * 22);
	}
}
void table::drowButton(int x, int y, int Width, string name) {
	setfillcolor(RGB(0,47,167));
	setlinecolor(BLACK);
	fillrectangle(x-5,y, x+Width+5, y+Width);
	showString(x , y+Width/9*4 , name);
	if (name == reName) {
		reButton = { x - 5,y, x + Width + 5, y + Width };
	}
	else if (name == exitName) {
		exitButton = { x - 5,y, x + Width + 5, y + Width };
	}
}
void table::setTable(int sWidth, COLORREF bkcolor,short** pieces) {
	height = sWidth * 24;
	width = sWidth * 24+sWidth * 4;//+ sWidth * 8;
	this->bkcolor = bkcolor;
	this->sWidth = sWidth;
	this->pieces = pieces;
	reButtonWidth = sWidth*2;
	exitButtonWidth = sWidth*2;
}
void table::drawPiece(int x, int y,int color) {
	if (color == 1) {
		setfillcolor(BLACK);
	}
	else {
		setfillcolor(WHITE);
	}
	setlinecolor(BLACK);
	x += 2;
	y += 2;
	fillcircle(x * sWidth, y * sWidth, sWidth / 2 - 1);
}
void table::peopleWin() {
	RECT rect = { 0,0,height,height };
	drawtext(_T("YOU WIN!"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void table::computerWin() {
	RECT rect = { 0,0,height,height };
	drawtext(_T("YOU LOSE!"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void table::noWinner() {
	RECT rect = { 0,0,height,height };
	drawtext(_T("DRAW!"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
bool table::noPiece(int x, int y) {
	if (x < 1 || x>19 || y < 1 || y>19) {
		return 0;
	}
	return !pieces[y][x];
}
wchar_t* multi_Byte_To_Wide_Char(const string& pKey)
{
	//string 转 char*
	const char* pCStrKey = pKey.c_str();
	//第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
	wchar_t* pWCStrKey = new wchar_t[pSize];
	//第二次调用将单字节字符串转换成双字节字符串
	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
	return pWCStrKey;
}
void table::showWinner(string name) {
	string out = name+" WIN!";
	int length = out.length();
	setlinecolor(BLACK);
	TCHAR s[100];
	_stprintf_s(s, _T("%s"), multi_Byte_To_Wide_Char(out));
	setbkmode(TRANSPARENT);
	int nWidth = sWidth;
	int nHeight = sWidth*2;
	settextstyle(nHeight, nWidth, _T("楷体"));
	int x = sWidth*(3+(19-length)/2);
	int y = 0;
	settextcolor(BLACK);
	outtextxy(x, y, s);
}
void table::showValue(int x, int y, int value) {
	TCHAR s[100];
	_stprintf_s(s, _T("%d"), value);
	x += 2;
	y += 2;
	setbkmode(TRANSPARENT);
	outtextxy(x * sWidth, y * sWidth, s);
}
void table::showNum(int num) {
	setfillcolor(bkcolor);
	setlinecolor(bkcolor);
	fillrectangle(0, 0, sWidth*2, sWidth*2);
	TCHAR s[100];
	_stprintf_s(s, _T("%d"), num);
	setbkmode(TRANSPARENT);
	outtextxy(sWidth, sWidth, s);
}
void table::showString(int x, int y, string str) {
	setlinecolor(WHITE);
	TCHAR s[100];
	_stprintf_s(s, _T("%s"), multi_Byte_To_Wide_Char(str));
	setbkmode(TRANSPARENT);
	int nWidth = 8;
	int nHeight = 20;
	settextcolor(BLACK);
	settextstyle(nHeight, nWidth, _T("宋体"));
	outtextxy(x, y, s);
}
int table::handleMessage(MOUSEMSG m) {
	if (reButtonClicked(m)) {
		return 2;
	}
	else if (exitButtonClicked(m)) {
		return 1;
	}
	return 0;
}
bool table::reButtonClicked(MOUSEMSG m) {
	if (m.x > reButton.left && m.x<reButton.right && m.y>reButton.top && m.y < reButton.bottom) {
		return 1;
	}
	return 0;
}
bool table::exitButtonClicked(MOUSEMSG m) {
	if (m.x > exitButton.left && m.x<exitButton.right && m.y>exitButton.top && m.y < exitButton.bottom) {
		return 1;
	}
	return 0;
}
void table::drawButtons() {
    drowButton(sWidth * 23, sWidth * (24 / 3) * 1, reButtonWidth, reName);
	drowButton(sWidth * 23, sWidth * (24 / 3) * 2, exitButtonWidth, exitName);
}
