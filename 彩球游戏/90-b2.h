/* 2252075 ÁõÎÄ·É ¹ú06 */
#pragma once


void solution1();
void solution2();
void solution3();
void solution4();
void solution5();
void solution6();
void solution7();
void row_column(int* p1, int* p2);
void whole_shuzu_print_1(int(*p)[9], int row, int column);
void whole_shuzu_print_2(int(*p)[9], int(*path)[2], int judge, int row, int column, int solution);
void generate_balls(int(*p)[9], int row, int column, int solution);
void generate_balls_3(int *next_balls);
void put_in_nextballs(int(*p)[9], int* next_balls, int column, int row);
int search(int(*p)[9], int row, int column, int x0, int y0, int x1, int y1, int(*path)[2], int* judge);
void coordinate(int(*p)[9], int row, int column, int* x0, int* y0, int* x1, int* y1);
void score(int(*p)[9], int x1, int y1, int row, int column, int* sum_score, int* once_score);
void end();
void read_mouse(int(*p)[9], int& x0, int& y0, int& x1, int& y1, int row, int col, int y_m);
int game_over(int(*p)[9], int row, int column,int y_m);
void qipan_1(int(*p)[9], int row, int col);
void qipan_2(int(*p)[9], int row, int col);
void moving_steps(int(*path)[2], int begin_value, int judge);
void right_(int row, int col, int sum_score, int(*p)[9], int* balls);