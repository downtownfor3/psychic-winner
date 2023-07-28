#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include<iostream>
#include"file_compression.h"
#include <chrono>//������ʱ
#include <iomanip>
using namespace std;
int main(int argc, char** argv) {
	if (argc != 4) {
		cout << "�����ָ��" << endl;
		return 0;
	}
	if (!(strcmp(argv[3],"zip"))) {
		//ѹ��
		auto start = std::chrono::high_resolution_clock::now();
		ifstream in;
		ofstream out;
		struct huffman* tree = new struct huffman[256];
		huffman* root = t_createnode();
		in.open(argv[1], ios::binary);
		in.seekg(0, ios::end);
		int fileSize1 = in.tellg();
		in.seekg(0, std::ios::beg);
		build_tree(in, tree, root, 0);
		in.close();
		in.open(argv[1], ios::binary);
		cout << argv[2];
		out.open(argv[2], ios::binary);
		huff_coding(in, out, tree);
		in.close();
		out.close();
		//�ͷŶ�̬�ڴ�
		free_leaf_left(tree);
		free_tree(root);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "����ʱ�� " << elapsed_time.count() << " ms\n";
		in.open(argv[2], ios::binary);
		in.seekg(0, ios::end);
		int fileSize2 = in.tellg();
		in.close();
		cout << "ѹ����Ϊ" << fixed << setprecision(2) << (fileSize2 + 0.0) / (fileSize1 + 0.0) * 100.0 << "%" << endl;
	}
	if (!(strcmp(argv[3], "unzip"))) {
		//��ѹ*/
		auto start = std::chrono::high_resolution_clock::now();
		ifstream in;
		ofstream out;
		struct huffman* tree = new struct huffman[256];
		huffman* root = t_createnode();
		in.open(argv[1], ios::binary);
		out.open(argv[2], ios::binary);
		build_tree(in, tree, root, 1);
		un_coding(in, out, root);
		in.close();
		out.close();
		cout << "��ѹ����" << endl;
		//�ͷŶ�̬�ڴ�
		free_leaf_left(tree);
		free_tree(root);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "����ʱ�� " << elapsed_time.count() << " ms\n";
	}
	return 0;
}