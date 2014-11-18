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
    const int w = 500;
    int levels = 3;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat img = Mat::zeros(w, w, CV_8UC1);

    //Draw 6 faces
    for( int i = 0; i < 6; i++ )
    {
        int dx = (i%2)*250 - 30;
        int dy = (i/2)*150;
        const Scalar white = Scalar(255);
        const Scalar black = Scalar(0);

        if( i == 0 )
        {
            for( int j = 0; j <= 10; j++ )
            {
                double angle = (j+5)*CV_PI/21;
                line(img, Point(cvRound(dx+100+j*10-80*cos(angle)),
                    cvRound(dy+100-90*sin(angle))),
                    Point(cvRound(dx+100+j*10-30*cos(angle)),
                    cvRound(dy+100-30*sin(angle))), white, 1, 8, 0);
            }
        }

        ellipse( img, Point(dx+150, dy+100), Size(100,70), 0, 0, 360, white, -1, 8, 0 );
        ellipse( img, Point(dx+115, dy+70), Size(30,20), 0, 0, 360, black, -1, 8, 0 );
        ellipse( img, Point(dx+185, dy+70), Size(30,20), 0, 0, 360, black, -1, 8, 0 );
        ellipse( img, Point(dx+115, dy+70), Size(15,15), 0, 0, 360, white, -1, 8, 0 );
        ellipse( img, Point(dx+185, dy+70), Size(15,15), 0, 0, 360, white, -1, 8, 0 );
        ellipse( img, Point(dx+115, dy+70), Size(5,5), 0, 0, 360, black, -1, 8, 0 );
        ellipse( img, Point(dx+185, dy+70), Size(5,5), 0, 0, 360, black, -1, 8, 0 );
        ellipse( img, Point(dx+150, dy+100), Size(10,5), 0, 0, 360, black, -1, 8, 0 );
        ellipse( img, Point(dx+150, dy+150), Size(40,10), 0, 0, 360, black, -1, 8, 0 );
        ellipse( img, Point(dx+27, dy+100), Size(20,35), 0, 0, 360, white, -1, 8, 0 );
        ellipse( img, Point(dx+273, dy+100), Size(20,35), 0, 0, 360, white, -1, 8, 0 );
    }
    //show the faces
    namedWindow( "image", 1 );
    imshow( "image", img );

    //Extract the contours so that
    vector<vector<Point> > contours0;
    findContours( img, contours0, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

    std::cout << contours0.size() << std::endl;
    contours.resize(contours0.size());
    for( size_t k = 0; k < contours0.size(); k++ )
        approxPolyDP(Mat(contours0[k]), contours[k], 3, true);

    namedWindow( "contours", 1 );

    Mat cnt_img = Mat::zeros(w, w, CV_8UC3);
    int _levels = levels - 3;
    drawContours( cnt_img, contours, -1, Scalar(128,255,255),
                  1, LINE_AA, hierarchy, std::abs(2) );

    imshow("contours", cnt_img);
    waitKey();

    return;
}
