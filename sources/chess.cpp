//
// Created by Elaina on 2023/12/3.
// 怎么写的又臭又长...
#include "chess.h"
#include "cstdlib"
#include "cstring"
#include "graphics.h"
#include "window.h"
#include "nlohmann/json.hpp"
using nlohmann::json;
chess::chess(int mode)//重新开始
{
	std::memset(chessBroad, 1, sizeof(chessBroad));
	data_ = load();
	mode_ = mode;
	currChess_ = BLACK_CHESS;
	step_ = 1;
	isEnd_ = false;
	xy_ ={};
}
void chess::chessClear(int mode, const chessData& t)
{
	if(t.id==0)
	{
		std::memset(chessBroad, 1, sizeof(chessBroad));
		data_ = load();
		mode_ = mode;
		currChess_ = BLACK_CHESS;
		step_ = 1;
		isEnd_ = false;
		xy_ ={};
	}
	else
	{
		std::memset(chessBroad, 1, sizeof(chessBroad));
		data_ = load();
		mode_ = mode;
		step_ = 1;
		xy_ ={};
		for(int i =0;i<t.totalStep;i++)
		{
			putchess(t.xy_[i].i_,t.xy_[i].j_);
		}
	}
}

int chess::subJudge(char* temp, const int& i, const int& j, const int& k)
{
	char tarBlack[6] = { 10, 10, 10, 10, 10, 0 };
	char tarWhite[6] = { 5, 5, 5, 5, 5, 0 };
	if (strstr(temp, tarWhite) != NULL)
	{
		red(i, j, k, temp - strstr(temp, tarWhite));
		isEnd_ = true;
		return WHITE_CHESS;
	}
	else if (strstr(temp, tarBlack) != NULL)
	{
		red(i, j, k, temp - strstr(temp, tarBlack));
		isEnd_ = true;
		return BLACK_CHESS;
	}
	else
		memset(temp, 1, 20 * sizeof(char));
	return EMPTY;
}

int chess::judgeNew()//判断赢没赢
{
	char temp[20] = {};//把一条线上的子存着
	memset(temp, 1, sizeof(temp));
	for (int k = 0; k < 4; k++)//4个方向
	{
		if (k == 0)
			for (int i = 0; i < 15; i++)
			{
				int j = 0;
				for (j = 0; j < 15; j++)
				{
					temp[j] = getChess(i, j);
				}
				int t = subJudge(temp, i, j, k);//简化一点点
				if (t != EMPTY)
					return t;
				memset(temp, 1, sizeof(temp));
			}
		if (k == 1)
			for (int j = 0; j < 15; j++)
			{
				int i = 0;
				for (i = 0; i < 15; i++)
				{
					temp[i] = getChess(i, j);
				}
				int t = subJudge(temp, i, j, k);
				if (t != EMPTY)
					return t;
				memset(temp, 1, sizeof(temp));
			}
		if (k == 2)//左斜
			for (int s = 0; s < 30; s++)
			{
				int i = 0;
				for (i = 0; i < 15; i++)
				{
					temp[i] = getChess(i, s - i);
				}
				int t = subJudge(temp, s, i, k);
				if (t != EMPTY)
					return t;
				memset(temp, 1, sizeof(temp));
			}
		if (k == 3)
			for (int s = -14; s <= 14; s++)
			{
				int i = 0;
				for (i = 0; i < 15; i++)
				{
					temp[i] = getChess(i, i + s);
				}
				int t = subJudge(temp, s, i, k);
				if (t != EMPTY)
					return t;
				memset(temp, 1, sizeof(temp));
			}
	}
	return EMPTY;
}

bool chess::putchess(int i, int j)//下棋,并存储数据
{
	chessxy temp = { i, j, currChess_,step_};
	if (chessBroad[i + 5][j + 5] == EMPTY)
	{
		chessBroad[i + 5][j + 5] = currChess_;
		xy_.push_back(temp);
		step_++;
		if (currChess_ == BLACK_CHESS)
		{
			setfillcolor(BLACK);
			fillcircle(50 + 45 * i, 50 + 45 * j, 18);
		}
		else
		{
			setfillcolor(WHITE);
			fillcircle(50 + 45 * i, 50 + 45 * j, 18);
		}
		if (currChess_ == BLACK_CHESS)
			currChess_ = WHITE_CHESS;
		else
			currChess_ = BLACK_CHESS;
		return true;
	}
	else
		return false;
}

void chess::red(int i, int j, int k, int dest)//赢了标出来
{
	for (int l = 0; l < 5; l++)
	{
		setlinecolor(RED);
		if (k == 0)
			circle(50 + 45 * (i), 50 + 45 * (l - dest), 18);
		if (k == 1)
			circle(50 + 45 * (l - dest), 50 + 45 * (j), 18);
		if (k == 2)
			circle(50 + 45 * (-dest + l), 50 + 45 * (i + dest - l), 18);
		if (k == 3)
			circle(50 + 45 * (-dest + l), 50 + 45 * (i - dest + l), 18);
	}
}

int chess::getChess(int i, int j)//这么做方便防止越界
{
	if (!(i >= 0 && i <= 14 && j >= 0 && j <= 14))
		return OUT;
	if (chessBroad[i + 5][j + 5] == BLACK_CHESS)
		return BLACK_CHESS;
	else if (chessBroad[i + 5][j + 5] == WHITE_CHESS)
		return WHITE_CHESS;
	else
		return EMPTY;
}