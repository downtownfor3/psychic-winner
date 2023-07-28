/* 国06 2252075 刘文飞 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include"hanoi.h"
using namespace std;
/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

int num = 0;
int top[3] = {};
int tower[3][10] = {};
int n_zhi(char src) {
	if (src == 'A')
		return tower[0][top[0]];
	if (src == 'B')
		return tower[1][top[1]];
	if (src == 'C')
		return tower[2][top[2]];
	else
		return 0;
}
void move(char src, char dst, int x, int sol) {
	if (src == 'A') {
		cct_gotoxy(x, 20 + sol * 10 - top[0]);
		cout << "  ";
	}
	if (src == 'B') {
		cct_gotoxy(x + 10, 20 + sol * 10 - top[1]);
		cout << "  ";
	}
	if (src == 'C') {
		cct_gotoxy(x + 20, 20 + sol * 10 - top[2]);
		cout << "  ";
	}
	if (dst == 'A') {
		cct_gotoxy(x + 1, 20 + sol * 10 - top[0] + 1);
		cout << tower[0][top[0] - 1];
	}
	if (dst == 'B') {
		cct_gotoxy(x + 10 + 1, 20 + sol * 10 - top[1] + 1);
		cout << tower[1][top[1] - 1];
	}
	if (dst == 'C') {
		cct_gotoxy(x + 20 + 1, 20 + sol * 10 - top[2] + 1);
		cout << tower[2][top[2] - 1];
	}

}
void zong_xiang_dayin(int x, int y, int T[][10], int top, int Tower) {
	cct_gotoxy(x, y);
	int i;
	for (i = 1; i <= top; i++) {
		cout << setw(2) << T[Tower][i - 1];
		cct_gotoxy(x, y - i);
	}
}
void heng_xiang_dayin(int xianshi, int n, char src, char dst, int sol) {
	cct_gotoxy(0, 25 + sol * 10);
	cout << "第" << setw(4) << ++num << ' ' << "步(" << setw(2) << n << ")" << ": " << src << "-->" << dst;
	if (xianshi) {
		int i;
		cout << " A:";
		for (i = 0; i < top[0]; i++) {
			cout << setw(2) << tower[0][i];
		}
		for (i = 9; i >= top[0]; i--) {
			cout << "  ";
		}
		cout << " B:";
		for (i = 0; i < top[1]; i++) {
			cout << setw(2) << tower[1][i];
		}
		for (i = 9; i >= top[1]; i--) {
			cout << "  ";
		}
		cout << " C:";
		for (i = 0; i < top[2]; i++) {
			cout << setw(2) << tower[2][i];
		}
		for (i = 9; i >= top[2]; i--) {
			cout << "  ";
		}
		cout << endl;
		return;

	}
	else
		return;
}
void chu_ru_(char src, char dst) {
	int out = 0;
	if (src == 'A')
		out = tower[0][--top[0]];
	if (src == 'B')
		out = tower[1][--top[1]];
	if (src == 'C')
		out = tower[2][--top[2]];
	if (dst == 'A')
		tower[0][top[0]++] = out;
	if (dst == 'B')
		tower[1][top[1]++] = out;
	if (dst == 'C')
		tower[2][top[2]++] = out;
}
void pan_move(char src, char dst, int n, int t);
void da_yin(int s, int n, char src, char dst, int xianshi, int t) {
	if (s == 1) {
		cout << setw(3) << n << '#' << ' ' << src << "-->" << dst << endl;
	}
	if (s == 2) {
		cout << setw(5) << ++num << ':' << setw(3) << n << '#' << ' ' << src << "-->" << dst << endl;
	}
	if (s == 3) {
		chu_ru_(src, dst);
		cout << "第" << setw(4) << ++num << ' ' << "步(" << setw(2) << n << ")" << ": " << src << "-->" << dst;
		int i;
		cout << " A:";
		for (i = 0; i < top[0]; i++) {
			cout << setw(2) << tower[0][i];
		}
		for (i = 9; i >= top[0]; i--) {
			cout << "  ";
		}
		cout << " B:";
		for (i = 0; i < top[1]; i++) {
			cout << setw(2) << tower[1][i];
		}
		for (i = 9; i >= top[1]; i--) {
			cout << "  ";
		}
		cout << " C:";
		for (i = 0; i < top[2]; i++) {
			cout << setw(2) << tower[2][i];
		}
		for (i = 9; i >= top[2]; i--) {
			cout << "  ";
		}
		cout << endl;
	}
	if (s == 4) {
		if (t != 0) {
			chu_ru_(src, dst);
			move(src, dst, base_Ax, 0);
			heng_xiang_dayin(xianshi, n, src, dst, 0);
			Sleep(1050 - t * 200);
		}
		else {
			while (1) {
				if (getchar() == '\n')
					break;
			}
			chu_ru_(src, dst);
			move(src, dst, base_Ax, 0);
			heng_xiang_dayin(xianshi, n, src, dst, 0);

		}
	}


	if (s == 8) {
		if (t != 0) {
			chu_ru_(src, dst);
			move(src, dst, base_Ax, 1);
			heng_xiang_dayin(1, n, src, dst, 1);
			pan_move(src, dst, n, t);
			cct_setcolor();
			if (n == 1)
				cct_gotoxy(0, 25);
		}
		else {
			while (1) {
				if (getchar() == '\n')
					break;
			}
			chu_ru_(src, dst);
			move(src, dst, base_Ax, 1);
			heng_xiang_dayin(1, n, src, dst, 1);
			pan_move(src, dst, n, t);
			cct_setcolor();
			if (n == 1)
				cct_gotoxy(0, 25);
		}
	}
}
void hanoi(int n, char src, char tmp, char dst, int s, int xianshi, int t)
{
	if (n == 1) {
		da_yin(s, n, src, dst, xianshi, t);
	}
	else {
		hanoi(n - 1, src, dst, tmp, s, xianshi, t);
		da_yin(s, n, src, dst, xianshi, t);
		hanoi(n - 1, tmp, src, dst, s, xianshi, t);
	}
}
void chu_shi_hua(int* n, char* src, char* tmp, char* dst, int sol, int* xianshi, int* t) {
	num = 0;
	int i, j;
	for (i = 0; i < 3; i++)
		top[i] = 0;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 10; j++)
			tower[i][j] = 0;
	}

	int t1, t2;
	int n1;
	while (1) {

		cout << "请输入汉诺塔的层数(1-10)" << endl;
		cin >> n1;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000000, '\n');
			continue;
		}
		if (n1 < 1 || n1>10) {
			cin.ignore(10000000, '\n');
			continue;
		}

		else {
			cin.ignore(10000000, '\n');
			break;
		}
	}
	*n = n1;
	while (1) {
		cout << "请输入起始柱(A-C)" << endl;
		t1 = getchar();
		while ((getchar()) != '\n');
		if (t1 == 65 || t1 == 66 || t1 == 67 || t1 == 97 || t1 == 98 || t1 == 99)
			break;
		else
			continue;
	}
	while (1) {
		cout << "请输入目标柱(A-C)" << endl;
		t2 = getchar();
		while ((getchar()) != '\n');
		if ((t2 == 65 || t2 == 66 || t2 == 67 || t2 == 97 || t2 == 98 || t2 == 99) && t1 != t2)
			break;
		else if (t1 == t2) {
			if (t1 == 65 || t1 == 97)
				cout << "目标柱(A)不能与起始柱(A)相同" << endl;
			if (t1 == 66 || t1 == 98)
				cout << "目标柱(B)不能与起始柱(B)相同" << endl;
			if (t1 == 67 || t1 == 99)
				cout << "目标柱(C)不能与起始柱(C)相同" << endl;
			continue;
		}
		else
			continue;
	}
	if (t1 == 65 || t1 == 97)
		*src = 'A';
	else if (t1 == 66 || t1 == 98)
		*src = 'B';
	else
		*src = 'C';
	if (t2 == 65 || t2 == 97)
		*dst = 'A';
	else if (t2 == 66 || t2 == 98)
		*dst = 'B';
	else
		*dst = 'C';
	if (*src != 'A' && *dst != 'A')
		*tmp = 'A';
	if (*src != 'B' && *dst != 'B')
		*tmp = 'B';
	if (*src != 'C' && *dst != 'C')
		*tmp = 'C';
	if (sol == 3 || sol == 4 || sol == 7 || sol == 8 || sol == 9) {
		for (num = 0; num < *n; num++) {
			if (*src == 'A')
				tower[0][num] = *n - num;
			if (*src == 'B')
				tower[1][num] = *n - num;
			if (*src == 'C')
				tower[2][num] = *n - num;
		}
		if (*src == 'A')
			top[0] = *n;
		if (*src == 'B')
			top[1] = *n;
		if (*src == 'C')
			top[2] = *n;
		if (sol == 4 || sol == 8) {
			cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
			int t1;
			cin >> t1;
			*t = t1;
			if (sol == 4) {
				cout << "请输入是否显示内部数组值(0-不显示 1-显示)" << endl;
				int xianshi1;
				cin >> xianshi1;
				*xianshi = xianshi1;
			}
		}
	}
}
void hua_ta() {
	cct_setcursor(CURSOR_INVISIBLE);
	cct_showch(base_x, base_y, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
	cct_showch(base_x + 30, base_y, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
	cct_showch(base_x + 60, base_y, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
	int i = 1;
	for (i = 1; i <= 13; i++) {
		cct_showch(base_x + 11, base_y - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		Sleep(100);
		cct_showch(base_x + 30 + 11, base_y - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		Sleep(100);
		cct_showch(base_x + 60 + 11, base_y - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		Sleep(100);
	}
	cct_setcolor();
}
void hua_pan(char src, int n) {
	int i;
	for (i = 1; i <= n; i++) {
		cct_showch(base_x + (src - 'A') * 30 + (10 - n + i), base_y - i, ' ', n - i + 1, n - i + 1, 2 * (n - i + 1) + 1);
		Sleep(100);
	}
	cct_setcolor();
}
void pan_move(char src, char dst, int n, int t) {

	int y;
	/*上*/
	for (y = base_y - top[0 + src - 'A'] - 1; y >= MIN_Y; y--) {

		cct_showstr(base_x + 1 + (10 - n) + (src - 'A') * 30, y, " ", n, n, 2 * n + 1);
		Sleep(170 - t * 30);


		if (y > MIN_Y) {

			cct_showch(base_x + 1 + (10 - n) + (src - 'A') * 30, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
			if (y > MIN_Y - 1) {
				cct_showch(base_x + 11 + (src - 'A') * 30, y, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
			}
		}
	}
	/*左*/
	if (src > dst) {
		int x;
		for (x = 0; x < (src - dst) * 30; x++) {
			cct_showstr(base_x + 1 + (10 - n) + (src - 'A') * 30 - x, MIN_Y, " ", n, n, 2 * n + 1);

			Sleep(170 - t * 30);


			if (x < (src - dst) * 30) {

				cct_showch(base_x + 1 + (10 - n) + (src - 'A') * 30 - x, MIN_Y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			}
		}
	}

	/*右*/
	if (src < dst) {
		int x;
		for (x = 0; x < (dst - src) * 30; x++) {
			cct_showstr(base_x + 1 + (10 - n) + (src - 'A') * 30 + x, MIN_Y, " ", n, n, 2 * n + 1);

			Sleep(170 - t * 30);


			if (x < (dst - src) * 30) {

				cct_showch(base_x + 1 + (10 - n) + (src - 'A') * 30 + x, MIN_Y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
			}
		}
	}
	/*下*/
	for (y = MIN_Y; y <= base_y - top[0 + dst - 'A']; y++) {

		cct_showstr(base_x + 1 + (10 - n) + (dst - 'A') * 30, y, " ", n, n, 2 * n + 1);


		Sleep(170 - t * 30);

		if (y < base_y - top[0 + dst - 'A']) {

			cct_showch(base_x + 1 + (10 - n) + (dst - 'A') * 30, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
			if (y != MIN_Y)
				cct_showch(base_x + 11 + (dst - 'A') * 30, y, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);

		}
	}
}
void pan__move(char tower1, char tower2) {
	chu_ru_(tower1, tower2);
	move(tower1, tower2, base_Ax, 1);
	heng_xiang_dayin(1, (n_zhi(tower1)), tower1, tower2, 1);
	pan_move(tower1, tower2, (n_zhi(tower1)), 1);
	cct_setcolor();
}

void solution1() {
	int n;
	char src, tmp, dst;
	int t = 0;
	int xianshi = 0;
	chu_shi_hua(&n, &src, &tmp, &dst, 1, &xianshi, &t);
	cout << "移动步骤为:" << endl;
	hanoi(n, src, tmp, dst, 1, 0, 0);
	cout << endl;
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void solution2() {
	int n;
	char src, tmp, dst;
	int t = 0;
	int xianshi = 0;
	chu_shi_hua(&n, &src, &tmp, &dst, 2, &xianshi, &t);
	hanoi(n, src, tmp, dst, 2, 0, 0);
	cout << endl;
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void solution3() {
	int n;
	char src, tmp, dst;
	int t = 0;
	int xianshi = 0;
	chu_shi_hua(&n, &src, &tmp, &dst, 3, &xianshi, &t);
	cout << "初始:               ";
	int i;
	cout << " A:";
	for (i = 0; i < top[0]; i++) {
		cout << setw(2) << tower[0][i];
	}
	for (i = 9; i >= top[0]; i--) {
		cout << "  ";
	}
	cout << " B:";
	for (i = 0; i < top[1]; i++) {
		cout << setw(2) << tower[1][i];
	}
	for (i = 9; i >= top[1]; i--) {
		cout << "  ";
	}
	cout << " C:";
	for (i = 0; i < top[2]; i++) {
		cout << setw(2) << tower[2][i];
	}
	for (i = 9; i >= top[2]; i--) {
		cout << "  ";
	}
	cout << endl;
	num = 0;
	hanoi(n, src, tmp, dst, 3, 0, 0);
	cout << endl;
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();

}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void solution4() {
	int n;
	char src, tmp, dst;
	int t = 0;
	int xianshi = 0;
	chu_shi_hua(&n, &src, &tmp, &dst, 4, &xianshi, &t);
	cct_cls();
	num = 0;
	zong_xiang_dayin(base_Ax, base_Ay, tower, top[0], 0);
	zong_xiang_dayin(base_Ax + 10, base_Ay, tower, top[1], 1);
	zong_xiang_dayin(base_Ax + 20, base_Ay, tower, top[2], 2);
	cct_gotoxy(base_Ax - 5, base_Ay + 1);
	cout << "====================================" << endl;
	cout << "           A         B         C" << endl;
	/*打印所有的盘*/
	cct_gotoxy(0, 0);
	cout << "从 " << src << " 移动到 " << dst << "，" << "共 " << n << " 层，延时设置为 " << t << "，";
	if (xianshi == 0)
		cout << "不";
	cout << "显示内部数组值" << endl;
	while (1) {
		if (getchar() == '\n')
			break;
	}
	hanoi(n, src, tmp, dst, 4, xianshi, t);
	cct_gotoxy(0, 28);
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void solution5() {
	cct_cls();
	hua_ta();

	cct_gotoxy(0, 28);
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void solution6() {
	int n;
	char src, tmp, dst;
	int t = 0;
	int xianshi = 0;
	chu_shi_hua(&n, &src, &tmp, &dst, 6, &xianshi, &t);
	cct_cls();
	cout << "从 " << src << " 移动到 " << dst << "，" << "共 " << n << " 层 " << endl;
	hua_ta();
	hua_pan(src, n);
	cct_gotoxy(0, 28);
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void solution7() {
	int n;
	char src, tmp, dst;
	int t = 0;
	int xianshi = 0;
	chu_shi_hua(&n, &src, &tmp, &dst, 7, &xianshi, &t);
	num = 0;
	cct_cls();
	cout << "从 " << src << " 移动到 " << dst << "，" << "共 " << n << " 层 " << endl;
	hua_ta();
	hua_pan(src, n);

	if (n % 2) {
		chu_ru_(src, dst);
		pan_move(src, dst, 1, 1);
	}
	if (n % 2 - 1) {
		chu_ru_(src, tmp);;
		pan_move(src, tmp, 1, 1);
	}
	cct_setcolor();
	cct_gotoxy(0, 28);
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void solution8() {
	int n;
	char src, tmp, dst;
	int t = 0;
	int xianshi = 0;
	chu_shi_hua(&n, &src, &tmp, &dst, 8, &xianshi, &t);
	cct_cls();
	num = 0;
	cct_cls();
	zong_xiang_dayin(base_Ax, base_Ay + 10, tower, top[0], 0);
	zong_xiang_dayin(base_Ax + 10, base_Ay + 10, tower, top[1], 1);
	zong_xiang_dayin(base_Ax + 20, base_Ay + 10, tower, top[2], 2);
	cct_gotoxy(base_Ax - 5, base_Ay + 11);
	cout << "====================================" << endl;
	cout << "           A         B         C" << endl;
	/*打印所有的盘*/
	cct_gotoxy(0, 0);
	cout << "从 " << src << " 移动到 " << dst << "，" << "共 " << n << " 层，延时设置为 " << t << endl;
	hua_ta();
	hua_pan(src, n);
	Sleep(500);
	while (1) {
		if (getchar() == '\n')
			break;
	}
	hanoi(n, src, tmp, dst, 8, 0, t);
	cct_gotoxy(0, 38);
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void solution9() {
	int n;
	char src, tmp, dst;
	int t = 0;
	int xianshi = 0;
	chu_shi_hua(&n, &src, &tmp, &dst, 9, &xianshi, &t);
	cct_cls();
	num = 0;
	zong_xiang_dayin(base_Ax, base_Ay + 10, tower, top[0], 0);
	zong_xiang_dayin(base_Ax + 10, base_Ay + 10, tower, top[1], 1);
	zong_xiang_dayin(base_Ax + 20, base_Ay + 10, tower, top[2], 2);
	cct_gotoxy(base_Ax - 5, base_Ay + 11);
	cout << "====================================" << endl;
	cout << "           A         B         C" << endl;
	/*打印所有的盘*/
	cct_gotoxy(0, 0);
	cout << "从 " << src << " 移动到 " << dst << "，" << "共 " << n << " 层" << endl;
	hua_ta();
	hua_pan(src, n);
	cct_gotoxy(0, 35);
	cout << "初始:               ";
	int i;
	cout << " A:";
	for (i = 0; i < top[0]; i++) {
		cout << setw(2) << tower[0][i];
	}
	for (i = 9; i >= top[0]; i--) {
		cout << "  ";
	}
	cout << " B:";
	for (i = 0; i < top[1]; i++) {
		cout << setw(2) << tower[1][i];
	}
	for (i = 9; i >= top[1]; i--) {
		cout << "  ";
	}
	cout << " C:";
	for (i = 0; i < top[2]; i++) {
		cout << setw(2) << tower[2][i];
	}
	for (i = 9; i >= top[2]; i--) {
		cout << "  ";
	}
	cout << endl;
	cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
	
	while (1) {
		char tower1, tower2;
		while (1) {
			cct_gotoxy(60, 36);
			cout << "    ";
			cct_gotoxy(60, 36);
			cin >> tower1;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000000, '\n');
				continue;
			}
			if (tower1 == 'q' || tower1 == 'Q')
				break;
			cin>> tower2;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000000, '\n');
				continue;
			}
			if (tower1 == tower2) {
				cin.ignore(10000000, '\n');
				continue;
			}
			if (tower1 == 'A' || tower1 == 'B' || tower1 == 'C' || tower1 == 'a' || tower1 == 'b' || tower1 == 'c') {
				if (tower2 == 'A' || tower2 == 'B' || tower2 == 'C' || tower2 == 'a' || tower2 == 'b' || tower2 == 'c') {
					if (tower1 > 'C')
						tower1 -= 32;
					if (tower2 > 'C')
						tower2 -= 32;
					if (tower1 == tower2) {
						cin.ignore(10000000, '\n');
						continue;
					}
					if ((getchar()) == '\n') {
						if ((top[tower1 - 'A'] == 0)) {
							cout << "源柱为空！！！" << endl;
							Sleep(500);
							cct_gotoxy(0, 37);
							cout << "                       ";
							continue;
						}
						if ((tower[tower1 - 'A'][top[tower1 - 'A']+1] > tower[tower2 - 'A'][top[tower2 - 'A']+1])) {
							cout << "大盘压小盘，非法移动" << endl;
							Sleep(500);
							cct_gotoxy(0, 37);
							cout << "                       ";
							continue;
						}
						break;
					}
				}
			}
			
			cin.ignore(10000000, '\n');
		}/*输入命令*/
		if (tower1 == 'q' || tower1 == 'Q') {
			cout << "游戏结束!!!" << endl;
			break;
		}
			
		pan__move(tower1, tower2);
		if (top[dst - 'A'] == n) {
			cct_gotoxy(0, 37);
			cout << "游戏结束!!!" << endl;
			break;
		}
	}
	cct_gotoxy(0, 38);
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;

	cct_cls();
}