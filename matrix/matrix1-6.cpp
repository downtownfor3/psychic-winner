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
        system("cls"); // ��������
        int** matrix1, ** matrix2, ** sum;
        int row1, col1, row2, col2;

        cout << "���������1���к�������";
        cin >> row1 >> col1;
        matrix1 = new int* [row1];
        for (int i = 0; i < row1; i++) {
            matrix1[i] = new int[col1];
        }
        cout << "���������1��Ԫ�أ��Կո�ָ�����" << endl;
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col1; j++) {
                cin >> matrix1[i][j];
            }
        }

        cout << "���������2���к�������";
        cin >> row2 >> col2;
        matrix2 = new int* [row2];
        for (int i = 0; i < row2; i++) {
            matrix2[i] = new int[col2];
        }
        cout << "���������2��Ԫ�أ��Կո�ָ�����" << endl;
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

            cout << "����1�Ӿ���2�Ľ���ǣ�" << endl;
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
            cout << "����1�;���2�޷���ӣ�" << endl;
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
    system("cls"); // ��������
    int row1, col1, scalar;
    cout << "�����������к�������" << endl;
    cin >> row1 >> col1 >> scalar;

    int** matrix = new int* [row1];  
    for (int i = 0; i < row1; i++) {
        matrix[i] = new int[col1];
    }

    cout << "����������Ԫ�أ��Կո�ָ�����" << endl;
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

    cout << "������������Ϊ ��" << endl;
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
    system("cls"); // ��������
    int** matrix, ** transMatrix;
    int rows, cols;

   
    cout << "�����������к�������";
    cin >> rows >> cols;
    matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

   
    cout << "����������Ԫ�أ��Կո�ָ�����" << endl;
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

   
    cout << "ת�ú�ľ����ǣ�" << endl;
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
    system("cls"); // ��������
    int** matrix1, ** matrix2, ** product;
    int row1, col1, row2, col2;

   
    cout << "���������1���к�������";
    cin >> row1 >> col1;
    matrix1 = new int* [row1];
    for (int i = 0; i < row1; i++) {
        matrix1[i] = new int[col1];
    }
    cout << "���������1��Ԫ�أ��Կո�ָ�����" << endl;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            cin >> matrix1[i][j];
        }
    }

    cout << "���������2���к�������";
    cin >> row2 >> col2;
    matrix2 = new int* [row2];
    for (int i = 0; i < row2; i++) {
        matrix2[i] = new int[col2];
    }
    cout << "���������2��Ԫ�أ��Կո�ָ�����" << endl;
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

        cout << "����1�˾���2�Ľ���ǣ�" << endl;
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
        cout << "����1�;���2�޷���ˣ�" << endl;
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
    system("cls"); // ��������
    int** matrix1, ** matrix2, ** sum;
    int row1, col1, row2, col2;

    cout << "���������1���к�������";
    cin >> row1 >> col1;
    matrix1 = new int* [row1];
    for (int i = 0; i < row1; i++) {
        matrix1[i] = new int[col1];
    }
    cout << "���������1��Ԫ�أ��Կո�ָ�����" << endl;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            cin >> matrix1[i][j];
        }
    }

    cout << "���������2���к�������";
    cin >> row2 >> col2;
    matrix2 = new int* [row2];
    for (int i = 0; i < row2; i++) {
        matrix2[i] = new int[col2];
    }
    cout << "���������2��Ԫ�أ��Կո�ָ�����" << endl;
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

        cout << "����1�;���2Hardmard�˻��Ľ���ǣ�" << endl;
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
        cout << "����1�;���2�޷���Hardmard�˻���" << endl;
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
    system("cls"); // ��������
    const int kernel_size = 3;
    const int padding = 1;
    const int stride = 1;

        int rows, cols;

        cout << "������ԭ������к�������";
        cin >> rows >> cols;

        int** input = new int* [rows]();
        for (int i = 0; i < rows; i++) {
            input[i] = new int[cols]();
        }

        cout << "������ԭ�����Ԫ�أ��Կո�ָ�����" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> input[i][j];
            }
        }

        int** kernel = new int* [kernel_size]();
        for (int i = 0; i < kernel_size; i++) {
            kernel[i] = new int[kernel_size]();
        }

        cout << "���������˵�Ԫ�أ��Կո�ָ�����" << endl;
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

        cout << "������þ���Ϊ ��" << endl;
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