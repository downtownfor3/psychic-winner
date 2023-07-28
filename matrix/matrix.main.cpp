#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 此框架若有不完美可以在作业中任意修改

void wait_for_enter()
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}
void application(Mat& ima,int i);
void demo()
{
    system("cls"); // 清屏函数

   

    Mat image[6];
    for (int i = 0; i < 6; i++)
        image[i] = imread("123.jpg");// 图像的灰度值存放在格式为Mat的变量image中
   
    for (int i = 0; i < 6; i++)
       application(image[i], i);
    
    namedWindow("Image-result_5", 0);//创建窗口
    imshow("Image-result_0", image[0]);
    imshow("Image-result_1", image[1]);
    imshow("Image-result_2", image[2]);
    imshow("Image-result_3", image[3]);
    imshow("Image-result_4", image[4]);
    imshow("Image-result_5", image[5]);
    waitKey(0);

    // 提示：Mat格式可与数组相互转换
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
    system("cls"); // 清屏函数



    Mat image[4];
   
       image[0]=imread("snowball.jpg");// 图像的灰度值存放在格式为Mat的变量image中
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

    // 提示：Mat格式可与数组相互转换
    wait_for_enter();

}
int main()
{
    // 定义相关变量
    char choice = '0';
    char ch;
    wait_for_enter();
    while (true) // 注意该循环退出的条件
    {
        system("cls"); // 清屏函数

        menu(&choice); // 调用菜单显示函数，自行补充完成

        // 按要求输入菜单选择项choice

        if (choice == '0') // 选择退出
        {
            cout << "\n 确定退出吗?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
         {
             // 下述矩阵操作函数自行设计并完成（包括函数参数及返回类型等），若选择加分项，请自行补充
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
             cout << "\n 输入错误，请从新输入" << endl;
             wait_for_enter();
         }
     }

    return 0;
}