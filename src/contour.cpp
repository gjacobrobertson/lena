#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

RNG rng(1);

Mat contour(Mat src) {
  Mat src_gray, src_bw, drawing;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  cvtColor(src, src_gray, CV_BGR2GRAY);
  adaptiveThreshold(src_gray, src_bw, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 3, 0);

  findContours(src_bw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  drawing = Mat::zeros(src_bw.size(), CV_8UC3);
  for(int i = 0; i < contours.size(); i ++) {
    int blue = 0;
    int green = 0;
    int red = 0;
    for(int j = 0; j < contours[i].size(); j++) {
      Point p = contours[i][j];
      Vec3b bgr = src.at<Vec3b>(p.y, p.x);
      blue += bgr[0];
      green += bgr[1];
      red += bgr[2];
    }
    red = red / float(contours[i].size());
    green = green / float(contours[i].size());
    blue = blue / float(contours[i].size());
    Scalar color = Scalar( blue, green, red );
    //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing, contours, i, color, CV_FILLED, CV_AA );
  }
  return drawing;
}

int main( int argc, char** argv )
{
  Mat src;
  int rows, cols;

  if( argc != 3)
  {
    cout <<" Usage: warhol ImageToWarhol FileToWrite Rows Columns" << endl;
    return -1;
  }

  //Load Image
  src = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
  if(! src.data )          // Check for invalid input
  {
    cout <<  "Could not open or find the image" << std::endl ;
    return -1;
  }

  imwrite(argv[2], contour(src));
  return 0;
}
