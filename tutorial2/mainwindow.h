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
    void on_pushButton_loadImage_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    cv::Mat imgSrc;
};

#endif // MAINWINDOW_H
