/* 2252075 刘文飞 国06 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include <string.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "90-b2.h"
#include<conio.h>
using namespace std;




char caidan() {
	cout << "--------------------------------------------" << endl;
	cout << "1.内部数组，随机生成初始5个球" << endl;
	cout << "2.内部数组，随机生成60%的球，寻找移动路径" << endl;
	cout << "3.内部数组，完整版" << endl;
	cout << "4.画出n*n的框架（无分隔线），随机显示5个球" << endl;
	cout << "5.画出n*n的框架（有分隔线），随机显示5个球" << endl;
	cout << "6.n*n的框架，60%的球，支持鼠标，完成一次移动" << endl;
	cout << "7.cmd图形界面完整版" << endl;
	cout << "0.退出" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[请选择:]" << ' ';
	char num;
	while (1) {
		num = _getche();
		if (num >= '0' && num <= '7') {
			cout << endl;
			break;
		}
	}
	
	return num;
}
int main()
{
	while (1) {
		switch ((caidan())) {
		case '1':
			solution1();
			break;
		case '2':
			solution2();
			break;
		case '3':
			solution3();
			break;
		case '4':
			solution4();
			break;
		case '5':
			solution5();
			break;
		case '6':
			solution6();
			break;
		case '7':
			solution7();
			break;
		case'0':
			return 0;
		}
	}



	return 0;
}