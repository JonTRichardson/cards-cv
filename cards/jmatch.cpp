// jmatch.cpp.  Version 0 of this file was copied from   
//         https://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/template_matching/template_matching.html
//         Ver 1.2 : experiments with grayscale. 
//////////////////////////////////////
#define JR_MATCH_CPP_VERSION   "ver 1.2wip"

// TODO : Reenable these warnings and fix the code.
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

#include "jutils.hpp"

//using namespace std;
using std::cout;
using std::endl;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// Function Headers
void MatchingMethod( int, void* );

/** @function main */
int main( int argc, char** argv )
{
  
  cout <<JR_MATCH_CPP_VERSION << endl;

  if (argc<3)
  {
	cout << "not enough args. argc="<<argc<<endl;
	exit(1);
  }
  cout << "Image file (argv[1]) : " << argv[1] << endl; 
  cout << "Pattern file (argv[2]) : " << argv[2] << endl; 

  //cout << "CV_LOAD_IMAGE_COLOR=" << CV_LOAD_IMAGE_COLOR << endl;
  //cout << "CV_LOAD_IMAGE_GRAYSCALE=" << CV_LOAD_IMAGE_GRAYSCALE << endl;

  /// Load image and template
  //img = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
  img = imread( argv[1], CV_LOAD_IMAGE_COLOR );
  //templ = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );
  templ = imread( argv[2], CV_LOAD_IMAGE_COLOR );

  /// Create windows
  namedWindow( image_window, CV_WINDOW_AUTOSIZE );
  namedWindow( result_window, CV_WINDOW_AUTOSIZE );

  /// Create Trackbar
  char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  //createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

  MatchingMethod( 0, 0 );

  waitKey(0);
  return 0;
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_rows, result_cols, CV_32FC1 );

  /// Do the Matching and Normalize

  j_print_matchMethod( match_method );

  matchTemplate( img, templ, result, match_method );
  //normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
  cout << "minVal=" << minVal << endl;
  cout << "maxVal=" << maxVal << endl;

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
  {
    cout << "Minimizing." << endl;
    matchLoc = minLoc;
  }
  else
  {
    cout << "Maximizing." << endl;
    matchLoc = maxLoc;
  }

  /// Show me what you got
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

  imshow( image_window, img_display );
  imshow( result_window, result );

  return;
}

