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
using namespace std;




/*��ʼ����*/

void row_column(int* p1, int* p2) {
	int n;
	while (1) {
		cout << "����������(7-9)��" << endl;
		cin >> n;
		if (n >= 7 && n <= 9) {
			*p1 = n;
			break;
		}
		else {
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
	}
	while (1) {
		cout << "����������(7-9)��" << endl;
		cin >> n;
		if (n >= 7 && n <= 9) {
			*p2 = n;
			break;
		}
		else {
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
	}
}
/*������(����λ�ã�������ɫ��*/
void generate_balls(int(*p)[9], int row, int column, int solution) {
	srand((unsigned int)(time(0)));
	int n;
	if (solution == 1 || solution == 3)
		n = 5;
	else
		n = int(0.6 * row * column);
	for (int i = 0; i < n;)
	{
		int x = rand() % column;
		int y = rand() % row;
		if (*(*(p + y) + x) == 0)
		{
			*(*(p + y) + x) = rand() % 7 + 1;
			i++;
		}
	}

}
/*�����򣨺�����*/
void generate_balls_3(int* next_balls) {
	srand((unsigned int)(time(0)));
	for (int i = 0; i < 3; i++) {
		next_balls[i] = rand() % 7 + 1;
	}
}
/*�ú���Ŀ���ǽ����ɵĺ��������������(�������ɣ�*/
void put_in_nextballs(int(*p)[9], int* next_balls, int column, int row)
{
	srand((unsigned int)(time(0)));
	for (int i = 0; i < 3;)
	{
		int x = rand() % column;
		int y = rand() % row;
		if (p[y][x] == 0)
		{
			p[y][x] = next_balls[i];
			i++;
		}
		int n = 0;
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < column; k++) {
				if (p[j][k] == 0)
					n++;
			}
		}
		if (n == 0)/*֤��û�п�λ��*/
			break;

	}
}

/*��ӡ����*/
void shuzu_print(int(*p)[9], int row, int column, int base_x, int base_y) {
	cct_gotoxy(base_x + 5, base_y + 2);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (*(*(p + i) + j) == 0)/*�˴��ж�Ŀ���ǽ����λ����ɫ����ʾ*/
				cout << *(*(p + i) + j) << "  ";
			else {
				cct_setcolor(14, *(*(p + i) + j));
				cout << *(*(p + i) + j);
				cct_setcolor();
				cout << "  ";
			}


		}
		cct_gotoxy(base_x + 5, base_y + 3 + i);
	}
}
void shuzu_print_2(int(*p)[9], int(*path)[2], int judge, int row, int column, int base_x, int base_y) {
	cct_gotoxy(base_x + 5, base_y + 2);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << "0  ";/*��ӡһ������0������*/
		}
		cct_gotoxy(base_x + 5, base_y + 3 + i);
	}
	base_x = base_x + 5;
	base_y = base_y + 2;
	int k = judge - 1;
	for (; k >= 0; k--) {
		cct_gotoxy(base_x + 3 * path[k][1], base_y + path[k][0]);
		cout << "*";
	}

}
void shuzu_print_3(int(*p)[9], int(*path)[2], int judge, int row, int column, int base_x, int base_y) {
	cct_gotoxy(base_x + 5, base_y + 2);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << *(*(p + i) + j) << "  ";
		}
		cct_gotoxy(base_x + 5, base_y + 3 + i);
	}
	base_x = base_x + 5;
	base_y = base_y + 2;
	int k = judge - 1;
	for (; k >= 0; k--) {
		cct_gotoxy(base_x + 3 * path[k][1], base_y + path[k][0]);
		cct_setcolor(14, *(*(p + path[k][0]) + path[k][1]));
		cout << *(*(p + path[k][0]) + path[k][1]);
		cct_setcolor();
		cout << "  ";
	}

}
/*��ӡ����ı߿�*/
void biankuang_print(int(*p)[9], int row, int column, int base_x, int base_y) {
	cct_gotoxy(base_x, base_y + 1);
	for (int i = 0; i < column * 3 + 4; i++) {
		cout << "-";
	}/*��ӡ����*/
	for (int j = 0; j < row + 2; j++) {
		cct_gotoxy(base_x + 2, base_y + j);
		cout << "|";
	}/*��ӡ����*/
	for (int j = 0; j < row; j++) {
		cct_gotoxy(base_x, base_y + 2 + j);
		cout << char(65 + j);
	}/*��ӡ�����ĸ*/
	cct_gotoxy(base_x + 5, base_y);
	for (int i = 1; i <= column; i++) {
		cout << i << "  ";
	}/*��ӡ�Ϸ�����*/
	cct_gotoxy(base_x + 2, base_y + 1);
	cout << "+";
}
/*�ú���Ϊ��������һ������Ĵ�ӡ*/
void whole_shuzu_print_1(int(*p)[9], int row, int column) {
	int base_x;
	int base_y;
	cct_getxy(base_x, base_y);
	shuzu_print(p, row, column, base_x, base_y);
	biankuang_print(p, row, column, base_x, base_y);
	cct_gotoxy(base_x, base_y + row + 2);

}
void whole_shuzu_print_2(int(*p)[9], int(*path)[2], int judge, int row, int column, int solution) {
	int base_x;
	int base_y;
	cct_getxy(base_x, base_y);
	if (solution == 1)
		shuzu_print_2(p, path, judge, row, column, base_x, base_y);
	else
		shuzu_print_3(p, path, judge, row, column, base_x, base_y);
	biankuang_print(p, row, column, base_x, base_y);
	cct_gotoxy(base_x, base_y + row + 2);

}

/*Ѱ·������Ӧ�������õݹ��˼·���ҵ�˼·����ÿһ����������Ѱ��ͨ·�����Ѿ����Ե���ֱ�ӷ���1��ÿһ������ɿ���һ���ڵ㣬�����߽����������Ϊ�μ�
ͨ·��ͨ���𼶷��أ�������������ܲ�ͨ���������Ϊû��ͨ·������0*/
int search(int(*p)[9], int row, int column, int x0, int y0, int x1, int y1, int(*path)[2], int* judge) {
	if (x1 == x0 && y1 == y0)/*�˴�����Ҫ�ٿ��ǳ�ĩλ����ͬ���������Ϊ����������ʱ�Ѿ���֤�������*/
	{
		path[*judge][0] = y0;
		path[*judge][1] = x0;
		(*judge)++;
		return 1;
	}
	else
		p[y0][x0] = -1;/*���߹��ĵ���0Ϊ-1*/

	if ((x0 != column - 1) && (p[y0][x0 + 1] == 0))
	{
		search(p, row, column, x0 + 1, y0, x1, y1, path, judge);
		if (*judge)
		{
			path[*judge][0] = y0;
			path[*judge][1] = x0;
			(*judge)++;
			return 1;
		}
	}
	if ((y0 != 0) && (p[y0 - 1][x0] == 0))
	{
		search(p, row, column, x0, y0 - 1, x1, y1, path, judge);
		if (*judge)
		{
			path[*judge][0] = y0;
			path[*judge][1] = x0;
			(*judge)++;
			return 1;
		}
	}
	if ((x0 != 0) && (p[y0][x0 - 1] == 0))
	{
		search(p, row, column, x0 - 1, y0, x1, y1, path, judge);
		if (*judge)
		{
			path[*judge][0] = y0;
			path[*judge][1] = x0;
			(*judge)++;
			return 1;
		}
	}
	if ((y0 != row - 1) && (p[y0 + 1][x0] == 0))
	{
		search(p, row, column, x0, y0 + 1, x1, y1, path, judge);
		if (*judge)
		{
			path[*judge][0] = y0;
			path[*judge][1] = x0;
			(*judge)++;
			return 1;
		}
	}
	return 0;


}

/*����*/
void captial(char& R) {
	if (R >= 'a' && R <= 'z')
		R = R - 32;
}/*ת��д*/
/*����*/
void src_coordinate(int(*p)[9], int row, int column, int* x, int* y) {
	char R;
	int col;
	while (1) {
		cout << "������ĸ + ������ʽ[����c2]����Ҫ�ƶ���ľ������꣺";
		cin >> R;
		captial(R);
		if (!(cin.good()) || ((R - 'A') >= row)) {
			cout << "�����������������." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		cin >> col;
		if (!(cin.good()) || (col > column || col < 1)) {
			cout << "�����������������." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		if (p[R - 'A'][col - 1] == 0) {
			cout << "��ʼλ��Ϊ�գ�����������." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;

		}
		break;

	}
	cout << "����Ϊ" << R << "��" << col << "��" << endl;
	*x = col - 1;
	*y = R - 'A';
}
void dst_coordinate(int(*p)[9], int row, int column, int* x, int* y) {
	char R;
	int col;
	while (1) {
		cout << "������ĸ + ������ʽ[����c2]����Ҫ�ƶ����Ŀ�����꣺";
		cin >> R;
		captial(R);
		if (!(cin.good()) || ((R - 'A') >= row)) {
			cout << "�����������������." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		cin >> col;
		if (!(cin.good()) || (col > column || col < 1)) {
			cout << "�����������������." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		if (p[R - 'A'][col - 1] != 0) {
			cout << "Ŀ��λ�÷ǿգ�����������." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		break;

	}
	cout << "����Ϊ" << R << "��" << col << "��" << endl;
	*x = col - 1;
	*y = R - 'A';
}
void coordinate(int(*p)[9], int row, int column, int* x0, int* y0, int* x1, int* y1) {
	src_coordinate(p, row, column, x0, y0);
	dst_coordinate(p, row, column, x1, y1);
}


/*�������*/
void end()
{
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;
	int base_x;
	int base_y;
	cct_getxy(base_x, base_y);
	cct_gotoxy(base_x, base_y);
	cout << "��С�������������End����...";
	char End[4];
	while (1) {
		for (int i = 0; i < 3; i++)
			cin >> End[i];
		End[3] = '\0';
		if (strcmp("End", End) != 0)/*�Ƚ�*/
		{
			cout << "�����������������";
			while ((getchar()) != '\n');
			cct_gotoxy(base_x + 28, base_y);
			cout << "               ";
			cct_gotoxy(base_x + 28, base_y);
		}
		else
			break;
	}
	cct_cls();


}

/*�ж���Ϸ�Ƿ�������������飬�ո���ڵ�����������Ϸδ��������0�����򷵻�1*/
int game_over(int(*p)[9], int row, int column,int y_m)
{
	int i, j, n = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
			if (p[i][j] == 0)
			{
				n++;
				if (n >= 3)
					return 0;
			}
	}
	cct_gotoxy(0, y_m);
	cct_setcolor();
	cout << "�޿�λ���ƶ�����Ϸ����!";
	return 1;
}

/*������������������������ܷ�÷ֵ��жϣ��Լ������Ļ���*/
void score(int(*p)[9], int x1, int y1, int row, int column, int* sum_score, int* once_score) {
	/*�÷ֵ��ж������֣��ֱ��Ǻ� �� б���� ���������*/
	int x = x1;
	int y = y1;/*��¼Ŀ��λ��*/
	int the_ball = p[y][x];/*ȡ�����ڵ���ɫ*/
	/*��*/
	int row1 = 0, row2 = 0;/*�ֱ���������ͳ�ƣ������һ���Լ�Ҫ��ȥ*/
	while (x - row1 >= 0 && p[y][x - row1] == the_ball)
		row1++;
	while (x + row2 < column && p[y][x + row2] == the_ball)
		row2++;
	int row_num = row1 + row2 - 1;
	/*��*/
	int col1 = 0, col2 = 0;/*�ֱ���������ͳ�ƣ������һ���Լ�Ҫ��ȥ*/
	while (y - col1 >= 0 && p[y - col1][x] == the_ball)
		col1++;
	while (y + col2 < row && p[y + col2][x] == the_ball)
		col2++;
	int column_num = col1 + col2 - 1;
	/*��б*/
	int k1 = 0, k2 = 0;
	while (p[y + k1][x + k1] == the_ball && y + k1 < row && x + k1 < column)
		k1++;
	while (p[y - k2][x - k2] == the_ball && y - k2 >= 0 && x - k2 >= 0)
		k2++;
	int k_num = k1 + k2 - 1;
	/*��б*/
	int K1 = 0, K2 = 0;
	while (p[y - K1][x + K1] == the_ball && y - K1 >= 0 && x + K1 < column)
		K1++;
	while (p[y + K2][x - K2] == the_ball && x - K2 >= 0 && y + K2 < row)
		K2++;
	int K_num = K1 + K2 - 1;

	/*�ж��ܷ���ȥ,���������������*/
	if (row_num >= 5) {
		*once_score += (row_num - 1) * (row_num - 2);
		for (int i = x - row1 + 1; i < x + row2; i++)
			p[y][i] = 0;
	}
	if (column_num >= 5) {
		*once_score += (column_num - 1) * (column_num - 2);
		for (int i = y - col1 + 1; i < y + col2; i++)
			p[i][x] = 0;
	}
	if (K_num >= 5) {
		*once_score += (K_num - 1) * (K_num - 2);
		for (int i = -K1 + 1; i < K2; i++)
			p[y + i][x - i] = 0;
	}
	if (k_num >= 5) {
		*once_score += (k_num - 1) * (k_num - 2);
		for (int i = -k1 + 1; i < k2; i++)
			p[y + i][y + i] = 0;
	}
	*sum_score += *once_score;
}


/*�޷ָ�����*/
void qipan_1(int(*p)[9], int row, int col)
{
	cct_setconsoleborder(col + 30, row + 20);
	cct_setfontsize("������", 25);
	cout << "��Ļ��" << row + 20 << "��" << col + 30 << "��" << endl;


	for (int i = 0; i < col + 2; i++)/*���±߽�*/
	{
		if (i == 0) {
			cct_showstr(2 * i, 1, "�X", COLOR_HWHITE, COLOR_BLACK);
			cct_showstr(2 * i, row + 2, "�^", COLOR_HWHITE, COLOR_BLACK);
		}
		else if (i == col + 1) {
			cct_showstr(2 * i, 1, "�[", COLOR_HWHITE, COLOR_BLACK);
			cct_showstr(2 * i, row + 2, "�a", COLOR_HWHITE, COLOR_BLACK);
		}
		else {
			cct_showstr(2 * i, 1, "�T", COLOR_HWHITE, COLOR_BLACK);
			cct_showstr(2 * i, row + 2, "�T", COLOR_HWHITE, COLOR_BLACK);
		}
	}

	for (int j = 0; j < row; j++)/*���ұ߽�*/
	{
		cct_showstr(0, 2 + j, "�U", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 * (col + 1), 2 + j, "�U", COLOR_HWHITE, COLOR_BLACK);
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (p[i][j] != 0)
				cct_showstr(2 * (j + 1), i + 2, "��", p[i][j] + 1, COLOR_HWHITE);
			else
				cct_showstr(2 * (j + 1), i + 2, "  ", COLOR_HWHITE, COLOR_HWHITE);
		}
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cct_gotoxy(0, row + 2);
	cout << endl;
}

/*�зָ�����*/
void qipan_2(int(*p)[9], int row, int col)
{
	/*������ɵĹؼ����ڶ�������ļ��㣬�ںδ���ӡ�����ַ���ע����ŵĳ��ȶ���2*/
	cct_setconsoleborder(col * 2 + 50, row * 2 + 10);
	cct_setfontsize("������", 25);
	cout << "��Ļ��" << row * 2 + 10 << "��" << col * 2 + 50 << "��" << endl;

	for (int i = 0; i < 2 * row + 1; i++)
		for (int j = 0; j < 2 * col + 1; j++)
		{
			if (i == 0)
			{

				if (j == 0)
					cct_showstr(0, 1, "�X", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * col)
					cct_showstr(j * 2, 1, "�[", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * col - 1)
					cct_showstr(j * 2, 1, "�T", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						cct_showstr(2 * j, 1, "�T", COLOR_HWHITE, COLOR_BLACK);
					else
						cct_showstr(2 * j, 1, "�j", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else if (i == 2 * row)
			{
				if (j == 0)
					cct_showstr(0, i + 1, "�^", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * col)
					cct_showstr(j * 2, i + 1, "�a", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * col - 1)
					cct_showstr(j * 2, i + 1, "�T", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						cct_showstr(2 * j, i + 1, "�T", COLOR_HWHITE, COLOR_BLACK);
					else
						cct_showstr(2 * j, i + 1, "�m", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else
			{
				if (j == 0)
					if (i % 2 == 1)
						cct_showstr(2 * j, i + 1, "�U", COLOR_HWHITE, COLOR_BLACK);
					else
						cct_showstr(2 * j, i + 1, "�c", COLOR_HWHITE, COLOR_BLACK);
				else if (j == col * 2)
					if (i % 2 == 1)
						cct_showstr(2 * j, i + 1, "�U", COLOR_HWHITE, COLOR_BLACK);
					else
						cct_showstr(2 * j, i + 1, "�g", COLOR_HWHITE, COLOR_BLACK);
				else
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
							cct_showstr(2 * j, i + 1, "  ", COLOR_HWHITE, COLOR_BLACK);
						else
							cct_showstr(2 * j, i + 1, "�U", COLOR_HWHITE, COLOR_BLACK);
					}
					else
					{
						if (j % 2 == 1)
							cct_showstr(2 * j, i + 1, "�T", COLOR_HWHITE, COLOR_BLACK);
						else if (j != 0 && j != col * 2)
							cct_showstr(2 * j, i + 1, "�p", COLOR_HWHITE, COLOR_BLACK);
					}
			}
		}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (p[i][j] != 0)
				cct_showstr(2 + j * 4, (i + 1) * 2, "��", p[i][j] + 1, COLOR_HWHITE);
	cct_gotoxy(0, row * 2 + 2);

	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
}

/*����ƶ�������ģ�⣬�뺺ŵ�����ƣ����һ���ƶ�����ǰһ����λ�ã����ӳ�*/
void moving_steps(int(*path)[2], int begin, int judge)
{

	for (int k = judge - 2; k >= 0; k--)
	{
		if (k != 0)
			cct_showstr(2 + path[k][1] * 4, (path[k][0] + 1) * 2, "��", begin + 1, COLOR_HWHITE);
		else
			cct_showstr(2 + path[k][1] * 4, (path[k][0] + 1) * 2, "��", begin + 1, COLOR_HWHITE);
		cct_showstr(2 + path[k + 1][1] * 4, (path[k + 1][0] + 1) * 2, "  ", COLOR_HWHITE, COLOR_HWHITE);
		Sleep(150);
	}
}

/*����꺯����ȷ�����λ�ã���ʱ��ʾ��ǰλ��*/
void read_mouse(int(*p)[9], int& x0, int& y0, int& x1, int& y1, int row, int col, int y_m) {
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int click = 0;
	int loop = 1;

	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);
	while (loop)
	{
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		cct_gotoxy(0, y_m);

		if ((Y - 1) / 2 + 1 > 0 && (Y - 1) / 2 + 1 <= row && (X / 4 + 1) > 0 && (X / 4 + 1) <= col)
		{
			cct_setcolor();
			cout << "[��ǰ���]" << char((Y - 1) / 2 + 'A') << "��" << X / 4 + 1 << "��";
			switch (maction)
			{
			case MOUSE_RIGHT_BUTTON_CLICK:
				end();
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				if (click >= 0 && p[(Y - 1) / 2][X / 4] != 0)
				{
					if (click)/*��һ����Ϊ����ѡ��ͬ�ĵ�һ���򣬻�ԭ�Ѿ�ѡ��*/
						cct_showstr(2 + x0 * 4, y0 * 2 + 2, "��", p[y0][x0] + 1, COLOR_HWHITE);
					y0 = (Y - 1) / 2;
					x0 = X / 4;
					cct_showstr(2 + X / 4 * 4, (Y - 1) / 2 * 2 + 2, "��", p[y0][x0] + 1, COLOR_HWHITE);
					click++;
					break;
				}
				else if (click > 0 && p[(Y - 1) / 2][X / 4] == 0)
				{
					y1 = (Y - 1) / 2;
					x1 = X / 4;
					loop = 0;
					break;
				}

			}
		}
	}

}

/*�Ҳ�״̬���Ĵ�ӡ*/
/*�����֣��ֱ��ǵ÷֣��²�����ʾ�������в������ȥ�����ͳ��*/
/*ͳ�������ϸ�����ɫ�����Ŀ*/
void statistic(int(*p)[9], int* num, int row, int column) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			switch (p[i][j]) {
			case 0:
				num[0]++;
				break;
			case 1:
				num[1]++;
				break;
			case 2:
				num[2]++;
				break;
			case 3:
				num[3]++;
				break;
			case 4:
				num[4]++;
				break;
			case 5:
				num[5]++;
				break;
			case 6:
				num[6]++;
				break;
			case 7:
				num[7]++;
				break;
			}
		}
	}

}
void right_(int row,int col, int sum_score,int(*p)[9], int* balls) {
	/*�÷�*/
	cct_showstr(4 * col + 4, 1, "�X", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 1, "�[", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 4, 3, "�^", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 3, "�a", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 2 * col + 3; i < 2 * col + 8; i++) {
		cct_showstr(2 * i, 3, "�T", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 * i, 1, "�T", COLOR_HWHITE, COLOR_BLACK);
	}
	cct_showstr(4 * col + 4, 2, "�U", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 2, "�U", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 6, 2, "�÷֣�    ", COLOR_HWHITE, COLOR_BLACK);
	cct_showint(4 * col + 14, 2, sum_score, COLOR_HWHITE, COLOR_BLACK);

	/*����*/
	cct_showstr(4 * col + 4, 5, "�X", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 5, "�[", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 4, 7, "�^", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 7, "�a", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 2 * col + 3; i < 2 * col + 8; i++) {
		cct_showstr(2 * i, 7, "�T", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 * i, 5, "�T", COLOR_HWHITE, COLOR_BLACK);
	}
	cct_showstr(4 * col + 4, 6, "�U", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 6, "�U", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 0; i < 3; i++)
	{
		cct_showstr(2 * (2 * col + 3 + 2 * i), 6, "��", balls[i] + 1, COLOR_HWHITE);
		cct_showstr(2 * (2 * col + 3 + 2 * i) + 2, 6, "��", COLOR_HWHITE, COLOR_BLACK);
	}

	/*ͳ��*/
	cct_showstr(4 * col + 4, 9, "�X", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 28, 9, "�[", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 4, 18, "�^", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 28, 18, "�a", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 2 * col + 3; i < 2 * col + 14; i++) {
		cct_showstr(2 * i, 18, "�T", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 * i, 9, "�T", COLOR_HWHITE, COLOR_BLACK);
	}
	
	for (int i = 0; i < 8; i++) {
		
		cct_showstr(4 * col + 6, 10 + i, "                        ", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(4 * col + 6, 10 + i, "��", i + 1, COLOR_HWHITE);
		if (i == 0)
			cct_showstr(4 * col + 6, 10 + i, "  ", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(4 * col + 4, 10+i, "�U", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(4 * col + 28, 10+i, "�U", COLOR_HWHITE, COLOR_BLACK);

		cct_showstr(4 * col + 8, 10 + i, ":  /(      ) ", COLOR_HWHITE, COLOR_BLACK);
	}
	int num[8] = { 0 };
	statistic(p, num, row, col);
	for (int i = 0; i < 8; i++) {
		cct_showint(4 * col +9, 10 + i, num[i], COLOR_HWHITE, COLOR_BLACK);
		cct_gotoxy(4 * col + 13, 10 + i);
	    cout << fixed << setprecision(2) <<setw(5)<< num[i] / 81.00 * 100 << "%";
	}

}
