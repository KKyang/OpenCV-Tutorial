#include "mainwindow.h"
#include "ui_mainwindow.h"

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



void MainWindow::on_actionBlur_triggered()
{
    if(!mat.empty())
    {
        cv::Mat dst;
        cv::blur(mat, dst, cv::Size(5,5));  //blur function
        cv::imshow("blur", dst);
    }
}

void MainWindow::on_actionGaussian_Blur_triggered()
{
    if(!mat.empty())
    {
        cv::Mat dst;
        cv::GaussianBlur(mat,dst, cv::Size(5,5),0,0);  //gaussian blur
        cv::imshow("Gaussian blur", dst);
    }
}

void MainWindow::on_actionMedian_Blur_triggered()
{
    if(!mat.empty())
    {
        cv::Mat dst;
        cv::medianBlur(mat,dst, 5);  //median blur
        cv::imshow("Median blur", dst);
    }
}

void MainWindow::on_actionBilateral_Blur_triggered()
{
    if(!mat.empty())
    {
        cv::Mat dst;
        cv::bilateralFilter(mat,dst, 5,2.5,2.5);  //bilateral blur
        cv::imshow("Bilateral blur", dst);
    }
}

void MainWindow::on_actionLaplacian_triggered()
{
    if(!mat.empty())
    {
        cv::Mat gray, dst, result, HSV;
        //BGR 2 GRAY fro laplacian
        cv::cvtColor(mat, gray,cv::COLOR_BGR2GRAY);
        cv::Laplacian(gray, dst, CV_16S, 1);
        //Normalize Laplacian result
        cv::convertScaleAbs(dst,dst);
        //Convert BGR image to HSV
        cv::cvtColor(mat, HSV, cv::COLOR_BGR2HSV);
        std::vector<cv::Mat> s;
        cv::split(HSV,s);
        //Compute Intensity using V channel (V channel - Laplacian result)
        s[2] = s[2] - dst;
        cv::merge(s,HSV);
        //Convert HSV back to BGR
        cv::cvtColor(HSV, result,cv::COLOR_HSV2BGR);
        cv::imshow("Laplacian result", dst);
        cv::imshow("Final result", result);
    }
}
