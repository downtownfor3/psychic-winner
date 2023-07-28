#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <conio.h>
#include<iostream>
#include<string>
#include <graphics.h>
#include <stdlib.h>
#include <ctime>
using namespace std;
const int size_x = 1100;
const int size_y = 730;
const int height = 38;
const int width = 38;
const int game_x1 = 375;
const int game_x2 = 1095;
const int game_y1 = 5;
const int game_y2 = 725;
struct body {
	int x;
	int y;
	struct body* next;
	struct body* previous;
};
class Snake {
private:
	int lenth;
	int life;
	int score;
	char direction;
	struct body tail;
	struct body head;
public:
	Snake() {
		lenth = 2;
		life = 1;
		score = 0;
		direction = 'r';
		head.x = 17;
		head.y = 17;
		tail.x = 16;
		tail.y = 17;
		head.previous = NULL;
		head.next = &tail;
		tail.next = NULL;
		tail.previous = &head;
	}
	void renew() {
		lenth = 2;
		life--;
		direction = 'r';
		head.x = 17;
		head.y = 17;
		tail.x = 16;
		tail.y = 17;
		head.previous = NULL;
		head.next = &tail;
		tail.next = NULL;
		tail.previous = &head;
	}
	int getlife() {
		return life;
	}
	void setlife(int x) {
		life = x;
	}
	struct body* create_body(int a, int b) {
		struct body* p = new body;
		p->x = a;
		p->y = b;
		p->next = NULL;
		p->previous = NULL;
		return p;
	}
	void create(char map[][38]) {
		map[head.x][head.y] = 'h';
		map[tail.x][tail.y] = 't';
	}
	void move(char map[][38],int &judge) {
		//�ȶ���
		if (_kbhit()) {//����а������£���_kbhit()����������
			char ch = _getch();//ʹ��_getch()��ȡ���µļ�ֵ
			if (ch == -32) {
				char c = _getch();
				switch (c) {
				case 72:
					direction = 'u';
					break;
				case 75:
					direction = 'l';
					break;
				case 77:
					direction = 'r';
					break;
				case 80:
					direction = 'd';
				}
			}
			switch (ch) {
			case 119:
				direction = 'u';
				break;
			case 97:
				direction = 'l';
				break;
			case 100:
				direction = 'r';
				break;
			case 115:
				direction = 'd';
			}

		}
		//���ݷ����˶�����Ϊ�������
		if (direction == 'u') {
			//��������ֱ�����ʳ���ʳ�ײǽ
			if (map[head.x][head.y - 1] == '0') {
				map[tail.x][tail.y] = '0';
				struct body* t = &tail;
				while (t->previous != NULL) {
					t->x = t->previous->x;
					t->y = t->previous->y;
					t = t->previous;
				}/*���������������ͷ�ڵ㣬���������Լ��������*/
				map[head.x][head.y] = 's';
				head.y = head.y - 1;
				map[head.x][head.y] = 'h';
				map[tail.x][tail.y] = 't';
			}
			else if ((map[head.x][head.y - 1] == 'b') || (map[head.x][head.y - 1] == 'c') || (map[head.x][head.y - 1] == 'y')) {
				lenth++;
				if (map[head.x][head.y - 1] == 'b')
					score++;
				else if (map[head.x][head.y - 1] == 'c')
					score = score + 2;
				else if (map[head.x][head.y - 1] == 'y')
					score = score + 3;
				struct body* p = create_body(head.x, head.y);
				p->previous = &head;
				p->next = head.next;
				map[head.x][head.y] = 's';
				head.y = head.y - 1;
				map[head.x][head.y] = 'h';
				head.next->previous = p;
				head.next = p;

				//ÿ�γ�һ��ʳ���ͷ�������һ���ڵ㣬��ֻ��Ҫ����ͷ����һ���ڵ������
			}
			else if ((map[head.x][head.y - 1] == 'w') || (map[head.x][head.y - 1] == 't') || (map[head.x][head.y - 1] == 's')) {
				judge = 0;
			}
		}
		else if (direction == 'd') {
			if (map[head.x][head.y + 1] == '0') {
				map[tail.x][tail.y] = '0';
				struct body* t = &tail;
				while (t->previous != NULL) {
					t->x = t->previous->x;
					t->y = t->previous->y;
					t = t->previous;
				}/*���������������ͷ�ڵ㣬���������Լ��������*/
				map[head.x][head.y] = 's';
				head.y = head.y + 1;
				map[head.x][head.y] = 'h';
				map[tail.x][tail.y] = 't';
			}
			else if ((map[head.x][head.y + 1] == 'b') || (map[head.x][head.y + 1] == 'c') || (map[head.x][head.y + 1] == 'y')) {
				lenth++;
				if (map[head.x][head.y + 1] == 'b')
					score++;
				else if (map[head.x][head.y + 1] == 'c')
					score = score + 2;
				else if (map[head.x][head.y + 1] == 'y')
					score = score + 3;
				struct body* p = create_body(head.x, head.y);
				p->previous = &head;
				p->next = head.next;
				map[head.x][head.y] = 's';
				head.y = head.y + 1;
				map[head.x][head.y] = 'h';
				head.next->previous = p;
				head.next = p;
				//ÿ�γ�һ��ʳ���ͷ�������һ���ڵ㣬��ֻ��Ҫ����ͷ����һ���ڵ������
			}

			else if ((map[head.x][head.y + 1] == 'w') || (map[head.x][head.y + 1] == 't') || (map[head.x][head.y + 1] == 's')) {
				judge = 0;
			}
		}
		else if (direction == 'l') {
			if (map[head.x - 1][head.y] == '0') {
				map[tail.x][tail.y] = '0';
				struct body* t = &tail;
				while (t->previous != NULL) {
					t->x = t->previous->x;
					t->y = t->previous->y;
					t = t->previous;
				}/*���������������ͷ�ڵ㣬���������Լ��������*/
				map[head.x][head.y] = 's';
				head.x = head.x - 1;
				map[head.x][head.y] = 'h';
				map[tail.x][tail.y] = 't';
			}
			else if ((map[head.x - 1][head.y] == 'b') || (map[head.x - 1][head.y] == 'c') || (map[head.x - 1][head.y] == 'y')) {
				lenth++;
				if (map[head.x - 1][head.y] == 'b')
					score++;
				else if (map[head.x - 1][head.y] == 'c')
					score = score + 2;
				else if (map[head.x - 1][head.y] == 'y')
					score = score + 3;
				struct body* p = create_body(head.x, head.y);
				p->previous = &head;
				p->next = head.next;
				map[head.x][head.y] = 's';
				head.x = head.x - 1;
				map[head.x][head.y] = 'h';
				head.next->previous = p;
				head.next = p;


				//ÿ�γ�һ��ʳ���ͷ�������һ���ڵ㣬��ֻ��Ҫ����ͷ����һ���ڵ������
			}
			else if ((map[head.x - 1][head.y] == 'w') || (map[head.x - 1][head.y] == 't') || (map[head.x - 1][head.y] == 's')) {
				judge = 0;

			}
		}
		else if (direction == 'r') {
			if (map[head.x + 1][head.y] == '0') {
				map[tail.x][tail.y] = '0';
				struct body* t = &tail;
				while (t->previous != NULL) {
					t->x = t->previous->x;
					t->y = t->previous->y;
					t = t->previous;
				}/*���������������ͷ�ڵ㣬���������Լ��������*/
				map[head.x][head.y] = 's';
				head.x = head.x + 1;
				map[head.x][head.y] = 'h';
				map[tail.x][tail.y] = 't';

			}
			else if ((map[head.x + 1][head.y] == 'b') || (map[head.x + 1][head.y] == 'c') || (map[head.x + 1][head.y] == 'y')) {
				lenth++;
				if (map[head.x + 1][head.y] == 'b')
					score++;
				else if (map[head.x + 1][head.y] == 'c')
					score = score + 2;
				else if (map[head.x + 1][head.y] == 'y')
					score = score + 3;
				struct body* p = create_body(head.x, head.y);
				p->previous = &head;
				p->next = head.next;
				map[head.x][head.y] = 's';
				head.x = head.x + 1;
				map[head.x][head.y] = 'h';
				head.next->previous = p;
				head.next = p;


				//ÿ�γ�һ��ʳ���ͷ�������һ���ڵ㣬��ֻ��Ҫ����ͷ����һ���ڵ������
			}
			else if ((map[head.x + 1][head.y] == 'w') || (map[head.x + 1][head.y] == 't') || (map[head.x + 1][head.y] == 's')) {
				judge = 0;
			}
		}
	}
	void display() {
		setfillcolor(RGB(135, 206, 235));
		solidrectangle(220,85,360,435);
		setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
		settextstyle(35, 25, "����");//��������߶ȣ���ȣ�����
		settextcolor(RGB(255, 97, 0));
		char buf1[10];
		sprintf_s(buf1, "%d",lenth); // �� int ����ת��Ϊ�ַ���
		char buf2[10];
		sprintf_s(buf2, "%d", life); // �� int ����ת��Ϊ�ַ���
		char buf3[10];
		sprintf_s(buf3, "%d", score); // �� int ����ת��Ϊ�ַ���
		outtextxy(220, 225, buf2);
		outtextxy(220, 85, buf1);
		outtextxy(220, 155, buf3);
	}//�ߵ��ƶ�
};
class Wall {
private:
public:
	void create(char map[][38]) {
		for (int i = 0; i < 38; i++) {
			map[0][i] = 'w';
			map[37][i] = 'w';
			map[i][0] = 'w';
			map[i][37] = 'w';
		}
	}//����ǽ
	void renew(char map[][38]) {
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 38; j++) {
				if ((map[i][j] == 's') || (map[i][j] == 't') || (map[i][j] == 'h')) {
					map[i][j] = 'w';
				}
			}
		}
	}
};
class Food {
private:
	int amount ;
	char version[3];
public:
	Food() {
		amount = 15;
		version[0] = 'b';//����
		version[1] = 'c';//ֻ��
		version[2] = 'y';//������
	}
	void create(char map[][38]) {
		int count = 0;
		while (count < amount) {
			int a = rand();
			int b = rand();
			int c = rand();
			a = a % 38;
			b = b % 38;
			c = c % 3;
			if (map[a][b] == '0') {
				map[a][b] = version[c];
				count++;
			}
		}
	}
	void renew(char map[][38]) {
		int count = 0;
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 38; j++) {
				if ((map[i][j] == 'b') || (map[i][j] == 'c') || (map[i][j] == 'y'))
					count++;
			}
		}
		while (count < amount) {
			int a = rand();
			int b = rand();
			int c = rand();
			a = a % 38;
			b = b % 38;
			c = c % 3;
			if (map[a][b] == '0') {
				map[a][b] = version[c];
				count++;
			}
		}
	}//��Ϸ������ˢ��
	void renew_(char map[][38]) {
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 38; j++) {
				if ((map[i][j] == 's') || (map[i][j] == 't') || (map[i][j] == 'h')) {
					int c = rand();
					c = c % 3;
					map[i][j] = version[c];
				}
			}
		}
	}

};
class UI {
private:
	clock_t start, end;
	int version;
public:
	UI() {
		start = 0;
		end = 0;
		version = 0;
	}
	void start_() {
		start = clock();
	}
	void time_display() {
		end = clock();
		double duration;
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
		settextstyle(35, 25, "����");//��������߶ȣ���ȣ�����
		settextcolor(RGB(255, 97, 0));
		char buf1[10];
		sprintf_s(buf1, "%d", (int)duration); // �� int ����ת��Ϊ�ַ���
		strcat(buf1, "s");
		outtextxy(220, 295, buf1);
	}
	int get_version() {
		return version;
	}
	void menu1();
	void menu2();
	void main_page();
	//void display();
	//void renew();
};
class Control {
private:
	Snake snake;
	Food food;
	Wall wall;
	UI ui;
	char map[height][width];
	char map2[height][width];
public:
	Control() {
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 38; j++) {
				map[i][j] = '0';
			}
		}// ��ʼ����ͼ
		wall.create(map);
		snake.create(map);
		food.create(map);
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 38; j++) {
				map2[i][j] = '1';
			}
		}// ��ʼ����ͼ
	}
	void display() {
		snake.display();
		ui.time_display();
	}
	void over() {
		char arr1[] = "��Ϸ����";
		settextstyle(90, 45, "����");//��������߶ȣ���ȣ�����
		setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
		settextcolor(RED);//����
		outtextxy(350, 300, arr1);
		/*һЩ���ݵĴ���*/
	}//����
	void run() {
		ui.start_();
		int judge = 1;
		int version = ui.get_version();
		pointing();
		if (version == 1) {
			while (1) {
				Sleep(300);
				snake.move(map,judge);
				food.renew(map);
				pointing();
				display();
				if (judge == 0) {
					over();
					Sleep(2000);
					break;
				}
			}
		}
		else if (version == 2) {
			snake.setlife(5);
			while (1) {
				Sleep(300);
				snake.move(map, judge);
				food.renew(map);
				pointing();
				display();
				if (judge == 0) {
					wall.renew(map);
					snake.renew();
					judge = 1;
					if (snake.getlife()==0) {
						over();
						Sleep(2000);
						break;
					}
				}
			}
		}
		else if (version == 3) {
			snake.setlife(5);
			while (1) {
				Sleep(300);
				snake.move(map, judge);
				food.renew(map);
				pointing();
				display();
				if (judge == 0) {
					food.renew_(map);
					snake.renew();
					judge = 1;
					if (snake.getlife() == 0) {
						over();
						Sleep(2000);
						break;
					}
				}
			}
		}

	}
	void menu() {
		initgraph(size_x, size_y);
		ui.menu1();
	}
	void pointing() {
		IMAGE img1;
		IMAGE img2;
		IMAGE img3;
		IMAGE img4;
		loadimage(&img1, "��ͨ����.jpg", 20, 20);//���·��
		loadimage(&img4, "����.png", 20, 20);//���·��
		loadimage(&img2, "ֻ��.jpg", 20, 20);//���·��
		loadimage(&img3, "������.jpg", 20, 20);//���·��
		for (int i = 1; i < 37;i++) {
			for (int j = 1; j < 37; j++) {
				if (map[i][j] != map2[i][j]) {
					if (map[i][j] == 'w') {
						setfillcolor(BLUE);
						solidrectangle(game_x1 + (i - 1) * 20, game_y1 + (j - 1) * 20, game_x1 + (i - 1) * 20 + 20, game_y1 + (j - 1) * 20 + 20);
					}
					else if (map[i][j] == 'b') {
						putimage(game_x1 + (i - 1) * 20, game_y1 + (j - 1) * 20, &img1);
					}
					else if (map[i][j] == 'c') {
						putimage(game_x1 + (i - 1) * 20, game_y1 + (j - 1) * 20, &img2);
					}
					else if (map[i][j] == 'y') {
						putimage(game_x1 + (i - 1) * 20, game_y1 + (j - 1) * 20, &img3);
					}
					else if (map[i][j] == 't') {
						setfillcolor(GREEN);
						solidrectangle(game_x1 + (i - 1) * 20, game_y1 + (j - 1) * 20, game_x1 + (i - 1) * 20 + 20, game_y1 + (j - 1) * 20 + 20);
					}
					else if (map[i][j] == 'h') {
						putimage(game_x1 + (i - 1) * 20, game_y1 + (j - 1) * 20, &img4);
					}
					else if (map[i][j] == 's') {
						setfillcolor(GREEN);
						solidrectangle(game_x1 + (i - 1) * 20, game_y1 + (j - 1) * 20, game_x1 + (i - 1) * 20 + 20, game_y1 + (j - 1) * 20 + 20);
					}
					else if (map[i][j] == '0') {
						setfillcolor(RGB(135, 206, 235));
						solidrectangle(game_x1 + (i - 1) * 20, game_y1 + (j - 1) * 20, game_x1 + (i - 1) * 20 + 20, game_y1 + (j - 1) * 20 + 20);
					}
					map2[i][j] = map[i][j];
				}
			}
		}
	}
};
void UI::menu1() {
	IMAGE img1;
	IMAGE img2;
	loadimage(&img1, "������.jpg", size_x, size_y);//���·��
	loadimage(&img2, "��ͨ.jpg", 300, 300);//���·��
	putimage(0, 0, &img1);
	putimage(750, 400, &img2);
	settextstyle(90, 45, "����");//��������߶ȣ���ȣ�����
	setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
	settextcolor(RED);//����
	//���־���
	char arr1[] = "ֻ  ��  ̰  ��  ��";
	char arr2[] = "��ʼ��Ϸ";
	char arr3[] = "��ʷ��¼";
	int x1 = (size_x - textwidth(arr1)) / 2;//textwidth���ַ�����ռ���س���
	int y1 = (size_y - textheight(arr1)) / 2;//textheight���ַ�����ռ���ظ߶�
	int x2 = (size_x - textwidth(arr2)) / 2;//textwidth���ַ�����ռ���س���
	int y2 = (size_y - textheight(arr2)) / 2;//textheight���ַ�����ռ���ظ߶�
	int x3 = (size_x - textwidth(arr3)) / 2;//textwidth���ַ�����ռ���س���
	int y3 = (size_y - textheight(arr3)) / 2;//textheight���ַ�����ռ���ظ߶�
	outtextxy(x1, y1 - 150, arr1);
	settextstyle(70, 35, "����");//��������߶ȣ���ȣ�����
	settextcolor(BROWN);//����
	outtextxy(x2, y2 + 100, arr2);
	outtextxy(x3, y3 + 250, arr3);
	MOUSEMSG m;
	int judge = 0;

	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if ((m.x > 370) && (m.x < 650) && (m.y > 435) && (m.y < 485)) {
				judge = 1;
				break;
			}
			else if ((m.x > 370) && (m.x < 650) && (m.y > 685) && (m.y < 735)) {
				judge = 2;
				break;
			}
		}
	}
	if (judge == 1) {
		menu2();
	}
	else if (judge == 2) {
		//menu3();
	}
}
void UI::menu2() {
	IMAGE img1;
	IMAGE img2;
	IMAGE img3;
	IMAGE img4;
	loadimage(&img1, "��.jpg", size_x, size_y);//���·��
	loadimage(&img2, "���С��.jpg", 200, 200);//���·��
	loadimage(&img3, "Ƥ����.jpg", 200, 200);//���·��
	loadimage(&img4, "�з�ͷ.jpg", 200, 200);//���·��
	putimage(0, 0, &img1);
	putimage(100, 50, &img2);
	putimage(100, 275, &img3);
	putimage(100, 500, &img4);
	settextstyle(90, 45, "����");//��������߶ȣ���ȣ�����
	setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
	settextcolor(RED);//����
	//���־���
	char arr1[] = "��  ��  ��";
	char arr2[] = "��  ��  ��";
	char arr3[] = "��  ��  ��";
	outtextxy(350, 100, arr1);
	outtextxy(350, 325, arr2);
	outtextxy(350, 550, arr3);

	MOUSEMSG m;

	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if ((m.x > 100) && (m.x < 820) && (m.y > 60) && (m.y < 260)) {
				version = 1;
				break;
			}
			else if ((m.x > 100) && (m.x < 820) && (m.y > 280) && (m.y < 480)) {
				version = 2;
				break;
			}
			else if ((m.x > 100) && (m.x < 820) && (m.y > 500) && (m.y < 700)) {
				version = 3;
				break;
			}
		}
	}
	main_page();
}
void UI::main_page() {
	setbkcolor(RGB(135, 206, 235));
	// �ñ���ɫ�����Ļ
	cleardevice();
	const int ui_x1 = 5;
	const int ui_x2 = 370;
	const int ui_y1 = 5;
	const int ui_y2 = 440;
	const int ui_y3 = 445;
	const int ui_y4 = 725;
	setfillcolor(BLUE);//���������ɫ-��ɫ
	solidrectangle(0, 0, size_x, game_y1);
	solidrectangle(0, game_y2, size_x, size_y);
	solidrectangle(0, 0, ui_x1, ui_y4);
	solidrectangle(ui_x2, ui_y1, game_x1, ui_y4);
	solidrectangle(game_x2, ui_y1, size_x, ui_y4);
	solidrectangle(ui_x1, ui_y2, ui_x2, ui_y3);
	char arr1[] = "���Ű�";
	char arr2[] = "���װ�";
	char arr3[] = "�߼���";
	char arr4[] = "����";
	char arr5[] = "�÷�";
	char arr6[] = "����";
	char arr7[] = "ʱ��";
	char arr8[] = "��߷�";
	char arr9[] = "ʳ��˵��";
	char arr10[] = "����       +1";
	char arr11[] = "ֻ��       +2";
	char arr12[] = "������     +3";
	setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
	settextstyle(55, 40, "����");//��������߶ȣ���ȣ�����
	settextcolor(RGB(255, 97, 0));
	if (version == 1) {
		outtextxy(20, 5, arr1);
	}
	else if (version == 2) {
		outtextxy(20, 5, arr2);
	}
	else if (version == 3) {
		outtextxy(20, 5, arr3);
	}
	settextstyle(35, 25, "����");//��������߶ȣ���ȣ�����
	outtextxy(20, 85, arr4);
	outtextxy(20, 155, arr5);
	outtextxy(20, 225, arr6);
	outtextxy(20, 295, arr7);
	outtextxy(20, 365, arr8);
	outtextxy(20, 460, arr9);
	outtextxy(20, 530, arr10);
	outtextxy(20, 600, arr11);
	outtextxy(20, 670, arr12);
	IMAGE img1;
	IMAGE img2;
	IMAGE img3;
	loadimage(&img1, "��ͨ����.jpg", 40, 40);//���·��
	loadimage(&img2, "ֻ��.jpg", 40, 40);//���·��
	loadimage(&img3, "������.jpg", 40, 40);//���·��
	putimage(220, 530, &img1);
	putimage(220, 600, &img2);
	putimage(220, 670, &img3);
}







