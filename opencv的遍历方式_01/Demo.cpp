#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
const char* filename { "../../../../1.jpg" };
const char* name { "show image" };

#define W 80
#define H 100
void colorReduce(Mat& inputImage, Mat& outputImage, int div);
int main(int argc, char** argv)
{

#if 1
    Mat image;
    image = imread(filename, CV_64FC1);
    if (image.empty()) {
        fprintf(stdout, "Can't open 1.jpg file!\n");
        exit(EXIT_SUCCESS);
    }
    Mat outputImage;
    colorReduce(image, outputImage, 32);

#endif
    // namedWindow(name);
    imshow(name, outputImage);
    waitKey(0);
    std::cout << "当前适用版本:" << CV_VERSION << "\n";
    return 0;
}

// 第三种方式: 动态地址方式访问
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    double time0 = static_cast<double>(getTickCount());
    // 参数准备,复制实参到临时变量
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols * outputImage.channels();
    // 存取彩色图像像素
    for (int i = 0; i != rowNumber; ++i) {
        uchar* data = outputImage.ptr<uchar>(i);
        for (int j = 0; j != colNumber; ++j) {
            *data++ = *data / div * div + div / 2;
        }
    }
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    std::cout << "\n 使用了: " << time0 << " 秒\n";
}