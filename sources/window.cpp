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
	loadimage(&menuImage, "../images/Elaina.png", 1280, 720, false);
	loadimage(&chessBroadImg, "../images/broad.jpg", 720, 720, false);

	//初始化按钮
	startGame 	= new button(980, 300, 70, 300, "开始游戏", buttonType::rectangle);
	gameRecord 	= new button(980, 400, 70, 300, "游戏记录", buttonType::text);
	aboutUs 	= new button(980, 500, 70, 300, "关于", buttonType::text);
	menuExit 	= new button(980, 600, 70, 300, "退出游戏", buttonType::text);
	PVPmode 	= new button(50, 500, 60, 220, "人人对战", buttonType::rectangle);
	PVEmode1 	= new button(450, 500, 70, 450, "人机模式", buttonType::rectangle);
	PVEmode2 	= new button(1000, 500, 200, 100, "人机模式（困难）", buttonType::text);
	prevPiece 	= new button(1000, 600, 200, 100, "上一步", buttonType::text);
	nextPiece 	= new button(1000, 300, 200, 100, "下一步", buttonType::text);
	save 		= new button(1000, 300, 200, 100, "保存", buttonType::text);
	backToMenu 	= new button(980, 600, 70, 300, "回到菜单", buttonType::rectangle);

}

void window::openMSG()
{
	openMenu();//先打开主菜单

	while (1)//消息循环
	{
		msg = getmessage();//获取鼠标信息

		if (state_ == MENU_WINDOW)
		{
			if (startGame->state(msg) == 1)
				std::cout << "2333";
			if (gameRecord->state(msg) == 1)
				std::cout << gettextcolor();
			if (aboutUs->state(msg) == 1)
			{
				//
			}
			if (menuExit->state(msg) == 1)
			{
				//
			}
		}

	}
}

void window::openMenu()
{
	state_ = MENU_WINDOW;
	cleardevice();
	putimage(0, 0, &menuImage);
	settextstyle(150, 0, "");
	settextcolor(BLACK);
	outtextxy(820, 90, "五子棋");
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
			//to do
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

}

void window::openPlay()
{
	state_ = PLAY_WINDOW;
	chess chessPlay;
	cleardevice();
	backToMenu->show();
	//putimage(0,0,&chessBroadImg);
	setlinecolor(BLACK);
	for (int i = 1; i <= 15; i++)
	{
		line(50, 5 + 45 * i, 680, 5 + 45 * i);
		line(5 + 45 * i, 50, 5 + 45 * i, 680);
	}
	bool winFlag = true;
	while (1)
	{
		msg = getmessage();

		if(backToMenu->state(msg))
		{
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
			if(mode_ == PVEMODE1)
			{
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
			state_ = PLAY_WINDOW;
			mode_ = PVEMODE1;
			break;
		}
	}
	if(state_==PLAY_WINDOW)
	{
		openPlay();
		sleep(2);
	}

}