//
// Created by Elaina on 2023/11/30.
//

#ifndef CHESS_NEW_SOURCES_WINDOW_H_
#define CHESS_NEW_SOURCES_WINDOW_H_
#include "widget.h"
#include "string"
#include "button.h"
#include "chess.h"
#include "table.h"
#define MENU_WINDOW 1
#define INFO_WINDOW 2
#define PLAY_WINDOW 3
#define SAVE_WINDOW 4
#define OPTION_WINDOW 5
#define OPTSEL_WINDOW 6
#define PVPMODE 100
#define PVEMODE1 200
#define PVEMODE2 300
using std::wstring;
class window:public widget
{
 protected:
	LPCTSTR windowTitle = "五子棋";
	int state_;
	int mode_;
	IMAGE menuImage;
	IMAGE chessBroadImg;


 public:
	window(int width =1280,int length=720);
	void openMenu();
	void openOpt();
	void openInfo();
	void openPlay(int mode = PVPMODE,const chessData& t ={});
	void openSave();
	void openMSG();
	void openOptSel();

	HWND hwnd;
	ExMessage msg;
	button *enter[10];
 private:
	chess chessPlay;

	button *startGame;//各个按钮
	button *gameRecord;
	button *aboutUs;
	button *menuExit;
	button *PVPmode;
	button *PVEmode1;
	button *PVEmode2;
	button *PVEselect1;
	button *PVEselect2;
	button *prevPiece;
	button *nextPiece;
	button *save;
	button *backToMenu;
	button *pageUp;
	button *pageDown;

};
#endif //CHESS_NEW_SOURCES_WINDOW_H_
