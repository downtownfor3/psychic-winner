#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include<iostream>
#include"file_compression.h"
using namespace std;
struct line {
	huffman* hf;
	line* next;
};/*����һ��������Ϊ���ȼ����У�����huffman��frq�����򣬴�С����*/
//��������
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
/*ѹ��ͳ��*/
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
		}/*ͳ���������ַ����ֵĴ���*/
	}
}
/*��ѹͳ��*/
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
}//�õݹ麯�������ǽ������256���з���Ƶ�ʵ��ַ����б���,����ײ������ַ���Ӧ����
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
	}/*ѭ������������Ƶ�ʷ�0�ַ��ڵ��ַ�Ѿ����������*/
//�����򣨸���fre����С����
	sort(l_head);
	//���湹����
	while (!(l_head->next->next == NULL)) {
		//����һ���µ�huffman�ڵ����ںϲ�ǰ����,�������ַ��ӵ���������
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
	//ѭ���������������л�ʣ�����ڵ�
	root->ch = '\0';
	root->frq = l_head->hf->frq + l_head->next->hf->frq;
	root->left = l_head->hf;
	root->right = l_head->next->hf;
	delete l_head->next;
	delete l_head;//����Ķ�̬�ڴ�ͬʱҲ�ͷ����
	//����huffman���������
	h_code(root);
}
//�ļ�����(ѹ����
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
	}/*���ı���ͷд��huffmantree����Ϣ*/
	char buffer1[1024];
	char buffer2[40] = {};
	while (in && !in.eof()) {
		in.read(buffer1, 1024);
		int num = int(in.gcount());
		for (int i = 0; i < num; i++) {
			strcat(buffer2, tree[buffer1[i] + 128].hcode);
			if (strlen(buffer2) >= 8) {
				out << binaryTochar(buffer2);/*���ֽ���char������ļ���*/
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
					out << binaryTochar(buffer2);/*���ֽ���char������ļ���*/
				}
				out << len;
			}//���һ���ֽڿ��ܲ���8λ�����ǿ��Բ���8λ���ҽ����һ���ֽڵ���Чλ��������ļ��У�����ʱ������Ӧ����
		}
	}
}
//��ѹ
void charTobinary(char c, char* buffer) {
	for (int i = 7; i >= 0; i--) {
		buffer[7 - i] = (char)((c >> i) & 1) + 48; // ͨ��λ������������Ʊ�ʾ
	}
}
void un_coding(ifstream& in, ofstream& out, huffman* root) {
	struct huffman* tool = root;
	char buffer1[1024];
	char buffer2[8];
	int n = 0;
	in.seekg(0, std::ios::end);
	// ��ǰ�ƶ�һ���ַ�λ��
	in.seekg(-1, std::ios::cur);
	// ��ȡ���һ���ַ�
	char c = in.get();
	n = (c - 48);/*��ȡ��Чλ��*/
	in.seekg(0, ios::beg); // ��ָ���ƶ����ļ���ͷ
	in.clear();
	for (int i = -128; i <= 127; i++) {
		int a;
		in >> a;
	}
	in.ignore();/*���Ե��ո�*/
	while (in && !in.eof()) {
		in.read(buffer1, 1024);
		int readnum = int(in.gcount());
		//һ������������ļ�û�е���β��ǡ�ð���Чλ���������⣬��ô���һ���ַ��Ľ�ѹ���������
		//���������ж��ļ�ָ���Ƿ񵽴��˵�����һ���ַ�,peekһ��
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
				break;//��ѹ����
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
/*�����˶�̬�ڴ�������ͷ�*/
//����Ķ�̬�ڴ��У�256���ڵ㣬huffman�����½ڵ㣬�Լ����ȶ��У�������
//����Ķ�̬�ڴ���ʹ��ʱ�Ѿ�ͬ���ͷţ�ֻ���עhuffman tree�Ľڵ��ͷ�
//���ͷŷ�Ҷ�ӽڵ㣬���ͷ�Ҷ��
void  free_tree(huffman* hf) {
	if (hf->is_leave) {
		return;
	}//��ֹ����
	free_tree(hf->left); // ���ͷ��������ڴ�
	free_tree(hf->right); // ���ͷ��������ڴ�
	delete hf;  // ����ͷŵ�ǰ�ڵ��ڴ�
}
void free_leaf_left(huffman* tree) {
	delete[]tree;
}
