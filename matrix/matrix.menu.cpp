#include <conio.h>
#include <iostream>
// #include <opencv2/opencv.hpp>
// using namespace cv;
using namespace std;

void wait_for_enter();

void print_menu() {
	int i = 0;
	while (i < 56) {
		cout << "*";
		i++;
	}
	cout << endl;
	cout << "*" << "      " << "1.矩阵加法" << "      " << "2.矩阵数乘" << "      " << "3.矩阵转置" << "      " << "*" << endl;
	cout << "*" << "      " << "4.矩阵乘法" << "      " << "5.Hardmard乘积" << "  " << "6.矩阵卷积" << "      " << "*" << endl;
	cout << "*" << "      " << "7.卷积应用" << "      " << "8.OTSU 算法" << "     " << "0.退出系统" << "      " << "*" << endl;
	i = 0;
	while (i < 56) {
		cout << "*";
		i++;
	}
}
void menu(char* p) {
	while (1) {
		print_menu();
		int num = 0;
		char s = _getch();
		if (!(s >= '0' && s <= '8')) {
			cout << "输入错误" << endl;
			while (getchar() != '\n');
			wait_for_enter();
			system("cls");
		}
		*p = s;
		break;
		
	}
}