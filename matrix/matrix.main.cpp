#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// �˿�����в�������������ҵ�������޸�

void wait_for_enter()
{
    cout << endl
        << "���س�������";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}
void application(Mat& ima,int i);
void demo()
{
    system("cls"); // ��������

   

    Mat image[6];
    for (int i = 0; i < 6; i++)
        image[i] = imread("123.jpg");// ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
   
    for (int i = 0; i < 6; i++)
       application(image[i], i);
    
    namedWindow("Image-result_5", 0);//��������
    imshow("Image-result_0", image[0]);
    imshow("Image-result_1", image[1]);
    imshow("Image-result_2", image[2]);
    imshow("Image-result_3", image[3]);
    imshow("Image-result_4", image[4]);
    imshow("Image-result_5", image[5]);
    waitKey(0);

    // ��ʾ��Mat��ʽ���������໥ת��
    wait_for_enter(); 
   

    return;
}

void menu(char*p);
void matriplus();
void nummulti();
void matritrans();
void matrimulti();
void hadamulti();
void conv();
void application_(Mat& ima);
void otsu() {
    system("cls"); // ��������



    Mat image[4];
   
       image[0]=imread("snowball.jpg");// ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
       image[1] = imread("polyhedrosis.jpg");
       image[2] = imread("ship.jpg");
       image[3] = imread("brain.jpg ");
        
    for (int i = 0; i < 4; i++)
        application_(image[i]);

    imshow("Image-result_0", image[0]);
    imshow("Image-result_1", image[1]);
    imshow("Image-result_2", image[2]);
    imshow("Image-result_3", image[3]);
    waitKey(0);

    // ��ʾ��Mat��ʽ���������໥ת��
    wait_for_enter();

}
int main()
{
    // ������ر���
    char choice = '0';
    char ch;
    wait_for_enter();
    while (true) // ע���ѭ���˳�������
    {
        system("cls"); // ��������

        menu(&choice); // ���ò˵���ʾ���������в������

        // ��Ҫ������˵�ѡ����choice

        if (choice == '0') // ѡ���˳�
        {
            cout << "\n ȷ���˳���?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
         {
             // ���������������������Ʋ���ɣ����������������������͵ȣ�����ѡ��ӷ�������в���
         case '1':
             matriplus();
             break;
         case '2':
             nummulti();
             break;
         case '3':
             matritrans();
             break;
         case '4':
             matrimulti();
             break;
         case '5':
             hadamulti();
             break;
         case '6':
             conv();
             break;
         case '7':
             demo();
             break;
         case '8':
             otsu();
             break;
         default:
             cout << "\n ����������������" << endl;
             wait_for_enter();
         }
     }

    return 0;
}