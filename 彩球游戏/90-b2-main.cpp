/* 2252075 ���ķ� ��06 */
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
	cout << "1.�ڲ����飬������ɳ�ʼ5����" << endl;
	cout << "2.�ڲ����飬�������60%����Ѱ���ƶ�·��" << endl;
	cout << "3.�ڲ����飬������" << endl;
	cout << "4.����n*n�Ŀ�ܣ��޷ָ��ߣ��������ʾ5����" << endl;
	cout << "5.����n*n�Ŀ�ܣ��зָ��ߣ��������ʾ5����" << endl;
	cout << "6.n*n�Ŀ�ܣ�60%����֧����꣬���һ���ƶ�" << endl;
	cout << "7.cmdͼ�ν���������" << endl;
	cout << "0.�˳�" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[��ѡ��:]" << ' ';
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