
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
};/*创立一个结构体用来作为huffman树的节点，分别存储字符极其出现频率，对应的编码以及左右孩子，以及是否是叶子节点*/
void build_tree(ifstream& in, huffman* tree, huffman* root,int i);
void huff_coding(ifstream& in, ofstream& out, huffman* tree);
void un_coding(ifstream& in, ofstream& out, huffman* root);
void  free_tree(huffman* hf);
void free_leaf_left(huffman* hf);
struct huffman* t_createnode();
