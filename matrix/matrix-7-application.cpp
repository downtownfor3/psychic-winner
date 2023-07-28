#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void convolve_(int** input, int** output, int** kernel, int rows, int cols, int kernel_size = 3, int padding = 1, int stride = 1) {
	int output_rows = (rows - kernel_size + 2 * padding) / stride + 1;
	int output_cols = (cols - kernel_size + 2 * padding) / stride + 1;
	int kernel_sum = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			kernel_sum += kernel[i][j];
		}
	}
	if (kernel_sum == 0)
		kernel_sum = 1;

	int** padded_input = new int* [rows + 2 * padding]();
	for (int i = 0; i < rows + 2 * padding; i++) {
		padded_input[i] = new int[cols + 2 * padding]();
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			padded_input[i + padding][j + padding] = input[i][j];
		}
	}


	for (int i = 0; i < output_rows; i++) {
		for (int j = 0; j < output_cols; j++) {
			int sum = 0;
			for (int m = 0; m < kernel_size; m++) {
				for (int n = 0; n < kernel_size; n++) {
					sum += padded_input[i * stride + m][j * stride + n] * kernel[m][n];
				}
			}
			output[i][j] = sum / kernel_sum;
		}
	}

	for (int i = 0; i < rows + 2 * padding; i++) {
		delete[] padded_input[i];
	}
	delete[] padded_input;
}

void application(Mat& ima, int i) {
	const int kernel_size = 3;
	const int padding = 1;
	const int stride = 1;
	int kernel_1[3][3] = { 1,1,1,1,1,1,1,1,1 };
	int kernel_2[3][3] = { -1,-2,-1,0,0,0,1,2,1 };
	int kernel_3[3][3] = { -1,0,1,-2,0,2,-1,0,1 };
	int kernel_4[3][3] = { -1 ,-1 ,-1,-1 ,9,-1,-1,-1,-1 };
	int kernel_5[3][3] = { -1,-1,0,-1,0,1,0,1,1 };
	int kernel_6[3][3] = { 1,2,1,2,4,2,1,2,1 };
	int rows = ima.rows;
	int cols = ima.cols;

	int** input = new int* [rows]();
	for (int i = 0; i < rows; i++) {
		input[i] = new int[cols]();
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			input[i][j] = ima.at<Vec3b>(i, j)[0];/*灰度图只需要读一个通道即可*/
		}
	}

	int** kernel = new int* [kernel_size]();
	for (int i = 0; i < kernel_size; i++) {
		kernel[i] = new int[kernel_size]();
	}

	if (i == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				kernel[i][j] = kernel_1[i][j];
			}
		}
	}
	else if (i == 2) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				kernel[i][j] = kernel_2[i][j];
			}
		}
	}
	else if (i == 3) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				kernel[i][j] = kernel_3[i][j];
			}
		}
	}
	else if (i == 4) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				kernel[i][j] = kernel_4[i][j];
			}
		}
	}
	else if (i == 5) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				kernel[i][j] = kernel_5[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				kernel[i][j] = kernel_6[i][j];
			}
		} 

	}


	int output_rows = rows;
	int output_cols = cols;

	int** output = new int* [output_rows]();
	for (int i = 0; i < output_rows; i++) {
		output[i] = new int[output_cols]();
	}

	convolve_(input, output, kernel, rows, cols);

	for (int i = 0; i < output_rows; i++) {
		for (int j = 0; j < output_cols; j++) {
			if (output[i][j] > 255)
				output[i][j] = 255;
			if (output[i][j] < 0)
				output[i][j] = 0;
			ima.at<Vec3b>(i, j)[0] = output[i][j];
			ima.at<Vec3b>(i, j)[1] = output[i][j];
			ima.at<Vec3b>(i, j)[2] = output[i][j];
		}
	}

	for (int i = 0; i < rows; i++) {
		delete[] input[i];
	}
	delete[] input;

	for (int i = 0; i < kernel_size; i++) {
		delete[] kernel[i];
	}
	delete[] kernel;

	for (int i = 0; i < output_rows; i++) {
		delete[] output[i];
	}
	delete[] output;
}