/* 2252075 刘文飞 国06 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "cmd_console_tools.h"
#include "90-b2.h"
using namespace std;




void solution1() {
	cct_cls();
	int row;
	int column;
	row_column(&row,&column);
	int shuzu[9][9] = { 0 };/*数组初始化到此完成*/
	cout << endl;
	cout << "初始数组：" << endl;
	generate_balls(shuzu, row, column, 1);
	whole_shuzu_print_1(shuzu,  row,  column);
	end();
	
}
void solution2() {
	cct_cls();
	int row;
	int column;
	row_column(&row, &column);
	int shuzu[9][9] = { 0 };/*数组初始化到此完成*/
	cout << endl;
	cout << "当前数组：" << endl;
	generate_balls(shuzu, row, column, 2);
	whole_shuzu_print_1(shuzu, row, column);
	int next_balls[3];
	generate_balls_3(next_balls);
	cout << endl;
	cout << "下三个彩球的颜色分别是： " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2]<<endl;
	int x0=0,y0=0;/*初始坐标*/
	int x1=0, y1=0;/*目的坐标*/
	coordinate(shuzu, row, column, &x0, &y0, &x1, &y1);
	int begin;
	begin = shuzu[y0][x0];/*因为search过程中会吃掉这个数据，我们在这里记录下来*/
	int path[81][2] = { 0 };/*用来记录走过的点的坐标*/
	int judge=0;/*用来判断是否要存入path，同时数值增减代表每一步的path*/
	if (!(search(shuzu, row, column, x0, y0, x1, y1, path, &judge))){
		cout << "无法找到移动路径" << endl;
			end();
	}
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (shuzu[i][j] < 0)
					shuzu[i][j] = 0;/*将寻路过程中的-1置为0*/
			}
		}
		shuzu[y0][x0] = begin;/*还原数组*/
		cout << "查找结果数组：" << endl;
		whole_shuzu_print_2(shuzu, path, judge, row, column,1);
		cout << endl;
		cout << "移动路径（不同色标识）"<<endl;
		whole_shuzu_print_2(shuzu, path, judge, row, column,2);
		end();
	}
}
/*对于程序三，为了美观，我采取了走一步一清屏的方式*/
void solution3() {/*分成三个大部分，分别是实现数组元素的改变，即初末位置的变化，是否可以消去；第二部分是放置三个新球；第三部分是计算得分*/
	cct_cls();
	int row=0, column=0;
	row_column(&row, &column);
	int sum_score = 0, once_score = 0;
	int judge = 0;
	int shuzu[9][9] = { 0 };
	int x0 = 0, y0 = 0;/*初始坐标*/
	int x1 = 0, y1 = 0;/*目的坐标*/
	int next_balls[3];
	int path[81][2];
	cct_cls();
	cout << "当前数组：" << endl;
	generate_balls(shuzu, row, column, 1);
	whole_shuzu_print_1(shuzu, row, column);
	generate_balls_3(next_balls);
	cout << endl;
	cout << "下三个彩球的颜色分别是： " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2];
	int xm, ym;
	cct_getxy(xm, ym);
	while (1)
	{
		
		judge = 0;
		once_score = 0;
		coordinate(shuzu, row, column,&x0, &y0, &x1, &y1);
		int begin;
		begin = shuzu[y0][x0];/*因为search过程中会吃掉这个数据，我们在这里记录下来*/
		if (search(shuzu, row, column, x0, y0, x1, y1, path, &judge))
		{
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					if (shuzu[i][j] < 0)
						shuzu[i][j] = 0;/*将寻路过程中的-1置为0，顺便初位置也已经置0*/
				}
			}
			shuzu[y1][x1] = begin;/*完成移动*/
			score(shuzu, x1, y1, row, column, &sum_score, &once_score);
			if (!once_score)
				put_in_nextballs(shuzu, next_balls, column, row);
			cout << endl;
			cct_cls();
			cout << "本次得分：" << once_score << " 总共得分：" << sum_score << endl;
			whole_shuzu_print_1(shuzu, row, column);
			if (once_score) {
				cout << endl;
				cout << "下三个彩球的颜色分别是： " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2];
				cout << endl;
			}
			else {
				generate_balls_3(next_balls);
				cout << endl;
				cout << "下三个彩球的颜色分别是： " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2];
			}
			if (game_over(shuzu, row, column,ym))
				break;
		}
		else
		{
			cct_cls();
			cout << "无法找到移动路径" << endl;
			cout << "本次得分：" << once_score << " 总共得分：" << sum_score << endl;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					if (shuzu[i][j] < 0)
						shuzu[i][j] = 0;/*将寻路过程中的-1置为0*/
				}
			}
			shuzu[y0][x0] = begin;/*还原数组*/
			whole_shuzu_print_1(shuzu, row, column);
			cout << "下三个彩球的颜色分别是： " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2]<<endl;
			continue;
		}
		
	}
	end();

}
