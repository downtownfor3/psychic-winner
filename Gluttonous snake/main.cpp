#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include"snake.h"
using namespace std;


int main() {
	Control con;
	con.menu();
	con.run();
	return 0;
}