#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
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
    void on_actionOpen_Image_triggered();

    void on_actionHistogram_triggered();

    void on_actionHistogram_Equalization_triggered();

private:
    Ui::MainWindow *ui;
    QString fileName;
    cv::Mat mat;
    std::vector<cv::Mat> bgr_planes;
};

#endif // MAINWINDOW_H
