/* 2252075 ���ķ� ��06 */
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




void solution4() {
	cct_cls();
	int row = 0, column = 0;
	row_column(&row, &column);
	int shuzu[9][9] = { 0 };
	cout << "��ǰ���飺" << endl;
	generate_balls(shuzu, row, column, 1);
	whole_shuzu_print_1(shuzu, row, column);
	cout << endl;
	cout << "���س�����ʾͼ��...";
	while (_getch() != '\r')
		;
	cct_cls();
	qipan_1(shuzu, row, column);
	end();

}
void solution5() {
	cct_cls();
	int row = 0, column = 0;
	row_column(&row, &column);
	int shuzu[9][9] = { 0 };
	cout << "��ǰ���飺" << endl;
	generate_balls(shuzu, row, column, 1);
	whole_shuzu_print_1(shuzu, row, column);
	cout << endl;
	cout << "���س�����ʾͼ��...";
	while (_getch() != '\r')
		;
	cct_cls();
	qipan_2(shuzu, row, column);
	end();
}
void solution6() {
	cct_cls();
	int row = 0, column = 0;
	row_column(&row, &column);
	int sum_score = 0, once_score = 0;
	int judge = 0;
	int shuzu[9][9] = { 0 };
	int x0 = 0, y0 = 0;/*��ʼ����*/
	int x1 = 0, y1 = 0;/*Ŀ������*/
	
	int path[81][2];
	cct_cls();
	generate_balls(shuzu, row, column, 2);
	qipan_2(shuzu, row, column);
	int y_m = 0;
	int x_m = 0;
	cct_getxy(x_m, y_m);
	while (1)
	{
		for (int i = 0; i < 81; i++)
			for (int j = 0; j < 2; j++)
				path[i][j] = -1;/*ȫ����-1����Ϊ0������ܻᵼ�»���*/
		read_mouse(shuzu, x0, y0, x1, y1, row, column, y_m);
		int begin= shuzu[y0][x0];
		if (search(shuzu, row, column, x0, y0, x1, y1, path, &judge))
		{
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					if (shuzu[i][j] < 0)
						shuzu[i][j] = 0;/*��Ѱ·�����е�-1��Ϊ0��˳���λ��Ҳ�Ѿ���0*/
				}
			}
			shuzu[y0][x0] = begin;
			moving_steps(path, begin, judge);
			break;
		}
		else
		{
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					if (shuzu[i][j] < 0)
						shuzu[i][j] = 0;/*��Ѱ·�����е�-1��Ϊ0��˳���λ��Ҳ�Ѿ���0*/
				}
			}
			shuzu[y0][x0] = begin;
			cout << endl;
			cout << "[����]  �޷���" << char(y0+'A') << x0+1 << "�ƶ���" << char(y1+'A') << x1+1;
			cct_showstr(2 + x0 * 4, y0 * 2 + 2, "��", shuzu[y0][x0] + 1, COLOR_HWHITE);
			continue;
		}
	}
	cct_gotoxy(x_m, y_m);
	end();
}
void solution7() {
	cct_cls();
	int row = 0, column = 0;
	row_column(&row, &column);
	int sum_score = 0, once_score = 0;
	int judge = 0;
	int shuzu[9][9] = { 0 };
	int x0 = 0, y0 = 0;/*��ʼ����*/
	int x1 = 0, y1 = 0;/*Ŀ������*/
	int next_balls[3];
	int path[81][2];
	cct_cls();
	generate_balls(shuzu, row, column, 1);
	qipan_2(shuzu, row, column);
	int y_m = 0;
	int x_m = 0;
	cct_getxy(x_m, y_m);
	generate_balls_3(next_balls);
	right_(row,column, sum_score,shuzu, next_balls);
	while (1)
	{

		for (int i = 0; i < 81; i++)
			for (int j = 0; j < 2; j++)
				path[i][j] = -1;/*ȫ����-1����Ϊ0������ܻᵼ�»���*/
		judge = 0;
		once_score = 0;
		read_mouse(shuzu, x0, y0, x1, y1, row, column, y_m);
		int begin;
		begin = shuzu[y0][x0];/*��Ϊsearch�����л�Ե�������ݣ������������¼����*/
		if (search(shuzu, row, column, x0, y0, x1, y1, path, &judge))
		{
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					if (shuzu[i][j] < 0)
						shuzu[i][j] = 0;/*��Ѱ·�����е�-1��Ϊ0��˳���λ��Ҳ�Ѿ���0*/
				}
			}
			shuzu[y1][x1] = begin;/*����ƶ�*/
			moving_steps(path, begin, judge);
			score(shuzu, x1, y1, row, column, &sum_score, &once_score);
			if (!once_score) {
				put_in_nextballs(shuzu, next_balls, column, row);
				cct_setcolor();
				qipan_2(shuzu, row, column);
				
				generate_balls_3(next_balls);
				right_(row, column, sum_score, shuzu, next_balls);
			}
			else {
				for (int i = 0; i < row; i++)
					for (int j = 0; j < column; j++)
						if (shuzu[i][j] == 0)
							cct_showstr(2 + j * 4, (i + 1) * 2, "  ", COLOR_HWHITE, COLOR_HWHITE);/*��ȥ��*/
				right_(row, column, sum_score, shuzu, next_balls);
			}
			
			
		}
		else
		{
			
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					if (shuzu[i][j] < 0)
						shuzu[i][j] = 0;/*��Ѱ·�����е�-1��Ϊ0*/
				}
			}
			shuzu[y0][x0] = begin;/*��ԭ����*/
			
			continue;
		}
		if (game_over(shuzu, row, column,y_m))
			break;
	}
	end();
}