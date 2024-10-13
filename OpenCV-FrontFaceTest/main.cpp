//
//  main.cpp
//  OpenCV-LittleLittleBoard
//
//  Created by Robert He on 2024/9/26.
//

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 加载预训练的人脸分类器（Haar 特征级联）
    String face_cascade_name = "/Users/robert/Documents/RobertProgrammes/C++/OpenCV/OpenCV-FrontFaceTest/OpenCV-FrontFaceTest/haarcascade_frontalface_alt.xml";
    CascadeClassifier face_cascade;

    // 检查是否成功加载分类器
    if (!face_cascade.load(face_cascade_name)) {
        cout << "Error loading face cascade" << endl;
        return -1;
    }

    // 打开摄像头
    VideoCapture capture(0); // 0表示使用默认摄像头
    if (!capture.isOpened()) {
        cout << "Error opening video capture" << endl;
        return -1;
    }

    Mat frame;

    while (capture.read(frame)) {
        if (frame.empty()) {
            cout << "No captured frame -- Break!" << endl;
            break;
        }

        // 转为灰度图像（人脸检测通常在灰度图上效果更好）
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray); // 均衡直方图以提高检测精度

        // 检测人脸
        std::vector<Rect> faces;
        face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        // 绘制矩形框在人脸周围
        for (size_t i = 0; i < faces.size(); i++) {
            // 使用 rectangle() 绘制矩形框
            rectangle(frame, faces[i], Scalar(255, 0, 255), 2);
        }
        
        // 显示结果
        imshow("Face Detection", frame);

        // 按下 'q' 键退出
        if (waitKey(10) == 'q') {
            break;
        }
    }

    return 0;
}
