
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include<iostream>
using namespace std;

struct huffman {
	char ch = '\0';
	int frq=0;
	char hcode[80] = { 0 };
	bool is_leave = 1;
	huffman* left = NULL;
	huffman* right = NULL;
};/*����һ���ṹ��������Ϊhuffman���Ľڵ㣬�ֱ�洢�ַ��������Ƶ�ʣ���Ӧ�ı����Լ����Һ��ӣ��Լ��Ƿ���Ҷ�ӽڵ�*/
void build_tree(ifstream& in, huffman* tree, huffman* root,int i);
void huff_coding(ifstream& in, ofstream& out, huffman* tree);
void un_coding(ifstream& in, ofstream& out, huffman* root);
void  free_tree(huffman* hf);
void free_leaf_left(huffman* hf);
struct huffman* t_createnode();
