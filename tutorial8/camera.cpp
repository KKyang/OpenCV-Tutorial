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
    cv::Mat frame;
    cv::waitKey(100);
    cv::VideoWriter w;

    w.open("fugu.avi", cv::VideoWriter::fourcc('F', 'M', 'P', '4'), 30, cv::Size(cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_FRAME_HEIGHT)), true);
    while(!stopped)
    {
        cap >> frame;
        emit sendFrame(frame);

        w.write(frame);
    }

    w.release();
}
