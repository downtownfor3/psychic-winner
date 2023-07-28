#include <conio.h>
#include <iostream>
// #include <opencv2/opencv.hpp>
// using namespace cv;
using namespace std;
void wait_for_enter();


void convolve(int** input, int** output, int** kernel, int rows, int cols, int kernel_size = 3, int padding = 1, int stride = 1) {
    int output_rows = (rows - kernel_size + 2 * padding) / stride + 1;
    int output_cols = (cols - kernel_size + 2 * padding) / stride + 1;

    
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
            output[i][j] = sum;
        }
    }

    for (int i = 0; i < rows + 2 * padding; i++) {
        delete[] padded_input[i];
    }
    delete[] padded_input;
}


void matriplus() {
        system("cls"); // 清屏函数
        int** matrix1, ** matrix2, ** sum;
        int row1, col1, row2, col2;

        cout << "请输入矩阵1的行和列数：";
        cin >> row1 >> col1;
        matrix1 = new int* [row1];
        for (int i = 0; i < row1; i++) {
            matrix1[i] = new int[col1];
        }
        cout << "请输入矩阵1的元素（以空格分隔）：" << endl;
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col1; j++) {
                cin >> matrix1[i][j];
            }
        }

        cout << "请输入矩阵2的行和列数：";
        cin >> row2 >> col2;
        matrix2 = new int* [row2];
        for (int i = 0; i < row2; i++) {
            matrix2[i] = new int[col2];
        }
        cout << "请输入矩阵2的元素（以空格分隔）：" << endl;
        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < col2; j++) {
                cin >> matrix2[i][j];
            }
        }

        if (row1 == row2 && col1 == col2) {
            sum = new int* [row1];
            for (int i = 0; i < row1; i++) {
                sum[i] = new int[col1];
                for (int j = 0; j < col1; j++) {
                    sum[i][j] = matrix1[i][j] + matrix2[i][j];
                }
            }

            cout << "矩阵1加矩阵2的结果是：" << endl;
            for (int i = 0; i < row1; i++) {
                for (int j = 0; j < col1; j++) {
                    cout << sum[i][j] << " ";
                }
                cout << endl;
            }

            for (int i = 0; i < row1; i++) {
                delete[] sum[i];
            }
            delete[] sum;
        }
        else {
            cout << "矩阵1和矩阵2无法相加！" << endl;
        }

        for (int i = 0; i < row1; i++) {
            delete[] matrix1[i];
        }
        delete[] matrix1;

        for (int i = 0; i < row2; i++) {
            delete[] matrix2[i];
        }
        delete[] matrix2;
        wait_for_enter();

}
void nummulti() {
    system("cls"); // 清屏函数
    int row1, col1, scalar;
    cout << "请输入矩阵的行和列数：" << endl;
    cin >> row1 >> col1 >> scalar;

    int** matrix = new int* [row1];  
    for (int i = 0; i < row1; i++) {
        matrix[i] = new int[col1];
    }

    cout << "请输入矩阵的元素（以空格分隔）：" << endl;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            cin >> matrix[i][j];
        }
    }


    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            matrix[i][j] = matrix[i][j] * scalar;
        }
    }

    cout << "数乘运算后矩阵为 ：" << endl;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < row1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    wait_for_enter();
}
void matritrans() {
    system("cls"); // 清屏函数
    int** matrix, ** transMatrix;
    int rows, cols;

   
    cout << "请输入矩阵的行和列数：";
    cin >> rows >> cols;
    matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

   
    cout << "请输入矩阵的元素（以空格分隔）：" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }

    
    transMatrix = new int* [cols];
    for (int i = 0; i < cols; i++) {
        transMatrix[i] = new int[rows];
        for (int j = 0; j < rows; j++) {
            transMatrix[i][j] = 0;
        }
    }

   
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            transMatrix[i][j] = matrix[j][i];
        }
    }

   
    cout << "转置后的矩阵是：" << endl;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            cout << transMatrix[i][j] << " ";
        }
        cout << endl;
    }

   
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    for (int i = 0; i < cols; i++) {
        delete[] transMatrix[i];
    }
    delete[] transMatrix;
    wait_for_enter();
}
void matrimulti() {
    system("cls"); // 清屏函数
    int** matrix1, ** matrix2, ** product;
    int row1, col1, row2, col2;

   
    cout << "请输入矩阵1的行和列数：";
    cin >> row1 >> col1;
    matrix1 = new int* [row1];
    for (int i = 0; i < row1; i++) {
        matrix1[i] = new int[col1];
    }
    cout << "请输入矩阵1的元素（以空格分隔）：" << endl;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            cin >> matrix1[i][j];
        }
    }

    cout << "请输入矩阵2的行和列数：";
    cin >> row2 >> col2;
    matrix2 = new int* [row2];
    for (int i = 0; i < row2; i++) {
        matrix2[i] = new int[col2];
    }
    cout << "请输入矩阵2的元素（以空格分隔）：" << endl;
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            cin >> matrix2[i][j];
        }
    }

  
    if (col1 == row2) {
        product = new int* [row1];
        for (int i = 0; i < row1; i++) {
            product[i] = new int[col2];
            for (int j = 0; j < col2; j++) {
                product[i][j] = 0;
                for (int k = 0; k < col1; k++) {
                    product[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        cout << "矩阵1乘矩阵2的结果是：" << endl;
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                cout << product[i][j] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < row1; i++) {
            delete[] product[i];
        }
        delete[] product;
    }
    else {
        cout << "矩阵1和矩阵2无法相乘！" << endl;
    }

   
    for (int i = 0; i < row1; i++) {
        delete[] matrix1[i];
    }
    delete[] matrix1;

    for (int i = 0; i < row2; i++) {
        delete[] matrix2[i];
    }
    delete[] matrix2;
    wait_for_enter();
}
void hadamulti() {
    system("cls"); // 清屏函数
    int** matrix1, ** matrix2, ** sum;
    int row1, col1, row2, col2;

    cout << "请输入矩阵1的行和列数：";
    cin >> row1 >> col1;
    matrix1 = new int* [row1];
    for (int i = 0; i < row1; i++) {
        matrix1[i] = new int[col1];
    }
    cout << "请输入矩阵1的元素（以空格分隔）：" << endl;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            cin >> matrix1[i][j];
        }
    }

    cout << "请输入矩阵2的行和列数：";
    cin >> row2 >> col2;
    matrix2 = new int* [row2];
    for (int i = 0; i < row2; i++) {
        matrix2[i] = new int[col2];
    }
    cout << "请输入矩阵2的元素（以空格分隔）：" << endl;
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            cin >> matrix2[i][j];
        }
    }

    if (row1 == row2 && col1 == col2) {
        sum = new int* [row1];
        for (int i = 0; i < row1; i++) {
            sum[i] = new int[col1];
            for (int j = 0; j < col1; j++) {
                sum[i][j] = matrix1[i][j] * matrix2[i][j];
            }
        }

        cout << "矩阵1和矩阵2Hardmard乘积的结果是：" << endl;
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col1; j++) {
                cout << sum[i][j] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < row1; i++) {
            delete[] sum[i];
        }
        delete[] sum;
    }
    else {
        cout << "矩阵1和矩阵2无法做Hardmard乘积！" << endl;
    }

    for (int i = 0; i < row1; i++) {
        delete[] matrix1[i];
    }
    delete[] matrix1;

    for (int i = 0; i < row2; i++) {
        delete[] matrix2[i];
    }
    delete[] matrix2;
    wait_for_enter();
}
void conv() {
    system("cls"); // 清屏函数
    const int kernel_size = 3;
    const int padding = 1;
    const int stride = 1;

        int rows, cols;

        cout << "请输入原矩阵的行和列数：";
        cin >> rows >> cols;

        int** input = new int* [rows]();
        for (int i = 0; i < rows; i++) {
            input[i] = new int[cols]();
        }

        cout << "请输入原矩阵的元素（以空格分隔）：" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> input[i][j];
            }
        }

        int** kernel = new int* [kernel_size]();
        for (int i = 0; i < kernel_size; i++) {
            kernel[i] = new int[kernel_size]();
        }

        cout << "请输入卷积核的元素（以空格分隔）：" << endl;
        for (int i = 0; i < kernel_size; i++) {
            for (int j = 0; j < kernel_size; j++) {
                cin >> kernel[i][j];
            }
        }

        int output_rows = rows + 2 * padding - kernel_size + 1;
        int output_cols = cols + 2 * padding - kernel_size + 1;

        int** output = new int* [output_rows]();
        for (int i = 0; i < output_rows; i++) {
            output[i] = new int[output_cols]();
        }

        convolve(input, output, kernel, rows, cols);

        cout << "卷积所得矩阵为 ：" << endl;
        for (int i = 0; i < output_rows; i++) {
            for (int j = 0; j < output_cols; j++) {
                cout << output[i][j] << " ";
            }
            cout << endl;
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
        wait_for_enter();
}