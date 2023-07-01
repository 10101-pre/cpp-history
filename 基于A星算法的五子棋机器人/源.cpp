#include<iostream>
#include<easyx.h>
#include <conio.h>
#include<graphics.h>
#include"table.h"
#include"game.h"
#include"menu.h"
using namespace std;
game myGame;
int main() {  
	MainMenu menu;
	menu.setTable(30, RGB(200, 204, 38));
	menu.drawMenu();
	closegraph();
}