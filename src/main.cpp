#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

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
        cv::imshow("OpenCV DNN 人脸检测演示", frame);
        if(cv::waitKey(10) == 27){
            break;
        }
    }

    cv::destroyAllWindows();
    return 0;
}
