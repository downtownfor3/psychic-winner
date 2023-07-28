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
using namespace std;




/*初始行列*/

void row_column(int* p1, int* p2) {
	int n;
	while (1) {
		cout << "请输入行数(7-9)：" << endl;
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
		cout << "请输入列数(7-9)：" << endl;
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
/*生成球(任意位置，任意颜色）*/
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
/*生成球（后三球）*/
void generate_balls_3(int* next_balls) {
	srand((unsigned int)(time(0)));
	for (int i = 0; i < 3; i++) {
		next_balls[i] = rand() % 7 + 1;
	}
}
/*该函数目的是将生成的后三球放入数组中(放满即可）*/
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
		if (n == 0)/*证明没有空位了*/
			break;

	}
}

/*打印数组*/
void shuzu_print(int(*p)[9], int row, int column, int base_x, int base_y) {
	cct_gotoxy(base_x + 5, base_y + 2);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (*(*(p + i) + j) == 0)/*此处判断目的是将球的位置用色块显示*/
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
			cout << "0  ";/*打印一个都是0的数组*/
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
/*打印数组的边框*/
void biankuang_print(int(*p)[9], int row, int column, int base_x, int base_y) {
	cct_gotoxy(base_x, base_y + 1);
	for (int i = 0; i < column * 3 + 4; i++) {
		cout << "-";
	}/*打印横线*/
	for (int j = 0; j < row + 2; j++) {
		cct_gotoxy(base_x + 2, base_y + j);
		cout << "|";
	}/*打印竖线*/
	for (int j = 0; j < row; j++) {
		cct_gotoxy(base_x, base_y + 2 + j);
		cout << char(65 + j);
	}/*打印左侧字母*/
	cct_gotoxy(base_x + 5, base_y);
	for (int i = 1; i <= column; i++) {
		cout << i << "  ";
	}/*打印上方数字*/
	cct_gotoxy(base_x + 2, base_y + 1);
	cout << "+";
}
/*该函数为完整处理一个数组的打印*/
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

/*寻路函数（应该是运用递归的思路）我的思路是在每一个坐标四周寻找通路，若已经可以到达直接返回1，每一个坐标可看作一个节点，遇到边界或者球则认为次级
通路不通，逐级返回，若在最初级四周不通，则可以认为没有通路，返回0*/
int search(int(*p)[9], int row, int column, int x0, int y0, int x1, int y1, int(*path)[2], int* judge) {
	if (x1 == x0 && y1 == y0)/*此处不需要再考虑初末位置相同的情况，因为在坐标输入时已经保证不会出现*/
	{
		path[*judge][0] = y0;
		path[*judge][1] = x0;
		(*judge)++;
		return 1;
	}
	else
		p[y0][x0] = -1;/*将走过的点由0为-1*/

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

/*坐标*/
void captial(char& R) {
	if (R >= 'a' && R <= 'z')
		R = R - 32;
}/*转大写*/
/*输入*/
void src_coordinate(int(*p)[9], int row, int column, int* x, int* y) {
	char R;
	int col;
	while (1) {
		cout << "请以字母 + 数字形式[例：c2]输入要移动球的矩阵坐标：";
		cin >> R;
		captial(R);
		if (!(cin.good()) || ((R - 'A') >= row)) {
			cout << "输入错误，请重新输入." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		cin >> col;
		if (!(cin.good()) || (col > column || col < 1)) {
			cout << "输入错误，请重新输入." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		if (p[R - 'A'][col - 1] == 0) {
			cout << "起始位置为空，请重新输入." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;

		}
		break;

	}
	cout << "输入为" << R << "行" << col << "列" << endl;
	*x = col - 1;
	*y = R - 'A';
}
void dst_coordinate(int(*p)[9], int row, int column, int* x, int* y) {
	char R;
	int col;
	while (1) {
		cout << "请以字母 + 数字形式[例：c2]输入要移动球的目的坐标：";
		cin >> R;
		captial(R);
		if (!(cin.good()) || ((R - 'A') >= row)) {
			cout << "输入错误，请重新输入." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		cin >> col;
		if (!(cin.good()) || (col > column || col < 1)) {
			cout << "输入错误，请重新输入." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		if (p[R - 'A'][col - 1] != 0) {
			cout << "目标位置非空，请重新输入." << endl;
			while ((getchar()) != '\n');
			cin.clear();
			continue;
		}
		break;

	}
	cout << "输入为" << R << "行" << col << "列" << endl;
	*x = col - 1;
	*y = R - 'A';
}
void coordinate(int(*p)[9], int row, int column, int* x0, int* y0, int* x1, int* y1) {
	src_coordinate(p, row, column, x0, y0);
	dst_coordinate(p, row, column, x1, y1);
}


/*结束语句*/
void end()
{
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;
	int base_x;
	int base_y;
	cct_getxy(base_x, base_y);
	cct_gotoxy(base_x, base_y);
	cout << "本小题结束，请输入End继续...";
	char End[4];
	while (1) {
		for (int i = 0; i < 3; i++)
			cin >> End[i];
		End[3] = '\0';
		if (strcmp("End", End) != 0)/*比较*/
		{
			cout << "输入错误，请重新输入";
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

/*判断游戏是否结束，遍历数组，空格大于等于三个则游戏未结束返回0，否则返回1*/
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
	cout << "无空位可移动，游戏结束!";
	return 1;
}

/*分数函数，负责球的消除，能否得分的判断，以及分数的积累*/
void score(int(*p)[9], int x1, int y1, int row, int column, int* sum_score, int* once_score) {
	/*得分的判断有四种，分别是横 纵 斜两种 五个即以上*/
	int x = x1;
	int y = y1;/*记录目标位置*/
	int the_ball = p[y][x];/*取得所在的颜色*/
	/*横*/
	int row1 = 0, row2 = 0;/*分别向左向右统计，会多数一个自己要减去*/
	while (x - row1 >= 0 && p[y][x - row1] == the_ball)
		row1++;
	while (x + row2 < column && p[y][x + row2] == the_ball)
		row2++;
	int row_num = row1 + row2 - 1;
	/*纵*/
	int col1 = 0, col2 = 0;/*分别向上向下统计，会多数一个自己要减去*/
	while (y - col1 >= 0 && p[y - col1][x] == the_ball)
		col1++;
	while (y + col2 < row && p[y + col2][x] == the_ball)
		col2++;
	int column_num = col1 + col2 - 1;
	/*降斜*/
	int k1 = 0, k2 = 0;
	while (p[y + k1][x + k1] == the_ball && y + k1 < row && x + k1 < column)
		k1++;
	while (p[y - k2][x - k2] == the_ball && y - k2 >= 0 && x - k2 >= 0)
		k2++;
	int k_num = k1 + k2 - 1;
	/*升斜*/
	int K1 = 0, K2 = 0;
	while (p[y - K1][x + K1] == the_ball && y - K1 >= 0 && x + K1 < column)
		K1++;
	while (p[y + K2][x - K2] == the_ball && x - K2 >= 0 && y + K2 < row)
		K2++;
	int K_num = K1 + K2 - 1;

	/*判断能否消去,并且在数组中清除*/
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


/*无分隔棋盘*/
void qipan_1(int(*p)[9], int row, int col)
{
	cct_setconsoleborder(col + 30, row + 20);
	cct_setfontsize("新宋体", 25);
	cout << "屏幕：" << row + 20 << "行" << col + 30 << "列" << endl;


	for (int i = 0; i < col + 2; i++)/*上下边界*/
	{
		if (i == 0) {
			cct_showstr(2 * i, 1, "╔", COLOR_HWHITE, COLOR_BLACK);
			cct_showstr(2 * i, row + 2, "╚", COLOR_HWHITE, COLOR_BLACK);
		}
		else if (i == col + 1) {
			cct_showstr(2 * i, 1, "╗", COLOR_HWHITE, COLOR_BLACK);
			cct_showstr(2 * i, row + 2, "╝", COLOR_HWHITE, COLOR_BLACK);
		}
		else {
			cct_showstr(2 * i, 1, "═", COLOR_HWHITE, COLOR_BLACK);
			cct_showstr(2 * i, row + 2, "═", COLOR_HWHITE, COLOR_BLACK);
		}
	}

	for (int j = 0; j < row; j++)/*左右边界*/
	{
		cct_showstr(0, 2 + j, "║", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 * (col + 1), 2 + j, "║", COLOR_HWHITE, COLOR_BLACK);
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (p[i][j] != 0)
				cct_showstr(2 * (j + 1), i + 2, "〇", p[i][j] + 1, COLOR_HWHITE);
			else
				cct_showstr(2 * (j + 1), i + 2, "  ", COLOR_HWHITE, COLOR_HWHITE);
		}
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cct_gotoxy(0, row + 2);
	cout << endl;
}

/*有分隔棋盘*/
void qipan_2(int(*p)[9], int row, int col)
{
	/*函数完成的关键在于对于坐标的计算，在何处打印何种字符，注意符号的长度都是2*/
	cct_setconsoleborder(col * 2 + 50, row * 2 + 10);
	cct_setfontsize("新宋体", 25);
	cout << "屏幕：" << row * 2 + 10 << "行" << col * 2 + 50 << "列" << endl;

	for (int i = 0; i < 2 * row + 1; i++)
		for (int j = 0; j < 2 * col + 1; j++)
		{
			if (i == 0)
			{

				if (j == 0)
					cct_showstr(0, 1, "╔", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * col)
					cct_showstr(j * 2, 1, "╗", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * col - 1)
					cct_showstr(j * 2, 1, "═", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						cct_showstr(2 * j, 1, "═", COLOR_HWHITE, COLOR_BLACK);
					else
						cct_showstr(2 * j, 1, "╦", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else if (i == 2 * row)
			{
				if (j == 0)
					cct_showstr(0, i + 1, "╚", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * col)
					cct_showstr(j * 2, i + 1, "╝", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * col - 1)
					cct_showstr(j * 2, i + 1, "═", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						cct_showstr(2 * j, i + 1, "═", COLOR_HWHITE, COLOR_BLACK);
					else
						cct_showstr(2 * j, i + 1, "╩", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else
			{
				if (j == 0)
					if (i % 2 == 1)
						cct_showstr(2 * j, i + 1, "║", COLOR_HWHITE, COLOR_BLACK);
					else
						cct_showstr(2 * j, i + 1, "╟", COLOR_HWHITE, COLOR_BLACK);
				else if (j == col * 2)
					if (i % 2 == 1)
						cct_showstr(2 * j, i + 1, "║", COLOR_HWHITE, COLOR_BLACK);
					else
						cct_showstr(2 * j, i + 1, "╣", COLOR_HWHITE, COLOR_BLACK);
				else
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
							cct_showstr(2 * j, i + 1, "  ", COLOR_HWHITE, COLOR_BLACK);
						else
							cct_showstr(2 * j, i + 1, "║", COLOR_HWHITE, COLOR_BLACK);
					}
					else
					{
						if (j % 2 == 1)
							cct_showstr(2 * j, i + 1, "═", COLOR_HWHITE, COLOR_BLACK);
						else if (j != 0 && j != col * 2)
							cct_showstr(2 * j, i + 1, "╬", COLOR_HWHITE, COLOR_BLACK);
					}
			}
		}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (p[i][j] != 0)
				cct_showstr(2 + j * 4, (i + 1) * 2, "○", p[i][j] + 1, COLOR_HWHITE);
	cct_gotoxy(0, row * 2 + 2);

	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
}

/*球的移动，动画模拟，与汉诺塔类似，完成一步移动擦掉前一步的位置，加延迟*/
void moving_steps(int(*path)[2], int begin, int judge)
{

	for (int k = judge - 2; k >= 0; k--)
	{
		if (k != 0)
			cct_showstr(2 + path[k][1] * 4, (path[k][0] + 1) * 2, "◎", begin + 1, COLOR_HWHITE);
		else
			cct_showstr(2 + path[k][1] * 4, (path[k][0] + 1) * 2, "○", begin + 1, COLOR_HWHITE);
		cct_showstr(2 + path[k + 1][1] * 4, (path[k + 1][0] + 1) * 2, "  ", COLOR_HWHITE, COLOR_HWHITE);
		Sleep(150);
	}
}

/*读鼠标函数，确定点击位置，随时显示当前位置*/
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
			cout << "[当前光标]" << char((Y - 1) / 2 + 'A') << "行" << X / 4 + 1 << "列";
			switch (maction)
			{
			case MOUSE_RIGHT_BUTTON_CLICK:
				end();
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				if (click >= 0 && p[(Y - 1) / 2][X / 4] != 0)
				{
					if (click)/*这一步是为了挑选不同的第一个球，还原已经选的*/
						cct_showstr(2 + x0 * 4, y0 * 2 + 2, "○", p[y0][x0] + 1, COLOR_HWHITE);
					y0 = (Y - 1) / 2;
					x0 = X / 4;
					cct_showstr(2 + X / 4 * 4, (Y - 1) / 2 * 2 + 2, "◎", p[y0][x0] + 1, COLOR_HWHITE);
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

/*右侧状态栏的打印*/
/*三部分，分别是得分，新彩球提示，和已有彩球和消去彩球的统计*/
/*统计棋盘上各种颜色球的数目*/
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
	/*得分*/
	cct_showstr(4 * col + 4, 1, "╔", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 1, "╗", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 4, 3, "╚", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 3, "╝", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 2 * col + 3; i < 2 * col + 8; i++) {
		cct_showstr(2 * i, 3, "═", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 * i, 1, "═", COLOR_HWHITE, COLOR_BLACK);
	}
	cct_showstr(4 * col + 4, 2, "║", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 2, "║", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 6, 2, "得分：    ", COLOR_HWHITE, COLOR_BLACK);
	cct_showint(4 * col + 14, 2, sum_score, COLOR_HWHITE, COLOR_BLACK);

	/*新球*/
	cct_showstr(4 * col + 4, 5, "╔", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 5, "╗", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 4, 7, "╚", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 7, "╝", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 2 * col + 3; i < 2 * col + 8; i++) {
		cct_showstr(2 * i, 7, "═", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 * i, 5, "═", COLOR_HWHITE, COLOR_BLACK);
	}
	cct_showstr(4 * col + 4, 6, "║", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 16, 6, "║", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 0; i < 3; i++)
	{
		cct_showstr(2 * (2 * col + 3 + 2 * i), 6, "○", balls[i] + 1, COLOR_HWHITE);
		cct_showstr(2 * (2 * col + 3 + 2 * i) + 2, 6, "┃", COLOR_HWHITE, COLOR_BLACK);
	}

	/*统计*/
	cct_showstr(4 * col + 4, 9, "╔", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 28, 9, "╗", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 4, 18, "╚", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(4 * col + 28, 18, "╝", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 2 * col + 3; i < 2 * col + 14; i++) {
		cct_showstr(2 * i, 18, "═", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 * i, 9, "═", COLOR_HWHITE, COLOR_BLACK);
	}
	
	for (int i = 0; i < 8; i++) {
		
		cct_showstr(4 * col + 6, 10 + i, "                        ", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(4 * col + 6, 10 + i, "○", i + 1, COLOR_HWHITE);
		if (i == 0)
			cct_showstr(4 * col + 6, 10 + i, "  ", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(4 * col + 4, 10+i, "║", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(4 * col + 28, 10+i, "║", COLOR_HWHITE, COLOR_BLACK);

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
