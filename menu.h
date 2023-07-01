#pragma once
#include<easyx.h>
#include <conio.h>
#include<graphics.h>
#include <string>
#include"table.h"
using namespace std;
class MainMenu:public table {
protected:
	ButtonPlace mainMenuButton;
	ButtonPlace pvpButton;
	ButtonPlace pveButton;
	ButtonPlace eveButton;
	ButtonPlace exitButton;
	enum buttonType { PVP, PVE, EVE, EXIT };
	game myGame;
	bool run = 1;
public:
	void drawMenu();
	void setTable(int sWidth, COLORREF bkcolor);
	void drawButton(const ButtonPlace&Button);
	void showMenuHead(const ButtonPlace& Button);
	void showString(int x, int y, const char* str);
	MOUSEMSG getClick();
	void getAChoice();
	int getClickType(MOUSEMSG m);
	bool pvpClicked(MOUSEMSG m);
	bool pveClicked(MOUSEMSG m);
	bool eveClicked(MOUSEMSG m);
	bool exitClicked(MOUSEMSG m);
	void pvpClicked();
	void pveClicked();
	void eveClicked();
	void exitClicked();
	bool inTheArea(MOUSEMSG m,const ButtonPlace& Button);
	friend class game;
	friend class People;
};
void MainMenu::setTable(int sWidth, COLORREF bkcolor) {
	table::setTable(sWidth, bkcolor, pieces);
	char mainMenu[] = "主菜单";
	char pvp[] = "双人战";
	char pve[] = "人机战";
	char eve[] = "双机战";
	char exit[] = "退出";
	int left = width / 7 * 2;
	int right= width / 7 * 5;
	int time =10;
	int gap = height / time / 2;
	int h = height / time;
	COLORREF color=RGB(0,47,167);
	mainMenuButton = { left,height / time*1,right,height / time * (1+2),color};
	strcpy_s(mainMenuButton.name,mainMenu);
	pvpButton = { mainMenuButton.left,mainMenuButton.bottom+gap,mainMenuButton.right ,mainMenuButton.bottom+gap+h,color};
	strcpy_s(pvpButton.name, pvp);
	pveButton = { pvpButton.left,pvpButton.bottom + gap,pvpButton.right ,pvpButton.bottom + gap + h,color };
	strcpy_s(pveButton.name, pve);
	eveButton = { pveButton.left,pveButton.bottom + gap,pveButton.right ,pveButton.bottom + gap + h,color };
	strcpy_s(eveButton.name, eve);
    exitButton = { eveButton.left,eveButton.bottom + gap,eveButton.right ,eveButton.bottom + gap + h,color };
	strcpy_s(exitButton.name, exit);
}
void MainMenu::drawButton(const ButtonPlace& Button) {
	int length = strlen(Button.name);
	setfillcolor(Button.color);
	setlinecolor(BLACK);
	fillrectangle(Button.left, Button.top, Button.right, Button.bottom);
	int x = (Button.right-Button.left-length-50)/2+Button.left;
	int y = (Button.bottom - Button.top) / 9 * 4 + Button.top;
	showString(x, y, Button.name);
}
void MainMenu::drawMenu() {
	while (run) {
		initgraph(width, height);
		setbkcolor(bkcolor);
		cleardevice();
		showMenuHead(mainMenuButton);
		drawButton(pvpButton);
		drawButton(pveButton);
		drawButton(eveButton);
		drawButton(exitButton);
		getAChoice();
		closegraph();
	}
}
void MainMenu::showMenuHead(const ButtonPlace& Button) {
	string out = Button.name;
	int length = strlen(Button.name);
	setlinecolor(BLACK);
	TCHAR s[100];
	_stprintf_s(s, _T("%s"), multi_Byte_To_Wide_Char(out));
	setbkmode(TRANSPARENT);
	int nWidth =(Button.right-Button.left)/length;
	int nHeight= Button.bottom - Button.top;
	settextstyle(nHeight, nWidth, _T("楷体"));
	int x = Button.left;
	int y = Button.top+height/20;
	settextcolor(BLACK);
	outtextxy(x, y, s);
}
void MainMenu::showString(int x, int y, const char* str) {
	string out = str;
	setlinecolor(WHITE);
	TCHAR s[100];
	_stprintf_s(s, _T("%s"), multi_Byte_To_Wide_Char(out));
	setbkmode(TRANSPARENT);
	settextstyle(20,10,_T("楷体"));
	outtextxy(x, y, s);
}
MOUSEMSG MainMenu::getClick() {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.mkLButton) {
			break;
		}
	}
	return m;
}
void MainMenu::getAChoice() {
	MOUSEMSG m;
	while (1) {
		m = getClick();
		switch (getClickType(m))
		{
		case PVP:pvpClicked(); closegraph(); return;
		case PVE:pveClicked(); closegraph(); return;
		case EVE:eveClicked(); closegraph(); return;
		case EXIT:exitClicked(); closegraph(); return;
		}
	}
}
int MainMenu::getClickType(MOUSEMSG m) {
	if (pvpClicked(m)) {
		return PVP;
	}
	else if (pveClicked(m)) {
		return PVE;
	}
	else if (eveClicked(m)) {
		return EVE;
	}
	else if (exitClicked(m)) {
		return EXIT;
	}
	return -1;
}
bool MainMenu::pvpClicked(MOUSEMSG m) {
	return inTheArea(m, pvpButton);
}
bool MainMenu::pveClicked(MOUSEMSG m) {
	return inTheArea(m, pveButton);
}
bool MainMenu::eveClicked(MOUSEMSG m) {
	return inTheArea(m, eveButton);
}
bool MainMenu::exitClicked(MOUSEMSG m) {
	return inTheArea(m, exitButton);
}
bool MainMenu::inTheArea(MOUSEMSG m, const ButtonPlace& Button) {
	if (m.x<Button.right && m.y>Button.left) {
		if (m.y<Button.bottom && m.y>Button.top)
			return 1;		
	}
	return 0;
}
void MainMenu::pvpClicked() {
	myGame.pvp();
}
void MainMenu::pveClicked() {
	myGame.pve();
}
void MainMenu::eveClicked() {
	myGame.eve();
}
void MainMenu::exitClicked() {
	run = 0;
}