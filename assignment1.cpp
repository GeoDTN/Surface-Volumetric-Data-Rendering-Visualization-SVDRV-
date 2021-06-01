#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
int main( int argc, char** argv )
{
char* source_window = "Source image";
char* histogram = "histogram ";
Mat im,src;
/// Load image
im = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
Mat im_eq=im_eq.zeros(im.rows,im.cols,im.type());
if( !im.data )
{ return -1; }
int k = im.type();
Mat hist = hist.zeros(1,256,CV_32F);
for (int i=0; i<im.rows; i++)
{
for (int j=0; j<im.cols; j++)
{
(hist.at<float>(0,im.at<uchar>(i,j)))++;
}
}
for (int i=0; i<hist.cols; i++) //normalization
{
hist.at<float>(0,i)=hist.at<float>(0,i)/(im.rows*im.cols);
}
Mat hist_im = hist_im.zeros(512,256,CV_32F);
int i=0;
for (int i=0; i<hist_im.cols; i++)
{
for (int j=0; j<hist_im.rows-((int)(hist.at<float>(0,i)*512*10)); j++)
{
hist_im.at<float>(j,i)=255;
}
}
// cumulative function
Mat cumul = cumul.zeros(1,256,CV_32F);
for (int i=1; i<cumul.cols; i++){
cumul.at<float>(0,i)=cumul.at<float>(0,i-1)+ hist.at<float>(0,i);
}
//equalize
for (int i=0; i<im.rows; i++)
{
for (int j=0; j<im.cols; j++)
{
im_eq.at<uchar>(i,j) = cumul.at<float>(0,im.at<uchar>(i,j))*255;
}
}
namedWindow( source_window, CV_WINDOW_AUTOSIZE );
namedWindow( histogram, CV_WINDOW_AUTOSIZE );
namedWindow( "eq_image", CV_WINDOW_AUTOSIZE );
imshow( source_window, im);
imshow( histogram, hist_im);
imshow( "eq_image", im_eq);
for (int i=0; i<im.rows; i++)
{
for (int j=0; j<im.cols; j++)
{
(hist.at<float>(0,im_eq.at<uchar>(i,j)))++;
}
}
for (int i=0; i<hist.cols; i++) //normalization
{
hist.at<float>(0,i)=hist.at<float>(0,i)/(im.rows*im.cols);
}
Mat hist_im_eq = hist_im_eq.zeros(512,256,CV_32F);
for (int i=0; i<hist_im_eq.cols; i++)
{
for (int j=0; j<hist_im_eq.rows-((int)(hist.at<float>(0,i)*512*10)); j+
+)
{
hist_im_eq.at<float>(j,i)=255;
}
}
namedWindow( "hist_eq", CV_WINDOW_AUTOSIZE );
imshow( "hist_eq", hist_im_eq);
waitKey(0);
return 0;
}

