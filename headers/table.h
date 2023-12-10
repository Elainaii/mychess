//
// Created by Elaina on 2023/12/9.
//

#ifndef CHESS_NEW_HEADERS_TABLE_H_
#define CHESS_NEW_HEADERS_TABLE_H_
#include "chess.h"
#include "widget.h"
#include "window.h"
class table:public widget
{
 private:
	std::vector<chessData>  data_;
	int index_;
	IMAGE image;
 public:
	table(const std::vector<chessData>& data);
	table();
	void show();
	void pageup();
	void pagedown();
	chessData entergame(int i);
};
#endif //CHESS_NEW_HEADERS_TABLE_H_
