#include "camera.h"

camera::camera(QObject *parent) :
    QThread(parent)
{
}

void camera::run()
{
    cv::VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())
        return;

    stopped = false;
    cv::Mat frame, hough;
    std::vector<cv::Vec3f> circles;
    cv::waitKey(100);
    cv::VideoWriter w;

    w.open("fugu.avi", cv::VideoWriter::fourcc('F', 'M', 'P', '4'), 30, cv::Size(cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_FRAME_HEIGHT)), true);
    while(!stopped)
    {
        cap >> frame;
        cv::cvtColor(frame, hough, cv::COLOR_BGR2GRAY);

        //Blur to avoid false circle.
        //cv::GaussianBlur(hough, hough, cv::Size(5,5), 2, 2);

        cv::HoughCircles(hough, circles, cv::HOUGH_GRADIENT, 1, hough.rows/8, 300, 100, 0, 0);
        //Draw circle
        for(size_t i = 0; i < circles.size();i++)
        {
            cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);

            cv::circle(frame, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
            cv::circle(frame, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
        }
        emit sendFrame(frame);
        w.write(frame);
    }

    w.release();
}
