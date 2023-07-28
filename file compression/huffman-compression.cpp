#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include<iostream>
#include"file_compression.h"
using namespace std;
struct line {
	huffman* hf;
	line* next;
};/*创立一个列来作为优先级队列，根据huffman的frq来排序，从小到大*/
//建树函数
void sort(struct line* head) {
	struct line* t1 = NULL;
	struct line* t2 = NULL;
	huffman* mid1;
	t1 = head;
	while (t1->next != NULL) {
		t2 = t1->next;

		if ((t1->hf->frq) > (t2->hf->frq)) {
			mid1 = t1->hf;
			t1->hf = t2->hf;
			t2->hf = mid1;
		}
		t1 = t2;
	}
}
struct line* l_createnode() {
	struct  line* pnode = new(nothrow) line;
	if (pnode != NULL)
	{
		pnode->next = NULL;
	}
	return pnode;
}
struct huffman* t_createnode() {
	struct  huffman* pnode = new(nothrow) huffman;
	if (pnode != NULL)
	{
		pnode->left = NULL;
		pnode->right = NULL;
		pnode->is_leave = 0;
	}
	return pnode;
}
/*压缩统计*/
void count(ifstream& in, huffman* t) {
	char buffer[1024];
	while (in && !in.eof()) {
		in.read(buffer, 1024);
		int readnum = int(in.gcount());
		for (int i = 0; i < readnum; i++) {
			t[buffer[i] + 128].frq++;
			t[buffer[i] + 128].ch = buffer[i];
			t[buffer[i] + 128].left = NULL;
			t[buffer[i] + 128].right = NULL;
		}/*统计了所有字符出现的次数*/
	}
}
/*解压统计*/
void gethuff(ifstream& in, huffman* t) {
	for (int i = -128; i <= 127; i++) {
		t[i + 128].ch = char(i);
		t[i + 128].left = NULL;
		t[i + 128].right = NULL;
		in >> t[i + 128].frq;
	}
}
void h_code(huffman* hf) {
	if (hf->left != NULL) {
		char left[] = "0";
		char right[] = "1";
		strcat(hf->left->hcode, hf->hcode);
		strcat(hf->right->hcode, hf->hcode);
		strcat(hf->left->hcode, left);
		strcat(hf->right->hcode, right);
		h_code(hf->left);
		h_code(hf->right);
	}
}//该递归函数作用是将最初的256个中非零频率的字符进行编码,在最底层获得其字符对应编码
void build_tree(ifstream& in, huffman* tree, huffman* root, int i) {
	if (i == 0)
		count(in, tree);
	if (i == 1)
		gethuff(in, tree);
	struct line* l_head = NULL;
	struct line* t1 = NULL;
	struct line* t2 = NULL;
	l_head = l_createnode();
	l_head->hf = NULL;
	l_head->next = NULL;
	t1 = l_head;
	for (int i = 0; i < 256; i++)
	{
		if (tree[i].frq == 0)
			continue;
		if ((tree[i].frq != 0) && (l_head->hf == NULL)) {
			l_head->hf = &tree[i];
			continue;
		}
		t2 = l_createnode();
		t2->hf = &tree[i];
		t1->next = t2;
		t1 = t2;
	}/*循环结束，各种频率非0字符节点地址已经放入队列中*/
//先排序（根据fre）从小到大
	sort(l_head);
	//下面构建树
	while (!(l_head->next->next == NULL)) {
		//生成一个新的huffman节点用于合并前两项,并将其地址添加到优先列中
		struct huffman* t1 = NULL;
		struct line* t2 = NULL;
		t1 = t_createnode();
		t1->ch = '\0';
		t1->frq = l_head->hf->frq + l_head->next->hf->frq;
		t1->left = l_head->hf;
		t1->right = l_head->next->hf;
		t2 = l_head->next->next;
		delete l_head->next;
		l_head->next = t2;
		l_head->hf = t1;
		sort(l_head);
	}
	//循环结束后，优先列中还剩两个节点
	root->ch = '\0';
	root->frq = l_head->hf->frq + l_head->next->hf->frq;
	root->left = l_head->hf;
	root->right = l_head->next->hf;
	delete l_head->next;
	delete l_head;//链表的动态内存同时也释放完毕
	//至此huffman树建立完毕
	h_code(root);
}
//文件编码(压缩）
char binaryTochar(char* str) {
	char result = 0;
	for (int i = 0; i < 8; i++) {
		if (str[i] == '1') {
			result |= 1 << (7 - i);
		}
	}
	return result;
}
void huff_coding(ifstream& in, ofstream& out, huffman* tree) {
	for (int i = 0; i < 256; i++) {
		out << tree[i].frq << ' ';
	}/*在文本开头写入huffmantree的信息*/
	char buffer1[1024];
	char buffer2[40] = {};
	while (in && !in.eof()) {
		in.read(buffer1, 1024);
		int num = int(in.gcount());
		for (int i = 0; i < num; i++) {
			strcat(buffer2, tree[buffer1[i] + 128].hcode);
			if (strlen(buffer2) >= 8) {
				out << binaryTochar(buffer2);/*按字节以char输出到文件里*/
				for (int j = 8; j < 30; j++) {
					buffer2[j - 8] = buffer2[j];
				}
			}
			if (in.eof() && i == num - 1) {
				int len = int(strlen(buffer2));
				if (strlen(buffer2) != 0) {
					for (int j = int(strlen(buffer2)); j < 8; j++) {
						buffer2[j] = '0';
					}
					out << binaryTochar(buffer2);/*按字节以char输出到文件里*/
				}
				out << len;
			}//最后一个字节可能不足8位，我们可以补齐8位并且将最后一个字节的有效位数输出到文件中，解码时进行相应处理
		}
	}
}
//解压
void charTobinary(char c, char* buffer) {
	for (int i = 7; i >= 0; i--) {
		buffer[7 - i] = (char)((c >> i) & 1) + 48; // 通过位运算输出二进制表示
	}
}
void un_coding(ifstream& in, ofstream& out, huffman* root) {
	struct huffman* tool = root;
	char buffer1[1024];
	char buffer2[8];
	int n = 0;
	in.seekg(0, std::ios::end);
	// 向前移动一个字符位置
	in.seekg(-1, std::ios::cur);
	// 读取最后一个字符
	char c = in.get();
	n = (c - 48);/*获取有效位数*/
	in.seekg(0, ios::beg); // 将指针移动到文件开头
	in.clear();
	for (int i = -128; i <= 127; i++) {
		int a;
		in >> a;
	}
	in.ignore();/*忽略掉空格*/
	while (in && !in.eof()) {
		in.read(buffer1, 1024);
		int readnum = int(in.gcount());
		//一种特殊情况：文件没有到结尾，恰好把有效位数独立在外，那么最后一个字符的解压会出现问题
		//加条件，判断文件指针是否到达了倒数第一个字符,peek一下
		for (int i = 0; i < readnum; i++) {
			if ((i == readnum - 2) && ((in.eof()) || (in.peek() == c))) {
				charTobinary(buffer1[i], buffer2);
				for (int k = 0; k < n; k++) {
					if (buffer2[k] == '0') {
						tool = tool->left;
						if (tool->left == NULL) {
							out << tool->ch;
							tool = root;
						}
						continue;
					}
					if (buffer2[k] == '1') {
						tool = tool->right;
						if (tool->left == NULL) {
							out << tool->ch;
							tool = root;
						}
						continue;
					}
				}
				break;//解压结束
			}
			charTobinary(buffer1[i], buffer2);
			for (int k = 0; k < 8; k++) {
				if (buffer2[k] == '0') {
					tool = tool->left;
					if (tool->left == NULL) {
						out << tool->ch;
						tool = root;
					}
					continue;
				}
				if (buffer2[k] == '1') {
					tool = tool->right;
					if (tool->left == NULL) {
						out << tool->ch;
						tool = root;
					}
					continue;
				}
			}
		}
	}
}
/*别忘了动态内存申请的释放*/
//申请的动态内存有，256个节点，huffman树的新节点，以及优先队列（单链表）
//链表的动态内存在使用时已经同步释放，只需关注huffman tree的节点释放
//先释放非叶子节点，再释放叶子
void  free_tree(huffman* hf) {
	if (hf->is_leave) {
		return;
	}//终止条件
	free_tree(hf->left); // 先释放左子树内存
	free_tree(hf->right); // 再释放右子树内存
	delete hf;  // 最后释放当前节点内存
}
void free_leaf_left(huffman* tree) {
	delete[]tree;
}
