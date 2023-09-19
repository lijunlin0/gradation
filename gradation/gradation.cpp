#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<iostream>
#include"time.h"

using namespace std;

long long time::update_ms = 0;


int main()
{
	const int WIDTH = 1920;
	const int HEIGHT = 1080;
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
	//������ֵ����
	double index = 0;
	//�̶�����
	int color_ = 1;
	//��ɫ����
	COLORREF one = RGB(101, 199, 247);
	COLORREF two = RGB(100, 65, 165);
	COLORREF three = RGB(101, 199, 247);
	//��Ϣ
	ExMessage m;
	ExMessage m2;
	while (true)
	{
		m=getmessage(EX_MOUSE);
		long long current = time::current_time();
		if (current - time::update_ms < time::frame_ms)
		{
			continue;
		}
		time::update_ms = current;

		if (m.message == WM_LBUTTONDOWN)
		{
			switch (color_)
			{
				//��ɫ
			case 1:one = RGB(250, 255, 209); two = RGB(44, 119, 68); three = RGB(250, 255, 209); color_ = 2; break;
				//��ɫ
			case 2:one = RGB(25, 10, 5); two = RGB(135, 0, 0); three = RGB(25, 10, 5); color_ = 3; break;
				//��ɫ
			case 3:one = RGB(255, 255, 255); two = RGB(0,0,0); three = RGB(255, 255, 255); color_ = 4; break;
				//��ɫ
			case 4:one = RGB(101, 199, 247); two = RGB(100, 65, 165); three = RGB(101, 199, 247); color_ = 1; break;
			}

		}
		//������Խ��������
		if (m.x >= WIDTH || m.x < 0)
		{
			continue;
		}


		BeginBatchDraw();
		//�����
		IMAGE img;
		getimage(&img, 0, 0, WIDTH, HEIGHT);
		// ��ȡͼ������ָ��
		DWORD* pImgData = GetImageBuffer(&img);

		index = 0;
		for (int i = 0; i <= m.x; i++)
		{
			double i_r = (GetRValue(two) - GetRValue(one)) * index;
			double i_g = (GetGValue(two) - GetGValue(one)) * index;
			double i_b = (GetBValue(two) - GetBValue(one)) * index;
			COLORREF pixel_color = RGB(GetRValue(one) + i_r, GetGValue(one) + i_g, GetBValue(one) + i_b);

			// ���Դ��ж�ͼ����д���
			for (int y = 0; y < img.getheight(); y++)
			{

				int temp = y * img.getwidth() + i;
				//��RGBת��ΪBGR���õ����ɫ
				pImgData[temp] = BGR(pixel_color);

			}
			index += 1.0 / m.x;
		}

		//�Ұ���
		index = 0;
		for (int j = m.x; j < img.getwidth(); j++)
		{
			double i_r = (GetRValue(three) - GetRValue(two)) * index;
			double i_g = (GetGValue(three) - GetGValue(two)) * index;
			double i_b = (GetBValue(three) - GetBValue(two)) * index;
			COLORREF pixel_color = RGB(GetRValue(two) + i_r, GetGValue(two) + i_g, GetBValue(two) + i_b);

			// ���Դ��ж�ͼ����д���
			for (int y = 0; y < img.getheight(); y++)
			{
				int temp = y * img.getwidth() + j;
				// �������ص����ɫֵ
				//��RGBת��ΪBGR���õ����ɫ
				pImgData[temp] = BGR(pixel_color);

			}
			index += (1.0 / (WIDTH - m.x));
		}
		putimage(0, 0, &img);

		EndBatchDraw();
	}
	return 0;
}