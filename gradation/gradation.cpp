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
	//渐变增值比例
	double index = 0;
	//固定搭配
	int color_ = 1;
	//三色渐变
	COLORREF one = RGB(101, 199, 247);
	COLORREF two = RGB(100, 65, 165);
	COLORREF three = RGB(101, 199, 247);
	//消息
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
				//绿色
			case 1:one = RGB(250, 255, 209); two = RGB(44, 119, 68); three = RGB(250, 255, 209); color_ = 2; break;
				//红色
			case 2:one = RGB(25, 10, 5); two = RGB(135, 0, 0); three = RGB(25, 10, 5); color_ = 3; break;
				//黑色
			case 3:one = RGB(255, 255, 255); two = RGB(0,0,0); three = RGB(255, 255, 255); color_ = 4; break;
				//蓝色
			case 4:one = RGB(101, 199, 247); two = RGB(100, 65, 165); three = RGB(101, 199, 247); color_ = 1; break;
			}

		}
		//如果鼠标越界则跳过
		if (m.x >= WIDTH || m.x < 0)
		{
			continue;
		}


		BeginBatchDraw();
		//左半区
		IMAGE img;
		getimage(&img, 0, 0, WIDTH, HEIGHT);
		// 获取图像数据指针
		DWORD* pImgData = GetImageBuffer(&img);

		index = 0;
		for (int i = 0; i <= m.x; i++)
		{
			double i_r = (GetRValue(two) - GetRValue(one)) * index;
			double i_g = (GetGValue(two) - GetGValue(one)) * index;
			double i_b = (GetBValue(two) - GetBValue(one)) * index;
			COLORREF pixel_color = RGB(GetRValue(one) + i_r, GetGValue(one) + i_g, GetBValue(one) + i_b);

			// 在显存中对图像进行处理
			for (int y = 0; y < img.getheight(); y++)
			{

				int temp = y * img.getwidth() + i;
				//将RGB转换为BGR设置点的颜色
				pImgData[temp] = BGR(pixel_color);

			}
			index += 1.0 / m.x;
		}

		//右半区
		index = 0;
		for (int j = m.x; j < img.getwidth(); j++)
		{
			double i_r = (GetRValue(three) - GetRValue(two)) * index;
			double i_g = (GetGValue(three) - GetGValue(two)) * index;
			double i_b = (GetBValue(three) - GetBValue(two)) * index;
			COLORREF pixel_color = RGB(GetRValue(two) + i_r, GetGValue(two) + i_g, GetBValue(two) + i_b);

			// 在显存中对图像进行处理
			for (int y = 0; y < img.getheight(); y++)
			{
				int temp = y * img.getwidth() + j;
				// 设置像素点的颜色值
				//将RGB转换为BGR设置点的颜色
				pImgData[temp] = BGR(pixel_color);

			}
			index += (1.0 / (WIDTH - m.x));
		}
		putimage(0, 0, &img);

		EndBatchDraw();
	}
	return 0;
}