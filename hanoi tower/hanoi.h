/* 国06 2252075 刘文飞 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */

   /* hanoi_multiple_solutions.cpp下的函数声明 */
char caidan();
void solution1();
void solution2();
void solution3();
void solution4();
void solution5();
void solution6();
void solution7();
void solution8();
void solution9();

const int base_Ax = 10;/*纵向显示的参数*/
const int base_Ay = 20;
const int base_x = 1;/*盘的参数*/
const int base_y = 15;
const int MIN_Y = 1;