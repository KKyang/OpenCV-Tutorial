#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <vector>
#include "opencv.hpp"

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
    void on_pushButton_loadImage_clicked();


    void on_pushButton_saveImage_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    cv::Mat imgSrc;
    std::vector<cv::UMat> img;
};

#endif // MAINWINDOW_H
