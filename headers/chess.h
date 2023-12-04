//
// Created by Elaina on 2023/12/3.
//

#ifndef CHESS_NEW_HEADERS_CHESS_H_
#define CHESS_NEW_HEADERS_CHESS_H_
#define WHITE_CHESS 5
#define BLACK_CHESS 10
#define EMPTY 1
#include "vector"
#include "graphics.h"
struct chessxy
{
	int i_;
	int j_;
	int currChess;
};
class chess
{
 protected:
	char chessBroad[30][30];
	std::vector<chessxy> xy_;
	int currChess_;
	IMAGE blackChessImg;
	IMAGE whiteChessImg;
 public:
	chess();
	chess(const std::vector<chessxy>& xy);
	int judge(int i,int j);
	bool putchess(int i,int j);
	void red(int i,int j,int k,int dest);
	int judgeNew();
	int subJudge(char* temp,const int& i,const int& j,const int& k);
	int getChess(int i,int j);
};
#endif //CHESS_NEW_HEADERS_CHESS_H_
