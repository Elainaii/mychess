//
// Created by Elaina on 2023/12/9.
//

#include "table.h"
#include "conio.h"
table::table(const std::vector<chessData>& data)
{
	data_ = data;
	index_ = 1;
	x_ = 10;
	y_ = 10;
	length_ = 1260;
	width_ = 700;

}

void table::show()//表格数据展示
{
	setlinecolor(BLACK);
	for (int i = 0; i <= 11; i++)
		line(50, 30 + 50 * i, 880, 30 + 50 * i);
	line(50,30,50,580);
	line(120,30,120,580);
	line(320,30,320,580);
	line(400,30,400,580);
	line(550,30,550,580);
	line(750,30,750,580);
	line(880,30,880,580);
	RECT rect = { 50, 30,  120, 80 };
	settextstyle(30,0,"行楷");
	drawtext("序号",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 120, 30,  320, 80 };
	drawtext("游戏时间",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 320, 30,  400, 80 };
	drawtext("模式",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 400, 30,  550, 80 };
	drawtext("步数",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 550, 30,  750, 80 };
	drawtext("对局情况",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 750, 30,  880, 80 };
	drawtext("读取",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//写学生数据
	int i = index_;
	for(int j = 1;j<=11;j++)
	{
		if(i<=data_.size())//
		{

			settextstyle(30,0,"行楷");
			rect = { 50, 30+j*50,  120, 80+j*50 };
			std::string str = std::to_string(data_[i-1].id);//将数字转换成字符串。。。
			LPCTSTR idStr = str.c_str();
			drawtext(idStr, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			rect = { 120, 30+j*50,  320, 80 +j*50};
			drawtext("...",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			rect = { 320, 30+j*50,  400, 80 +j*50};
			if(data_[i-1].mode==PVPMODE)
				drawtext("PVP",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			else if(data_[i-1].mode == PVEMODE1)
				drawtext("PVE先手",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			else if(data_[i-1].mode == PVEMODE2)
				drawtext("PVE后手",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			rect = { 400, 30+j*50,  550, 80 +j*50};
			str = std::to_string(data_[i-1].totalStep);//将数字转换成字符串。。。
			LPCTSTR stepStr = str.c_str();
			drawtext(stepStr,&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			rect = { 550, 30+j*50,  750, 80+j*50 };
			if(data_[i-1].isEnd)
			{
				if(data_[i-1].xy_.rbegin()->currChess==BLACK_CHESS)
					drawtext("黑子赢",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				else
					drawtext("白子赢",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else
				drawtext("未结束",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			i++;
		}
	}
}

void table::pageup()
{
	index_ -=10;
	if(index_ <0)
	{
		index_ +=10;
		return;
	}
	show();
}

void table::pagedown()
{
	index_ += 10;
	if (index_ > data_.size())	// 读取到最后一页停止操作
	{
		index_ -= 10;
		return;
	}
	show();
}

chessData table::entergame(int i)
{
	chessData temp ={0};
	if(i+index_<=data_.size())
		return data_[i+index_-1];
	else
		return  temp;
}