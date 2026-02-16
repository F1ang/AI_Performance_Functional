/*
 * @Description:
 * @Author: YiPei_Fang
 * @Date: 2022-04-11 13:10:01
 */
/*
    powershell:g++ Romantic-a.cpp -o Romantic-a.exe; ./Romantic-a.exe
*/

// #include <opencv2/highgui.hpp>
// #include <opencv2/opencv.hpp>

// using namespace cv;

// int main() {
//   Mat img = imread("Lena.jpg");
//   namedWindow("309", 0);
//   resizeWindow("309", 640, 480);
//   imshow("309", img);
//   waitKey(0);
//   return 0;
// }

// #include <iostream>
// #include <math.h>
// #include <opencv2/opencv.hpp>
// #include <opencv2/xfeatures2d/xfeatures2d.hpp>

// using namespace cv;
// using namespace std;
// using namespace cv::xfeatures2d;

// Mat src, dst, gray_src;
// const char *output_title = "output_win";
// int corners = 20;
// int max_corners = 50;

// void Tomasi_Demo(int, void *);
// void SubPixel_Demo(int, void *);
// int main(int argc, char **argv) {
//   src = imread("people.jpg");
//   if (src.empty()) {
//     printf("could not load image");
//     return -1;
//   }
//   namedWindow("input image", 1);
//   imshow("input_img", src);

//   // 计算检测算??

//   // 将目标图像转化为窗口大小
//   // resize(src, dst, Size(64, 128));
//   // cvtColot(dst, dst_gray, COLOR_BGR2GRAY);

//   // 定义HOG检测器
//   // HOGDescriptor detector(Size(64, 128), Size(16, 16), Size(8, 8), Size(8,
//   8),
//   // 9);

//   // 定义容器装特征描述子以及对应描述子的位置
//   // vector<float> descriptors;
//   // vector<Point> locations;

//   // 根据窗口大小??动???算窗口移动步长，并返回算子数据
//   // detector.compute(dst_gray,descriptors,Size(0,0),Size(0,0),locations);

//   // printf("number of HOG descriptors:%d", descriptors.size());//3780

//   // 行人检测???例

//   // 新建一个HOGDescriptor对象
//   HOGDescriptor hog = HOGDescriptor();
//   // 使用open CV定义好的模型
//   // 新建一个SVM分类检测器
//   // getDefaultPeopleDetector()--人像检测库
//   vector<Rect> foundLocations;
//   hog.setSVMDetector(hog.getDefaultPeopleDetector());

//   vector<Rect> foundLocation; // 定义容器装???测结果的矩形
//   // detectMultiScale对图像进行???尺度?????
//   hog.detectMultiScale(src, foundLocations, 0, Size(8, 8), Size(32,
//   32), 1.05,
//                        2);

//   // 将结果在另一张图片中画出
//   Mat result = src.clone();
//   for (size_t i = 0; i < foundLocations.size(); i++) {
//     rectangle(result, foundLocation[i], Scalar(0, 0, 255), 2, 8, 0);
//   }
//   imshow("HOG SVM Detector Demo", result);

//   waitKey(0);
//   return 0;
// }

// // #include <opencv2\opencv.hpp>

// // using namespace cv;
// // using namespace std;

// // int main()
// // {
// //     Mat frame;
// //     VideoCapture
// //
// capture(0);//读取视摄像头实时画面数据??0默???是笔???本的摄像头；???果??外接摄像头，这里改为1

// //     while (true)
// //     {

// //         capture >> frame;            //读取当前??
// //         if(!frame.empty()){ //判断输入的??????帧??否为空的

// //             imshow("window",frame);
// //             //在window窗口显示frame摄像头数??画面
// //         }

// //         if(waitKey(20) == 'q')
// //         //延时20ms,获取用户??否按??的情况，如果按下q，会推出程序
// // 		break;
// //     }

// //     capture.release();     //释放摄像头资??
// //     destroyAllWindows();   //释放全部窗口
// //     return 0;
// // }

// #include <opencv2/opencv.hpp>

// using namespace cv;

// int main() {
//   VideoCapture cap(0); // 双目相机作为一个设备

//   Mat frame, left, right;

//   while (true) {
//     cap >> frame; // 读取一帧（左右拼接的画面）

//     // 从中间分割成左右两图
//     int width = frame.cols / 2;
//     left = frame(Rect(0, 0, width, frame.rows));      // 左图
//     right = frame(Rect(width, 0, width, frame.rows)); // 右图

//     imshow("Left", left);
//     imshow("Right", right);
//     imshow("Stereo", frame);

//     if (waitKey(1) == 27)
//       break; // ESC 退出
//   }

//   return 0;
// }

#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
  // ? 硬件双目 = 1 个设备 = 只需要打开 cap(0)
  VideoCapture cap(0);
  if (!cap.isOpened()) {
    return -1;
  }

  Mat frame, left, right, output;
  namedWindow("Stereo Camera", WINDOW_NORMAL);

  while (true) {
    cap >> frame; // 读取一帧（包含左右两个画面）
    if (frame.empty())
      continue;

    // ? 从中间分割成左右两部分
    int w = frame.cols / 2;
    left = frame(Rect(0, 0, w, frame.rows));  // 左半部分
    right = frame(Rect(w, 0, w, frame.rows)); // 右半部分

    // ? 拼接显示（添加白色分隔线）
    Mat divider(frame.rows, 5, CV_8UC3, Scalar(255, 255, 255));
    hconcat(left, divider, output);
    hconcat(output, right, output);

    imshow("Stereo Camera", output);

    if (waitKey(1) == 27)
      break;
  }

  return 0;
}