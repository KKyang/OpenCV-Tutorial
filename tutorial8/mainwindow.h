#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/features2d/features2d.hpp"
#include <math.h>
#include <iostream>
#include "camera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_Camera_triggered();
    void closeEvent(QCloseEvent *);

    void getFrame(cv::Mat dst);

private:
    Ui::MainWindow *ui;
    QString fileName;
    cv::Mat mat;
    std::vector<cv::Mat> bgr_planes;
    camera *c;
};

#endif // MAINWINDOW_H
