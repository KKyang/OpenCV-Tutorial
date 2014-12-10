#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Image_triggered()
{
    //Open a Qt Dialog to get file name path.
         fileName = QFileDialog::getOpenFileName(this,tr("Open File"));
         //OpenCV read image to mat.
         mat = cv::imread(fileName.toStdString());
         //Check if the mat gets the image data.
         if(!mat.empty())
         {
                 //Change UMat colorchannel from BGR to RGB.
                 cv::cvtColor(mat,mat,cv::COLOR_BGR2RGB);
                 //Port image data from UMat to QImage.
                 QImage tmp(mat.data,
                            mat.cols,
                            mat.rows,
                            mat.step,
                            QImage::Format_RGB888);
                 //If QImage is too big, resize to fit the screen.
                 if(tmp.width() > ui->loadImage->width() ||
                    tmp.height() > ui->loadImage->height())
                 {
                     //QImage resize.
                     tmp = tmp.scaled(ui->loadImage->width(),
                                      ui->loadImage->height(),
                                      Qt::KeepAspectRatio);
                 }
                 //Put QImage on a label.
                 ui->loadImage->setPixmap(QPixmap::fromImage(tmp));
                 //Change UMat colorchannel from RGB back to BGR to get next image data.
                 cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
         }
}
void MainWindow::on_actionBlob_triggered()
{
    if(mat.empty())
        return;
    // Blob test
    cv::SimpleBlobDetector::Params params;
    params.minDistBetweenBlobs = 50.0f;
    params.filterByInertia = false;
    params.filterByConvexity = true;
    params.filterByColor = true;
    params.blobColor = 0;
    params.filterByCircularity = false;
    params.filterByArea = true;
    params.minArea = 1000.0f;
    params.maxArea = 1000000.0f;

    std::vector<cv::KeyPoint> keypoints;

    //Method One
    //cv::SimpleBlobDetector a(params);
    //a.detect(mat, keypoints);
    //Method Two
    cv::Ptr<cv::FeatureDetector> blob_detector = cv::makePtr<cv::SimpleBlobDetector>(params);
    blob_detector->detect(mat, keypoints);
    cv::Mat frame = mat.clone();

    //Two ways - Method one.

    for (int i = 0; i < keypoints.size(); i++)
    {
        cv::circle(frame, cv::Point(keypoints[i].pt.x, keypoints[i].pt.y), 5, cv::Scalar(255, 0, 0), -1);
        //std::cout << keypoints[i].size << std::endl;
    }
    /*
    //Two ways - Method two.
    cv::drawKeypoints(mat, keypoints, frame);
    */
    for(auto blobIterator = keypoints.begin(); blobIterator != keypoints.end(); blobIterator++){
       std::cout << "size of blob is: " << blobIterator->size << std::endl;
       std::cout << "point is at: " << blobIterator->pt.x << " " << blobIterator->pt.y << std::endl;
    }
    cv::imshow("yeah", frame);
    return;
}
