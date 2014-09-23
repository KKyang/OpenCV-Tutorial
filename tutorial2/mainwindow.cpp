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

void MainWindow::on_pushButton_loadImage_clicked()
{
     cv::UMat img[2];
     fileName = QFileDialog::getOpenFileName(this,tr("Open File"));
     imgSrc = cv::imread(fileName.toStdString());

     if(!imgSrc.empty())
     {
         for(int i=0;i<2;i++)
         {
             if(i == 1)
                 cv::threshold(imgSrc, img[i], 10, 255, 0);
             else
                 imgSrc.copyTo(img[i]);
             cv::cvtColor(img[i],img[i],cv::COLOR_BGR2RGB);
             QImage tmp(img[i].getMat(1).data,
                        img[i].cols,
                        img[i].rows,
                        img[i].step,
                        QImage::Format_RGB888);

             if(tmp.width() > ui->loadImage->width() ||
                tmp.height() > ui->loadImage->height())
             {
                 tmp = tmp.scaled(ui->loadImage->width(),
                                  ui->loadImage->height(),
                                  Qt::KeepAspectRatio);
             }
             if(i == 0)
                ui->loadImage->setPixmap(QPixmap::fromImage(tmp));
             else
                 ui->loadImage_2->setPixmap(QPixmap::fromImage(tmp));
             cv::cvtColor(img[i],img[i],cv::COLOR_RGB2BGR);
         }
     }
}

