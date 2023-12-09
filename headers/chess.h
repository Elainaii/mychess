//
// Created by Elaina on 2023/12/3.
//

#ifndef CHESS_NEW_HEADERS_CHESS_H_
#define CHESS_NEW_HEADERS_CHESS_H_
#define WHITE_CHESS 5
#define BLACK_CHESS 10
#define EMPTY 1
#define OUT 100
#define PVPMODE 100
#define PVEMODE1 200
#define NOTHING 0
#define WIN5 999999
#define ALIVE4 10000
#define DIE4 500
#define DDIE4
#define ALIVE3
#define DALIVE3
#define DIE3
#define ALIVE2
#define DALIVE2
#define DIE2
#include "vector"
#include "graphics.h"
struct chessxy
{
	int i_;
	int j_;
	int currChess;
	int step;
};
class chess
{
 protected:
	char chessBroad[30][30];
	std::vector<chessxy> xy_;
	int currChess_;
	int step_;
	int mode_;//0为人机，1为人人，2电子斗蛐蛐
 public:
	chess(int mode = PVPMODE);
	chess(const std::vector<chessxy>& xy);
	bool putchess(int i,int j);
	void red(int i,int j,int k,int dest);
	int judgeNew();
	int subJudge(char* temp,const int& i,const int& j,const int& k);
	int getChess(int i,int j);
	//ai部分
	int score(int i,int j,int who);
	void simpleAI();
};
#endif //CHESS_NEW_HEADERS_CHESS_H_
