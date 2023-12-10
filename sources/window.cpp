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
	setbkcolor(WHITE);//������ɫ
	setbkmode(TRANSPARENT);//����͸������
	//����ͼƬ
	loadimage(&menuImage, "../images/Elaina.png", 1280, 720, false);
	loadimage(&chessBroadImg, "../images/broad.jpg", 720, 720, false);

	//��ʼ����ť
	startGame 	= new button(980, 300, 70, 300, "��ʼ��Ϸ", buttonType::rectangle);
	gameRecord 	= new button(980, 400, 70, 300, "��Ϸ��¼", buttonType::text);
	aboutUs 	= new button(980, 500, 70, 300, "����", buttonType::text);
	menuExit 	= new button(980, 600, 70, 300, "�˳���Ϸ", buttonType::text);
	PVPmode 	= new button(50, 500, 60, 220, "���˶�ս", buttonType::rectangle);
	PVEmode1 	= new button(450, 500, 70, 450, "�˻�ģʽ", buttonType::rectangle);
	PVEselect1 	= new button(980, 300, 70, 300, "�������", buttonType::rectangle);
	PVEselect2 	= new button(980, 400, 70, 300, "��Һ���", buttonType::rectangle);
	PVEmode2 	= new button(1000, 500, 200, 100, "�˻�ģʽ�����ѣ�", buttonType::text);
	prevPiece 	= new button(1000, 600, 200, 100, "��һ��", buttonType::text);
	nextPiece 	= new button(1000, 300, 200, 100, "��һ��", buttonType::text);
	save 		= new button(980, 500, 70, 300, "����", buttonType::rectangle);
	backToMenu 	= new button(980, 600, 70, 300, "�ص��˵�", buttonType::rectangle);
	pageUp 		= new button(980, 50, 70, 300, "��һҳ", buttonType::rectangle);
	pageDown 	= new button(980, 150, 70, 300, "��һҳ", buttonType::rectangle);
	for(int num =0;num<10;num++)
		enter[num] = new button(750,80+50* num,50,100,"��ȡ",buttonType::rectangle);

}

void window::openMSG()
{
	openMenu();//�ȴ����˵�

	while (1)//��Ϣѭ��
	{
		msg = getmessage();//��ȡ�����Ϣ

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
	outtextxy(820, 90, "������");
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

void window::openPlay(int mode,const chessData& t )
{
	state_ = PLAY_WINDOW;
	mode_ = mode;
	cleardevice();
	backToMenu->show();
	save->show();
	//putimage(0,0,&chessBroadImg);
	setlinecolor(BLACK);
	for (int i = 1; i <= 15; i++)
	{
		line(50, 5 + 45 * i, 680, 5 + 45 * i);
		line(5 + 45 * i, 50, 5 + 45 * i, 680);
	}
	settextstyle(30,0,"�п�");
	outtextxy(900,100,"���ڸ��£�");
	setfillcolor(BLACK);
	fillcircle( 920, 150 , 18);
	bool winFlag = true;
	bool aichessflag = true;
	chessPlay.chessClear(mode,t);
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
					chessPlay.putchess(7,7);//�������м�
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
	PVEselect1->show();
	PVEselect2->show();
	backToMenu->show();
	while (1)
	{
		msg = getmessage();

		if(PVEselect1->state(msg))
		{
			mode_ = PVEMODE1;
			state_ = PLAY_WINDOW;
			break;
		}
		else if(PVEselect2->state((msg)))
		{
			mode_ = PVEMODE2;
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
		openPlay(mode_);
	}
}

void window::openSave()
{
	state_ = SAVE_WINDOW;
	table tableChess(chessPlay.load());
	cleardevice();
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
		openPlay(t.mode,t);
	}

}

