//
// Created by Elaina on 2023/11/30.
//

#include "window.h"
#include "iostream"
#include "chess.h"
#include "unistd.h"
window::window(int width, int length)
{
	hwnd = initgraph(width, length);
	SetWindowText(hwnd, windowTitle);
	setbkcolor(WHITE);//背景颜色
	setbkmode(TRANSPARENT);//文字透明背景
	//载入图片
	loadimage(&menuImage, "../images/Elaina2.jpg", 1280, 720, false);
	loadimage(&chessBroadImg, "../images/ElainaPlay.png", 1280, 720, false);

	//初始化按钮
	startGame 	= new button(980, 300, 70, 300, "开始游戏", buttonType::text);
	gameRecord 	= new button(980, 400, 70, 300, "游戏记录", buttonType::text);
	aboutUs 	= new button(980, 500, 70, 300, "关于", buttonType::text);
	menuExit 	= new button(980, 600, 70, 300, "退出游戏", buttonType::text);
	PVPmode 	= new button(980, 300, 70, 300, "人人对战", buttonType::text);
	PVEmode1 	= new button(980, 400, 70, 300, "人机模式", buttonType::text);
	PVEselect1 	= new button(980, 200, 70, 300, "困难先手", buttonType::text);
	PVEselect2 	= new button(980, 300, 70, 300, "困难后手", buttonType::text);
	PVEselect3 	= new button(980, 400, 70, 300, "简单先手", buttonType::text);
	PVEselect4 	= new button(980, 500, 70, 300, "简单后手", buttonType::text);
	PVEmode2 	= new button(1000, 500, 200, 100, "人机模式（困难）", buttonType::text);
	prevPiece 	= new button(1000, 600, 200, 100, "上一步", buttonType::text);
	nextPiece 	= new button(1000, 300, 200, 100, "下一步", buttonType::text);
	save 		= new button(980, 500, 70, 300, "保存", buttonType::text);
	backToMenu 	= new button(980, 600, 70, 300, "回到菜单", buttonType::text);
	pageUp 		= new button(980, 50, 70, 300, "上一页", buttonType::text);
	pageDown 	= new button(980, 150, 70, 300, "下一页", buttonType::text);
	for(int num =0;num<10;num++)
		enter[num] = new button(750,80+50* num,50,130,"读取",buttonType::rectangle);

}

void window::openMenu()
{
	state_ = MENU_WINDOW;
	cleardevice();
	putimage(0, 0, &menuImage);
	settextstyle(150, 0, "");
	settextcolor(BLACK);
	outtextxy(50, 90, "五子棋");
	startGame->show();
	gameRecord->show();
	aboutUs->show();
	menuExit->show();
	while (1)
	{
		msg = getmessage();
		if (startGame->state(msg))
		{
			state_ = OPTION_WINDOW;
			break;
		}
		if (gameRecord->state(msg))
		{
			state_ = SAVE_WINDOW;
			break;
		}
		if (aboutUs->state(msg))
		{
			//to do
		}
		if (menuExit->state(msg))
		{
			//to do
		}
	}
	if (state_ == OPTION_WINDOW)
		openOpt();
	else if(state_ = SAVE_WINDOW)
		openSave();
}

void window::openPlay(int mode, int difficulty, const chessData& t)
{
	state_ = PLAY_WINDOW;
	mode_ = mode;
	difficulty_ = difficulty;
	cleardevice();
	putimage(0, 0, &chessBroadImg);
	backToMenu->show();
	save->show();
	//putimage(0,0,&chessBroadImg);
	setlinecolor(BLACK);
	for (int i = 1; i <= 15; i++)
	{
		line(50, 5 + 45 * i, 680, 5 + 45 * i);
		line(5 + 45 * i, 50, 5 + 45 * i, 680);
	}
	settextstyle(30,0,"行楷");
	outtextxy(900,100,"现在该下：");
	setfillcolor(BLACK);
	fillcircle( 920, 150 , 18);
	bool winFlag = true;
	bool aichessflag = true;
	chessPlay.chessClear(mode,t,difficulty_);
	if(chessPlay.judgeNew()!=1)
		winFlag = false;
	sleep(1);
	while (1)
	{
		msg = getmessage();

		if(backToMenu->state(msg))
		{
			state_ = MENU_WINDOW;
			break;
		}
		else if(save->state(msg))
		{
			chessPlay.save();
			state_ = MENU_WINDOW;
			break;
		}
		else if (msg.lbutton&&winFlag)
		{
			/*std::cout << "x:" << msg.x << "y:" << msg.y << std::endl;
			std::cout << "x:" << int((msg.x - 22.5) / 45) << "y:" << int((msg.y - 22.5) / 45) << std::endl;*/
			if(mode_ ==PVPMODE)
			{
				int i = (msg.x - 22.5) / 45;
				int j = (msg.y - 22.5) / 45;
				if (i >= 0 && i <= 14 && j >= 0 && j <= 14)
				{
					chessPlay.putchess(i, j);
					if(chessPlay.judgeNew()!=1)
					{
						std::cout<<"win!!!";
						winFlag = false;
					}
				}
			}
			else if(mode_ == PVEMODE1||mode_ ==PVEMODE2)
			{
				if(mode_ == PVEMODE2&&aichessflag)
				{
					chessPlay.putchess(7,7);//机器下中间
					aichessflag = false;
				}
				int i = (msg.x - 22.5) / 45;
				int j = (msg.y - 22.5) / 45;
				if (i >= 0 && i <= 14 && j >= 0 && j <= 14)
				{
					if(!chessPlay.putchess(i, j))
						continue;
					if(chessPlay.judgeNew()!=1)
					{
						std::cout<<"win!!!";
						winFlag = false;
						continue;
					}
				chessPlay.simpleAI();
				}
				if(chessPlay.judgeNew()!=1)
				{
					std::cout<<"win!!!";
					winFlag = false;
					continue;
				}
			}

		}

	}
	if(state_ == MENU_WINDOW)
		openMenu();
}

void window::openOpt()
{
	state_ = OPTION_WINDOW;
	cleardevice();
	putimage(0, 0, &menuImage);
	PVPmode->show();
	PVEmode1->show();
	backToMenu->show();
	while(1)
	{
		msg = getmessage();

		if(PVPmode->state(msg))
		{
			state_ = PLAY_WINDOW;
			mode_ = PVPMODE;
			break;
		}
		if(PVEmode1->state(msg))
		{
			state_ = OPTSEL_WINDOW;
			break;
		}
		if(backToMenu->state(msg))
		{
			state_ = MENU_WINDOW;
			break;
		}
	}
	if(state_==PLAY_WINDOW)
	{
		openPlay(mode_);
	}
	else if(state_==OPTSEL_WINDOW)
	{
		openOptSel();
	}
	else if(state_==MENU_WINDOW)
	{
		openMenu();
	}

}

void window::openOptSel()
{
	state_ = OPTSEL_WINDOW;
	cleardevice();
	putimage(0, 0, &menuImage);
	PVEselect1->show();
	PVEselect2->show();
	backToMenu->show();
	while (1)
	{
		msg = getmessage();

		if(PVEselect1->state(msg))
		{
			mode_ = PVEMODE1;
			difficulty_ = HARDMODE;
			state_ = PLAY_WINDOW;
			break;
		}
		else if(PVEselect2->state((msg)))
		{
			mode_ = PVEMODE2;
			difficulty_ = HARDMODE;
			state_ = PLAY_WINDOW;
			break;
		}
		else if(PVEselect3->state(msg))
		{
			mode_ = PVEMODE1;
			difficulty_ = EASYMODE;
			state_ = PLAY_WINDOW;
			break;
		}
		else if(PVEselect4->state(msg))
		{
			mode_ = PVEMODE2;
			difficulty_ = EASYMODE;
			state_ = PLAY_WINDOW;
			break;
		}
		else if(backToMenu->state(msg))
		{
			state_ = MENU_WINDOW;
			break;
		}

	}
	if(state_==MENU_WINDOW)
	{
		openMenu();
	}
	else if(state_==PLAY_WINDOW)
	{
		openPlay(mode_,difficulty_);
	}
}

void window::openSave()
{
	state_ = SAVE_WINDOW;
	table tableChess(chessPlay.load());
	cleardevice();
	putimage(0, 0, &menuImage);
	backToMenu->show();
	pageDown->show();
	pageUp->show();
	tableChess.show();
	chessData t;
	while(1)
	{
		msg = getmessage();
		if(backToMenu->state(msg))
		{
			state_ = MENU_WINDOW;
			break;
		}
		else if(pageUp->state(msg))
		{
			tableChess.pageup();
		}
		else if(pageDown->state(msg))
		{
			tableChess.pagedown();
		}
		else
		{
			bool flag =0;
			for(int i =0;i<10;i++)
				if(enter[i]->state(msg))
				{
					t = tableChess.entergame(i);
					if(t.id!=0)
					{
						flag =1;
						state_ = PLAY_WINDOW;
						break;
					}
				}
			if(flag)
				break;
		}
	}
	if(state_ == MENU_WINDOW)
	{
		openMenu();
	}
	else if(state_ == PLAY_WINDOW)
	{
		openPlay(t.mode,t.difficulty,t);
	}

}

