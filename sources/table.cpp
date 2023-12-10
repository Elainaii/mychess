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
	loadimage(&image, "../images/elainaback.png", 1280, 720, false);
}

void table::show()//�������չʾ
{
	cleardevice();
	putimage(0, 0, &image);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	for (int i = 0; i <= 11; i++)
		line(50, 30 + 50 * i, 880, 30 + 50 * i);
	line(50,30,50,580);
	line(120,30,120,580);
	line(320,30,320,580);
	line(450,30,450,580);
	line(550,30,550,580);
	line(750,30,750,580);
	line(880,30,880,580);
	RECT rect = { 50, 30,  120, 80 };
	settextstyle(30,0,"�п�");
	drawtext("���",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 120, 30,  320, 80 };
	drawtext("��Ϸʱ��",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 320, 30,  450, 80 };
	drawtext("ģʽ",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 450, 30,  550, 80 };
	drawtext("����",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 550, 30,  750, 80 };
	drawtext("�Ծ����",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 750, 30,  880, 80 };
	drawtext("��ȡ",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//дѧ������
	int i = index_;
	for(int j = 1;j<=10;j++)
	{
		if(i<=data_.size())//
		{

			settextstyle(30,0,"�п�");
			rect = { 50, 30+j*50,  120, 80+j*50 };
			std::string str = std::to_string(data_[i-1].id);//������ת�����ַ���������
			LPCTSTR idStr = str.c_str();
			drawtext(idStr, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			rect = { 120, 30+j*50,  320, 80 +j*50};
			settextstyle(20,0,"�п�");
			drawtext(data_[i-1].time.c_str(),&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextstyle(30,0,"�п�");
			rect = { 320, 30+j*50,  450, 80 +j*50};
			if(data_[i-1].mode==PVPMODE)
				drawtext("PVP",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			else if(data_[i-1].mode == PVEMODE1)
				drawtext("PVE����",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			else if(data_[i-1].mode == PVEMODE2)
				drawtext("PVE����",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			rect = { 450, 30+j*50,  550, 80 +j*50};
			str = std::to_string(data_[i-1].totalStep-1);//������ת�����ַ���������
			LPCTSTR stepStr = str.c_str();
			drawtext(stepStr,&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			rect = { 550, 30+j*50,  750, 80+j*50 };
			if(data_[i-1].isEnd)
			{
				if(data_[i-1].xy_.rbegin()->currChess==BLACK_CHESS)
					drawtext("����Ӯ",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				else
					drawtext("����Ӯ",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else
				drawtext("δ����",&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
	if (index_ > data_.size())	// ��ȡ�����һҳֹͣ����
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