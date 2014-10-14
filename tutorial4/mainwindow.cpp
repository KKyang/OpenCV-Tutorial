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

void MainWindow::on_actionHistogram_triggered()
{
    if(!mat.empty())
    {
        cv::split(mat,bgr_planes);
        int histSize = 256;

        /// Set the ranges ( for B,G,R) )
        float range[] = { 0, 256 } ;
        const float* histRange = { range };

        bool uniform = true;
        bool accumulate = false;

        cv::Mat b_hist, g_hist, r_hist;

        // Compute the histograms:
        cv::calcHist( &bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
        cv::calcHist( &bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
        cv::calcHist( &bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

        // Draw the histograms for B, G and R
        int hist_w = 512; int hist_h = 200;
        //cvRound: Rounds floating-point number to the nearest integer
        int bin_w = cvRound( (double) hist_w/histSize ); // x rescale

        //Create a new mat to hold histogram image
        cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

        // Normalize the result to [ 0, histImage.rows ]
        cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
        cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
        cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

        // Draw for each channel
        for( int i = 1; i < histSize; i++ )
        {
            //image, first point, second point, color of the line, thickness, line type, shift =0
            cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                                 cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                                 cv::Scalar( 255, 0, 0), 2, 8, 0  );
            cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                                 cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                                 cv::Scalar( 0, 255, 0), 2, 8, 0  );
            cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                                 cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                                 cv::Scalar( 0, 0, 255), 2, 8, 0  );
        }

        cv::namedWindow("calcHist Demo", cv::WINDOW_AUTOSIZE );
        cv::imshow("calcHist Demo", histImage );

        cv::waitKey(0);
    }
}

void MainWindow::on_actionHistogram_Equalization_triggered()
{
    if(!mat.empty())
    {
        cv::Mat src = mat;
        cv::Mat dst;
        // Convert to grayscale
        cv::cvtColor( src, src, cv::COLOR_BGR2GRAY );

        // Apply Histogram Equalization
        cv::equalizeHist( src, dst );

        // Display results
        cv::namedWindow( "Source image", cv::WINDOW_AUTOSIZE );
        cv::namedWindow( "Equalized Image", cv::WINDOW_AUTOSIZE );

        cv::imshow( "Source image", src );
        cv::imshow( "Equalized Image", dst );

        // Wait until user exits the program
        cv::waitKey(0);
    }
}
