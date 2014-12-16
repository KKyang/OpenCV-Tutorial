#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<cv::Mat>("cv::Mat");

    c = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    if(c)
    {
        c->stopCam();
        disconnect(c, SIGNAL(sendFrame(cv::Mat)), this, SLOT(getFrame(cv::Mat)));
        c->deleteLater();
    }
}

void MainWindow::on_actionOpen_Camera_triggered()
{
    if(ui->actionOpen_Camera->isChecked())
    {
        c = new camera();
        connect(c, SIGNAL(sendFrame(cv::Mat)), this, SLOT(getFrame(cv::Mat)));
        c->start();
    }
    else
    {
        c->stopCam();
    }
}

void MainWindow::getFrame(cv::Mat dst)
{
    //cv::imshow("ya", dst);
    cv::resize(dst, dst, cv::Size(ui->loadImage->width(), ui->loadImage->height()));
    ui->loadImage->setPixmap(QPixmap::fromImage(QImage(dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888).rgbSwapped()));
}
