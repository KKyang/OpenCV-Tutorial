#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.resize(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_loadImage_clicked()
{
     //Open a Qt Dialog to get file name path.
     fileName = QFileDialog::getOpenFileName(this,tr("Open File"));
     //OpenCV read image to mat.
     imgSrc = cv::imread(fileName.toStdString());
     //Check if the mat gets the image data.
     if(!imgSrc.empty())
     {
         for(int i=0;i<2;i++)
         {
             if(i == 1)
                 //OpenCV threshold
                 cv::threshold(imgSrc, img[i], 10, 255, 0);
             else
                 //Copy image to UMat
                 imgSrc.copyTo(img[i]);
             //Change UMat colorchannel from BGR to RGB.
             cv::cvtColor(img[i],img[i],cv::COLOR_BGR2RGB);
             //Port image data from UMat to QImage.
             QImage tmp(img[i].getMat(1).data,
                        img[i].cols,
                        img[i].rows,
                        img[i].step,
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
             if(i == 0)
                 //Put QImage on a label.
                 ui->loadImage->setPixmap(QPixmap::fromImage(tmp));
             else
                 ui->loadImage_2->setPixmap(QPixmap::fromImage(tmp));
             //Change UMat colorchannel from RGB back to BGR to get next image data.
             cv::cvtColor(img[i],img[i],cv::COLOR_RGB2BGR);
         }
     }
}




void MainWindow::on_pushButton_saveImage_clicked()
{
    //Open a Qt Dialog to get save file name path.
    fileName = QFileDialog::getSaveFileName(this,tr("Close File"));

    if(!fileName.isEmpty())
        for(int i =0; i < img.size();i++)
        {
            //Rename if multiple image saving is required.
            QString a = fileName + "_"+QString::number(i)+".png";
            if(!img[i].empty())
                //OpenCV save image.
                cv::imwrite(a.toStdString(),img[i]);
        }
}
