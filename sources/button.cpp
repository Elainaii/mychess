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
		settextstyle(width_, 0, "��Բ");
		drawtext(buttonText_, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		settextstyle(width_/1.5, 0, "��Բ");
		fillrectangle(x_, y_, x_ + length_, y_ + width_);
		drawtext(buttonText_, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

bool button::state(const ExMessage& msg)
{
	RECT rect = { x_, y_, x_ + length_, y_ + width_ };
	if (type_ == buttonType::rectangle)//ʵ�İ�ť
	{

		if (mouseisIn(msg) && !msg.lbutton)//���δ���º�������0 ��ͣ
		{
			show(LIGHTCYAN);
			return false;
		}
		else if (mouseisIn(msg) && msg.lbutton)//��갴��������1 ����
		{
			show(WHITE);
			return true;
		}
		else//û���������ð�ť
		{
			show();
			return false;
		}
	}
	else//���ְ�ť
	{
		settextstyle(width_, 0, "��Բ");
		if (mouseisIn(msg) && !msg.lbutton)//���δ���º�������0 ��ͣ
		{
			settextcolor(YELLOW);
			drawtext(buttonText_, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			return false;
		}
		else if (mouseisIn(msg) && msg.lbutton)//��갴��������1 ����
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
	if (msg.x >= x_ && msg.x <= (x_ + length_) && msg.y >= y_ && msg.y <= (y_ + width_))//���������Χ�ɵľ�����
		return true;
	else
		return false;
}