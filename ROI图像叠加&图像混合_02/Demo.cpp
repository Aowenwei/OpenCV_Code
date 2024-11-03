#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>

const char* filepath = "../../../../1.jpg";
const char* logopath = "../../../../logo.png";

const char* mogu = "../../../../image/1.jpg";
const char* rain = "../../../../image/2.jpg";

using namespace cv;

//感兴趣的区域
bool ROI_AddImage();
//计算数组加权和:addWeighted()函数,实现图像的线性混合
bool LinearBlending();
//ROI区域图像叠加&图像混合
bool ROI_LinearBlending();

int main(int argc, char** argv) {
	//Mat image;
	//ROI_AddImage();
	//LinearBlending();
	system("color 5E");
	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending()) {
		fprintf(stdout,"运行成功,得出你需要的图片");
	}
	waitKey(0);
	//
	return 0;
}

//感兴趣的区域
bool ROI_AddImage() {
	Mat scrImage = imread(filepath);
	Mat logoImage = imread(logopath);
	if (!scrImage.data) {
		fprintf(stdout, "读取scrImage错误!\n"); 
		return false;
	}
	if (!logoImage.data) {
		fprintf(stdout, "读取logoImage错误!\n");
		return false;
	}
	//定义一个Mat类型给其设定ROI区域
	Mat imageROI = scrImage(Rect(200, 250, logoImage.cols, logoImage.rows));
	//加载掩模 (必须是灰度图)
	Mat mask = imread(logopath, 0);
	//将掩膜复制到ROI区域
	logoImage.copyTo(imageROI, mask);//掩膜运算
	
	imshow("ROI 区域", scrImage);
	return true;
}

//计算数组加权和:addWeighted()函数,实现图像的线性混合
bool LinearBlending() {

	//定义一些局部变量
	double alphaValue = 0.5; //透明程度
	double betaValue{};
	Mat scrImage2, scrImage3, destImage;
	//读取图像(相符图片像需要同样的尺寸和类型)

	scrImage2 = imread(mogu);
	scrImage3 = imread(rain);
	if (!scrImage2.data) {
		fprintf(stdout, "读取scrImage2错误!\n");
		return false;
	}
	if (!scrImage3.data) {
		fprintf(stdout, "读取scrImage3错误!\n");
		return false;
	}

	//做图像混合加权操作
	betaValue = (1.0 - alphaValue);
	addWeighted(scrImage2, alphaValue, scrImage3, betaValue, 0.0, destImage);

	//显示
	imshow("混合窗口原图: ", scrImage2);
	imshow("混合窗口效果图: ", destImage);
	return true;
}

//ROI区域图像叠加&图像混合
bool ROI_LinearBlending() {
	//线性混合实现函数.指定区域线性图像混合,利用cv::addWeighted()函数结合定义
	//读取图片
	Mat scrImage4 = imread(filepath);
	Mat logoImage = imread(logopath);
	if (!scrImage4.data) {
		fprintf(stdout, "读取scrImage4错误!\n");
		return false;
	}
	if (!logoImage.data) {
		fprintf(stdout, "读取logoImage错误!\n");
		return false;
	}

	//定义一个Mat类型并给其设定ROI区域
	Mat imageROI;
	//方法1
	imageROI = scrImage4(Rect(200, 250, logoImage.cols,logoImage.rows));
	//方法2
	//imageROI = scrImage4(Range(250, 250 + logoImage.rows), Range(200, 200 + logoImage.cols));

	//将loge加到原图上
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0.0, imageROI);

	//显示
	imshow("区域线性图像混合实例窗口", scrImage4);

}