#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

RNG rng(1);

Mat warhol(Mat src, int K, int blurSize) {
  Mat img, bestLabels, centers, clustered;
  Vec3b colors[K];

  //Blur the image
  blur(src, img, Size(blurSize, blurSize));

  //Create samples
  Mat samples = img.reshape(1, img.rows * img.cols);
  samples.convertTo(samples, CV_32F);

  //K-Means clustering
  kmeans(samples, K, bestLabels, TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);


  //Select a random palette
  for(int i = 0; i < K; i ++) {
    Vec3b color = Vec3b( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    colors[i] = color;
  }

  //Draw the new image
  clustered = Mat(img.size(), img.type());
  for(int i = 0; i < img.cols*img.rows; i++) {
    clustered.at<Vec3b>(i/img.cols, i%img.cols) = colors[bestLabels.at<int>(0,i)];
  }

  return clustered;
}

Mat makePanel(Mat src, int rows, int cols) {
  Mat dst = Mat(src.rows * rows, src.cols * cols, src.type());
  Mat trgt;
  for(int i = 0; i < rows; i ++) {
    for (int j = 0; j < cols; j ++) {
      warhol(src, 8, 5).copyTo(dst(Rect(j * src.cols, i * src.rows, src.cols, src.rows)));
      //trgt = warhol(src, 8, 5);
    }
  }
  return dst;
}

int main( int argc, char** argv )
{
  Mat src;
  int rows, cols;

  if( argc != 5)
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

  stringstream rowstream(argv[3]);
  rowstream >> rows;
  stringstream colstream(argv[4]);
  colstream >> cols;

  imwrite(argv[2], makePanel(src, rows, cols));
  return 0;
}