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
	cout << "*" << "      " << "1.����ӷ�" << "      " << "2.��������" << "      " << "3.����ת��" << "      " << "*" << endl;
	cout << "*" << "      " << "4.����˷�" << "      " << "5.Hardmard�˻�" << "  " << "6.������" << "      " << "*" << endl;
	cout << "*" << "      " << "7.���Ӧ��" << "      " << "8.OTSU �㷨" << "     " << "0.�˳�ϵͳ" << "      " << "*" << endl;
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
			cout << "�������" << endl;
			while (getchar() != '\n');
			wait_for_enter();
			system("cls");
		}
		*p = s;
		break;
		
	}
}