//
// Created by Elaina on 2023/11/30.
//

#ifndef CHESS_NEW_SOURCES_BUTTON_H_
#define CHESS_NEW_SOURCES_BUTTON_H_
#include "widget.h"
#include "string"
enum class buttonType{text,rectangle};
class button: public widget
{
 protected:
	LPCTSTR buttonText_;
	buttonType type_;
 public:

	button(int x =0,int y =0,int width =200,int length =100, const LPCTSTR &s ="°´Å¥",buttonType t =buttonType::text);
	bool mouseisIn(const ExMessage &msg);
	void show(COLORREF color = WHITE) const;
	bool state(const ExMessage &msg);

};
#endif //CHESS_NEW_SOURCES_BUTTON_H_
