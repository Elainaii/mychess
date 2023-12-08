//
// Created by Elaina on 2023/12/4.
//
#include "chess.h"

void chess::simpleAI()
{
	chessxy ourPoint = {}, oppPoint = {};
	int ourBestScore = 0, oppBestScore = 0;//我方攻击分，对方防守分
	int ourBestSopp = 0, oppBestSour = 0;//我方攻击分最高时对方防守分
	int oppChess;
	if (currChess_ == WHITE_CHESS)
		oppChess = BLACK_CHESS;
	else
		oppChess = WHITE_CHESS;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (getChess(i, j) != EMPTY)
				continue;
			int temp = score(i, j, currChess_);//对当前的位置打分，这是进攻分
			int temp2 = score(i, j, oppChess);//防守分
				if (temp > ourBestScore)
			{
				ourBestScore = temp;
				ourBestSopp = temp2;
				ourPoint.i_ = i;
				ourPoint.j_ = j;
			}
			else if (temp == ourBestScore && temp2 > ourBestSopp)//攻击分一样高就取防守分高的点
			{
				ourBestSopp = temp2;
				ourPoint.i_ = i;
				ourPoint.j_ = j;
			}

		}
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (getChess(i, j) != EMPTY)
				continue;
			int temp = score(i, j,  oppChess);
			int temp2 = score(i, j, currChess_);
			if (temp > oppBestScore)
			{
				oppBestScore = temp;
				oppBestSour = temp2;
				oppPoint.i_ = i;
				oppPoint.j_ = j;
			}
			else if (temp == oppBestScore && temp2 > oppBestSour)//同理
			{
				oppBestSour = temp2;
				oppPoint.i_ = i;
				oppPoint.j_ = j;
			}
		}
	if (ourBestScore > oppBestScore)
	{
		putchess(ourPoint.i_, ourPoint.j_);
		currChess_ = oppChess;
	}
	else
	{
		putchess(oppPoint.i_, oppPoint.j_);
		currChess_ = oppChess;
	}
}

int chess::score(int i, int j, int who)
{
	int win5 = 0, alive4 = 0, die4 = 0, ddie4 = 0, alive3 = 0,
		dalive3 = 0, die3 = 0, alive2 = 0, dalive2 = 0, die2 = 0, nothing = 0;
	int opp = 0;
	if (who == WHITE_CHESS)
		opp = BLACK_CHESS;
	else
		opp = WHITE_CHESS;
	for (int k = 0; k < 4; k++)
	{
		int left[5] = {};
		int right[5] = {};
		chessxy le = { i, j }, ri = { i, j };
		int l = 1;
		if (k == 0)
		{
			le.j_--;
			ri.j_++;
			while (getChess(le.i_, le.j_) == who)
			{
				le.j_--;//先减一次再进来
				l++;
			}
			while (getChess(ri.i_, ri.j_) == who)
			{
				ri.j_++;
				l++;
			}

			for (int s = 0; s < 4; s++)
			{
				left[s+1] = getChess(le.i_, le.j_ - s);
				right[s+1] = getChess(ri.i_, ri.j_ + s);
			}
		}
		if (k == 1)
		{
			le.i_--;
			ri.i_++;
			while (getChess(le.i_, le.j_) == who)
			{
				le.i_--;
				l++;
			}
			while (getChess(ri.i_, ri.j_) == who)
			{
				ri.i_++;
				l++;
			}
			for (int s = 0; s < 5; s++)
			{
				left[s+1] = getChess(le.i_ - s, le.j_ );
				right[s+1] = getChess(ri.i_ + s, ri.j_ );
			}
		}
		if (k == 2)
		{
			le.j_++;
			le.i_--;
			ri.i_++;
			ri.j_--;
			while (getChess(le.i_, le.j_) == who)
			{
				le.j_++;
				le.i_--;
				l++;
			}
			while (getChess(ri.i_, ri.j_) == who)
			{
				ri.i_++;
				ri.j_--;
				l++;
			}
			for (int s = 0; s < 5; s++)
			{
				left[s+1] = getChess(le.i_-s, le.j_ + s);
				right[s+1] = getChess(ri.i_+s, ri.j_ - s);
			}
		}
		if (k == 3)
		{
			le.j_--;
			le.i_--;
			ri.j_++;
			ri.i_++;
			while (getChess(le.i_, le.j_) == who)
			{
				le.j_--;
				le.i_--;
				l++;
			}
			while (getChess(ri.i_, ri.j_) == who)
			{
				ri.j_++;
				ri.i_++;
				l++;
			}
			for (int s = 0; s < 5; s++)
			{
				left[s+1] = getChess(le.i_ - s, le.j_ - s);
				right[s+1] = getChess(ri.i_ + s, ri.j_ + s);
			}
		}

		//开始判断
		if (l == 5)
			win5++;
		else if (l == 4)
		{
			if (left[1] == EMPTY && right[1] == EMPTY)
				alive4++;
			else if (left[1] == EMPTY || right[1] == EMPTY)
				die4++;
			else
				nothing++;
		}
		else if (l == 3)
		{
			if ((left[1] == EMPTY && left[2] == who) || (right[1] == EMPTY && right[2] == who))
				ddie4++;
			else if (left[1] == EMPTY && right[1] == EMPTY && (left[2] == EMPTY || right[2] == EMPTY))
				alive3++;
			else if ((left[1] == EMPTY && left[2] == EMPTY) || (right[1] == EMPTY && right[2] == EMPTY))
				die3++;
			else if (left[1] == EMPTY && right[1] == EMPTY)
				die3++;
			else
				nothing++;
		}
		else if (l == 2)
		{
			if ((left[1] == EMPTY && left[2] == who && left[3] == who) &&
				(right[1] == EMPTY && right[2] == who && right[3] == who))
				ddie4++;
			else if (left[1] == EMPTY && right[1] == EMPTY &&
				((left[2] == who && left[3] == EMPTY) || (right[2] == who && right[3] == EMPTY)))
				dalive3++;
			else if ((left[1] == EMPTY && left[3] == EMPTY && left[2] == who) ||
				(right[1] == EMPTY && right[3] == EMPTY && right[2] == who))
				die3++;
			else if ((left[1] == EMPTY && right[1] == EMPTY) &&
				(left[2] == who || right[2] == who))
				die3++;
			else if ((left[1] == EMPTY && left[2] == EMPTY && left[3] == who) ||
				(right[1] == EMPTY && right[2] == EMPTY && right[3] == who))
				die3++;
			else if ((left[1] == EMPTY && right[1] == EMPTY && right[2] == EMPTY && right[3] == EMPTY) ||
				(left[1] == EMPTY && left[2] == EMPTY && right[1] == EMPTY && right[2] == EMPTY) ||
				(left[1] == EMPTY && left[2] == EMPTY && left[3] == EMPTY && right[1] == EMPTY))
				alive2++;
			else if ((left[1] == EMPTY && left[2] == EMPTY && left[3] == EMPTY) ||
				(right[1] == EMPTY && right[2] == EMPTY && right[3] == EMPTY))
				die2++;
			else
				nothing++;
		}
		else if (l == 1)
		{
			if ((left[1] == EMPTY && left[2] == who && left[3] == who && left[4] == who) ||
				(right[1] == EMPTY && right[2] == who && right[3] == who && right[4] == who))
				ddie4++;
			else if ((left[1] == EMPTY && right[1] == EMPTY)
				&& ((left[2] == who && left[3] == who && left[4] == EMPTY) ||
					(right[2] == who && right[3] == who && right[4] == EMPTY)))
				dalive3++;
			else if ((left[1] == EMPTY && right[1] == EMPTY) &&
				((left[2] == who && left[3] == who) || (right[2] == who && right[3] == who)))
				die3++;
			else if ((left[1] == EMPTY && left[4] == EMPTY && left[2] == who && left[3] == who) ||
				(right[1] == EMPTY && right[4] == EMPTY && right[2] == who && right[3] == who))
				die3++;
			else if ((left[1] == EMPTY && left[2] == EMPTY && left[3] == who && left[4] == who) ||
				(right[1] == EMPTY && right[2] == EMPTY && right[3] == who && right[4] == who))
				die3++;
			else if ((left[1] == EMPTY && left[3] == EMPTY && left[2] == who && left[4] == who) ||
				(right[1] == EMPTY && right[3] == EMPTY && right[2] == who && right[4] == who))
				die3++;
			else if ((left[1] == EMPTY && right[1] == EMPTY && right[3] == EMPTY && right[2] == who)
				&& (left[2] == EMPTY || right[4] == EMPTY))
				dalive2++;
			else if ((right[1] == EMPTY && left[1] == EMPTY && left[3] == EMPTY && left[2] == who) &&
				(right[2] == EMPTY || left[4] == EMPTY))
				dalive2++;
			else if (
				(left[1] == EMPTY && right[1] == EMPTY && right[2] == EMPTY && right[4] == EMPTY && right[3] == who) ||
					(right[1] == EMPTY && left[1] == EMPTY && left[2] == EMPTY && left[4] == EMPTY && left[3] == who))
				dalive2++;
			else if ((left[1] == EMPTY && left[3] == EMPTY && left[4] == EMPTY && left[2] == who) ||
				(right[1] == EMPTY && right[3] == EMPTY && right[4] == EMPTY && right[2] == who))
				die2++;
			else if ((left[1] == EMPTY && right[1] == EMPTY && right[2] == EMPTY && left[2] == who) ||
				(right[1] == EMPTY && left[1] == EMPTY && left[2] == EMPTY && right[2] == who))
				die2++;
			else if ((left[1] == EMPTY && left[2] == EMPTY && left[4] == EMPTY && left[3] == who) ||
				(right[1] == EMPTY && right[2] == EMPTY && right[4] == EMPTY && right[3] == who))
				die2++;
			else if ((left[1] == EMPTY && left[2] == EMPTY && right[1] == EMPTY && left[3] == who) ||
				(right[1] == EMPTY && right[2] == EMPTY && left[1] == EMPTY && right[3] == who))
				die2++;
			else if ((left[1] == EMPTY && left[2] == EMPTY && left[3] == EMPTY && left[4] == who) ||
				(right[1] == EMPTY && right[2] == EMPTY && right[3] == EMPTY && right[4] == who))
				die2++;
			else
				nothing++;
		}
	}
	if (win5 >= 1)
		return 14;//赢5
	if (alive4 >= 1 || die4 >= 2 || (die4 >= 1 && alive3 >= 1))
		return 13;//活4 双死4 死4活3
	if (alive3 >= 2)
		return 12;//双活3
	if (die3 >= 1 && alive3 >= 1)
		return 11;//死3高级活3
	if (die4 >= 1)
		return 10;//高级死4
	if (ddie4 >= 1)
		return 9;//低级死4
	if (alive3 >= 1)
		return 8;//单活3
	if (dalive3 >= 1)
		return 7;//跳活3
	if (alive2 >= 2)
		return 6;//双活2
	if (alive2 >= 1)
		return 5;//活2
	if (dalive2 >= 1)
		return 4;//低级活2
	if (die3 >= 1)
		return 3;//死3
	if (die2 >= 1)
		return 2;//死2
	return 1;//没有威胁

}

