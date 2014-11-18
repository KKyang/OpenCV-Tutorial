#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <iostream>

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
    void on_actionOpen_Image_triggered();

    void on_actionBlob_triggered();

private:
    Ui::MainWindow *ui;
    QString fileName;
    cv::Mat mat;
    std::vector<cv::Mat> bgr_planes;
};

#endif // MAINWINDOW_H
