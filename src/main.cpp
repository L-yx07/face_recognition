#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;

#ifdef _WIN32
// OpenCV 4.1.0(MinGW 版) 的 highgui 用系统 ANSI 代码页(中文系统即 GBK)解析窗口标题，
// 而源码里的中文字面量是 UTF-8，直接传会导致标题乱码。这里运行时转成 ANSI。
static std::string utf8ToAnsi(const std::string& utf8) {
    if (utf8.empty()) return utf8;
    int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
    std::wstring wide(wlen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &wide[0], wlen);
    int alen = WideCharToMultiByte(CP_ACP, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string ansi(alen, '\0');
    WideCharToMultiByte(CP_ACP, 0, wide.c_str(), -1, &ansi[0], alen, nullptr, nullptr);
    ansi.resize(alen - 1); // 去掉结尾的 '\0'
    return ansi;
}
#else
static std::string utf8ToAnsi(const std::string& s) { return s; }
#endif

int main(){
    std::string pb_file_path = "D:/opencv_face_detector_uint8.pb";
    std::string txt_file_path = "D:/opencv_face_detector.pbtxt";
    cv::dnn::Net net = cv::dnn::readNetFromTensorflow(pb_file_path, txt_file_path);
    VideoCapture cap(0);
    cv::Mat frame;
    if(!cap.isOpened()){
        std::cout << "Error opening video stream" << std::endl;
        return -1;
    }
    while(1){
        cap.read(frame);
        if(frame.empty()){
            std::cout << "Error reading frame" << std::endl;
            break;
        }
        cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0));
        net.setInput(blob);
        cv::Mat probs = net.forward();
        cv::Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

        for(int rows = 0; rows < detectionMat.rows; rows++){
            float confidence = detectionMat.at<float>(rows, 2);
            if(confidence > 0.5){
                float x1 = static_cast<int>(detectionMat.at<float>(rows, 3) * frame.cols);
                float y1 = static_cast<int>(detectionMat.at<float>(rows, 4) * frame.rows);
                float x2 = static_cast<int>(detectionMat.at<float>(rows, 5) * frame.cols);
                float y2 = static_cast<int>(detectionMat.at<float>(rows, 6) * frame.rows);
                cv::Rect box(x1, y1, x2 - x1, y2 - y1);
                cv::rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);
            }
        }
 //       rotate(frame, frame, cv::ROTATE_90_CLOCKWISE);
 //       flip(frame, frame, 1);
        cv::imshow(utf8ToAnsi("OpenCV DNN 人脸检测演示"), frame);
        if(cv::waitKey(10) == 27){
            break;
        }
    }

    cv::destroyAllWindows();
    return 0;
}
