#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void OTSU(int**in,int**out,int rows,int cols) {
		
		int threshold;
		long sum0 = 0, sum1 = 0; //�洢ǰ���ĻҶ��ܺͺͱ����Ҷ��ܺ�
		long cnt0 = 0, cnt1 = 0; //ǰ�����ܸ����ͱ������ܸ���
		double w0 = 0, w1 = 0; //ǰ���ͱ�����ռ����ͼ��ı���
		double u0 = 0, u1 = 0;  //ǰ���ͱ�����ƽ���Ҷ�
		double variance = 0; //�����䷽��
		int i;
		double u = 0;
		double maxVariance = 0;
		for (i = 1; i < 256; i++) //һ�α���ÿ������
		{
			sum0 = 0;
			sum1 = 0;
			cnt0 = 0;
			cnt1 = 0;
			w0 = 0;
			w1 = 0;

			for (int m = 0; m < rows; m++) {
				for (int n = 0; n < cols; n++) {
					if (in[m][n] < i) {
						cnt0++;
						sum0 += in[m][n];
					}
				}
			}
			for (int m = 0; m < rows; m++) {
				for (int n = 0; n < cols; n++) {
					if (in[m][n] >= i) {
						cnt1++;
						sum1 += in[m][n];
					}
				}
			}
			 
			u0 = (double)sum0 / cnt0;
			w0 = (double)cnt0 /(rows*cols);


			u1 = (double)sum1 / cnt1;
			w1 = 1 - w0; // (double)cnt1 / size;

			u = u0 * w0 + u1 * w1; //ͼ���ƽ���Ҷ�
			//variance =  w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
			variance = w0 * w1 * (u0 - u1) * (u0 - u1);
			if (variance > maxVariance)
			{
				maxVariance = variance;
				threshold = i;
			}
		}
		for (int m = 0; m < rows; m++) {
			for (int n = 0; n < cols; n++) {
				if (in[m][n] > threshold) {
					out[m][n] = in[m][n];
				}
				else
					out[m][n] =0;
			}
		}
		
	}


void application_(Mat& ima) {
	
	int rows = ima.rows;
	int cols = ima.cols;

	int** input = new int* [rows]();
	for (int i = 0; i < rows; i++) {
		input[i] = new int[cols]();
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			input[i][j] = ima.at<Vec3b>(i, j)[0];/*�Ҷ�ͼֻ��Ҫ��һ��ͨ������*/
		}
	}

	


	int output_rows = rows;
	int output_cols = cols;

	int** output = new int* [output_rows]();
	for (int i = 0; i < output_rows; i++) {
		output[i] = new int[output_cols]();
	}

	OTSU(input, output, rows, cols);

	for (int i = 0; i < output_rows; i++) {
		for (int j = 0; j < output_cols; j++) {
			ima.at<Vec3b>(i, j)[0] = output[i][j];
			ima.at<Vec3b>(i, j)[1] = output[i][j];
			ima.at<Vec3b>(i, j)[2] = output[i][j];
		}
	}

	for (int i = 0; i < rows; i++) {
		delete[] input[i];
	}
	delete[] input;



	for (int i = 0; i < output_rows; i++) {
		delete[] output[i];
	}
	delete[] output;
}