#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include<iostream>
#include"file_compression.h"
#include <chrono>//用来计时
#include <iomanip>
using namespace std;
int main(int argc, char** argv) {
	if (argc != 4) {
		cout << "错误的指令" << endl;
		return 0;
	}
	if (!(strcmp(argv[3],"zip"))) {
		//压缩
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
		//释放动态内存
		free_leaf_left(tree);
		free_tree(root);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "运行时间 " << elapsed_time.count() << " ms\n";
		in.open(argv[2], ios::binary);
		in.seekg(0, ios::end);
		int fileSize2 = in.tellg();
		in.close();
		cout << "压缩比为" << fixed << setprecision(2) << (fileSize2 + 0.0) / (fileSize1 + 0.0) * 100.0 << "%" << endl;
	}
	if (!(strcmp(argv[3], "unzip"))) {
		//解压*/
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
		cout << "解压结束" << endl;
		//释放动态内存
		free_leaf_left(tree);
		free_tree(root);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "运行时间 " << elapsed_time.count() << " ms\n";
	}
	return 0;
}