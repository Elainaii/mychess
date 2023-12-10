//
// Created by Elaina on 2023/11/30.
//

#include "button.h"
#include "widget.h"

button::button(int x, int y, int width, int length, const LPCTSTR& s, buttonType t)
{
	x_ = x;
	y_ = y;
	width_ = width;
	length_ = length;
	buttonText_ = s;
	type_ = t;
}

void button::show(COLORREF color) const
{
	RECT rect = { x_, y_, x_ + length_, y_ + width_ };
	setlinestyle(PS_SOLID, 2);
	setfillcolor(color);
	settextcolor(BLACK);
	if (type_ == buttonType::text)
	{
		settextstyle(width_, 0, "幼圆");
		drawtext(buttonText_, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		settextstyle(width_/1.5, 0, "幼圆");
		fillrectangle(x_, y_, x_ + length_, y_ + width_);
		drawtext(buttonText_, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

bool button::state(const ExMessage& msg)
{
	RECT rect = { x_, y_, x_ + length_, y_ + width_ };
	if (type_ == buttonType::rectangle)//实心按钮
	{

		if (mouseisIn(msg) && !msg.lbutton)//鼠标未按下和在里面0 悬停
		{
			show(LIGHTCYAN);
			return false;
		}
		else if (mouseisIn(msg) && msg.lbutton)//鼠标按下在里面1 按下
		{
			show(WHITE);
			return true;
		}
		else//没动作，重置按钮
		{
			show();
			return false;
		}
	}
	else//文字按钮
	{
		settextstyle(width_, 0, "幼圆");
		if (mouseisIn(msg) && !msg.lbutton)//鼠标未按下和在里面0 悬停
		{
			settextcolor(YELLOW);
			drawtext(buttonText_, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			return false;
		}
		else if (mouseisIn(msg) && msg.lbutton)//鼠标按下在里面1 按下
		{
			settextcolor(LIGHTCYAN);
			drawtext(buttonText_, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			return true;
		}
		else
		{
			show();
			return 0;
		}
	}

}

bool button::mouseisIn(const ExMessage& msg)
{
	if (msg.x >= x_ && msg.x <= (x_ + length_) && msg.y >= y_ && msg.y <= (y_ + width_))//鼠标在坐标围成的矩形内
		return true;
	else
		return false;
}