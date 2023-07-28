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




void solution1() {
	cct_cls();
	int row;
	int column;
	row_column(&row,&column);
	int shuzu[9][9] = { 0 };/*�����ʼ���������*/
	cout << endl;
	cout << "��ʼ���飺" << endl;
	generate_balls(shuzu, row, column, 1);
	whole_shuzu_print_1(shuzu,  row,  column);
	end();
	
}
void solution2() {
	cct_cls();
	int row;
	int column;
	row_column(&row, &column);
	int shuzu[9][9] = { 0 };/*�����ʼ���������*/
	cout << endl;
	cout << "��ǰ���飺" << endl;
	generate_balls(shuzu, row, column, 2);
	whole_shuzu_print_1(shuzu, row, column);
	int next_balls[3];
	generate_balls_3(next_balls);
	cout << endl;
	cout << "�������������ɫ�ֱ��ǣ� " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2]<<endl;
	int x0=0,y0=0;/*��ʼ����*/
	int x1=0, y1=0;/*Ŀ������*/
	coordinate(shuzu, row, column, &x0, &y0, &x1, &y1);
	int begin;
	begin = shuzu[y0][x0];/*��Ϊsearch�����л�Ե�������ݣ������������¼����*/
	int path[81][2] = { 0 };/*������¼�߹��ĵ������*/
	int judge=0;/*�����ж��Ƿ�Ҫ����path��ͬʱ��ֵ��������ÿһ����path*/
	if (!(search(shuzu, row, column, x0, y0, x1, y1, path, &judge))){
		cout << "�޷��ҵ��ƶ�·��" << endl;
			end();
	}
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (shuzu[i][j] < 0)
					shuzu[i][j] = 0;/*��Ѱ·�����е�-1��Ϊ0*/
			}
		}
		shuzu[y0][x0] = begin;/*��ԭ����*/
		cout << "���ҽ�����飺" << endl;
		whole_shuzu_print_2(shuzu, path, judge, row, column,1);
		cout << endl;
		cout << "�ƶ�·������ͬɫ��ʶ��"<<endl;
		whole_shuzu_print_2(shuzu, path, judge, row, column,2);
		end();
	}
}
/*���ڳ�������Ϊ�����ۣ��Ҳ�ȡ����һ��һ�����ķ�ʽ*/
void solution3() {/*�ֳ������󲿷֣��ֱ���ʵ������Ԫ�صĸı䣬����ĩλ�õı仯���Ƿ������ȥ���ڶ������Ƿ����������򣻵��������Ǽ���÷�*/
	cct_cls();
	int row=0, column=0;
	row_column(&row, &column);
	int sum_score = 0, once_score = 0;
	int judge = 0;
	int shuzu[9][9] = { 0 };
	int x0 = 0, y0 = 0;/*��ʼ����*/
	int x1 = 0, y1 = 0;/*Ŀ������*/
	int next_balls[3];
	int path[81][2];
	cct_cls();
	cout << "��ǰ���飺" << endl;
	generate_balls(shuzu, row, column, 1);
	whole_shuzu_print_1(shuzu, row, column);
	generate_balls_3(next_balls);
	cout << endl;
	cout << "�������������ɫ�ֱ��ǣ� " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2];
	int xm, ym;
	cct_getxy(xm, ym);
	while (1)
	{
		
		judge = 0;
		once_score = 0;
		coordinate(shuzu, row, column,&x0, &y0, &x1, &y1);
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
			score(shuzu, x1, y1, row, column, &sum_score, &once_score);
			if (!once_score)
				put_in_nextballs(shuzu, next_balls, column, row);
			cout << endl;
			cct_cls();
			cout << "���ε÷֣�" << once_score << " �ܹ��÷֣�" << sum_score << endl;
			whole_shuzu_print_1(shuzu, row, column);
			if (once_score) {
				cout << endl;
				cout << "�������������ɫ�ֱ��ǣ� " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2];
				cout << endl;
			}
			else {
				generate_balls_3(next_balls);
				cout << endl;
				cout << "�������������ɫ�ֱ��ǣ� " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2];
			}
			if (game_over(shuzu, row, column,ym))
				break;
		}
		else
		{
			cct_cls();
			cout << "�޷��ҵ��ƶ�·��" << endl;
			cout << "���ε÷֣�" << once_score << " �ܹ��÷֣�" << sum_score << endl;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					if (shuzu[i][j] < 0)
						shuzu[i][j] = 0;/*��Ѱ·�����е�-1��Ϊ0*/
				}
			}
			shuzu[y0][x0] = begin;/*��ԭ����*/
			whole_shuzu_print_1(shuzu, row, column);
			cout << "�������������ɫ�ֱ��ǣ� " << next_balls[0] << " " << next_balls[1] << " " << next_balls[2]<<endl;
			continue;
		}
		
	}
	end();

}
