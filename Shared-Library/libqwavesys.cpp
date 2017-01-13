#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/core/fast_math.hpp"

#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

#ifdef __cplusplus
extern "C"
{
#endif
    int webcam_open( int w, int h );
    void webcam_close();
    int webcam_getimagedata(int *data, uchar *data8bit);
    int webcam_getimagesize(int *img_rows, int *img_cols);
    int color_detect(uchar *data,uchar Alow_h,uchar Alow_s,uchar Alow_v,uchar Aupp_h,uchar Aupp_s,uchar Aupp_v,uchar Blow_h,uchar Blow_s,uchar Blow_v,uchar Bupp_h,uchar Bupp_s,uchar Bupp_v,int *found);
    void color_found(int *data);
    int getimagefilesize(char *filename, int *img_rows, int *img_cols);
    int getimagedatafromfile(char *filename, int *data, uchar *data8);
    int MyPatternMatch(uchar *img, uchar *templ, int img_cols, int img_rows, int templ_cols, int templ_rows, int *xL, int *xR, int *yT, int *yB, double *score);
#ifdef __cplusplus
}
#endif


class myclass{
public:
    Mat img;
    VideoCapture capture;
    std::vector<Vec3f> circles;
    int readimage() {
    	capture.read( img );
        if(!img.data)
            return -1;
        return 0;
    }
    void close() {
    	capture.~VideoCapture();
    }
};

myclass mywebcam;

int webcam_open( int w, int h ) {
    mywebcam.capture.open( -1 );
    mywebcam.capture.set(CAP_PROP_FRAME_WIDTH, w);
    mywebcam.capture.set(CAP_PROP_FRAME_HEIGHT, h);
    if( !mywebcam.capture.isOpened() )
    	return -1;
    return 0;
}

void webcam_close() {
	mywebcam.close();
}

int webcam_getimagesize(int *img_rows, int *img_cols)
{
    int error_code = mywebcam.readimage();
    if(error_code != 0)
        return -1;
    (*img_rows) = mywebcam.img.rows;
    (*img_cols) = mywebcam.img.cols;
    return 0;
}

int webcam_getimagedata(int *data, uchar *data8bit)
{
    Mat img24_to_LV(mywebcam.img.rows, mywebcam.img.cols, CV_8UC4, &data[0]);
    Mat img8_to_LV(mywebcam.img.rows, mywebcam.img.cols, CV_8U, &data8bit[0]);
    cvtColor(mywebcam.img, img24_to_LV, CV_BGR2BGRA );
    cvtColor(mywebcam.img, img8_to_LV, CV_BGR2GRAY );

    return 0;
}

int getimagefilesize(char *filename, int *img_rows, int *img_cols) {
	Mat img = imread( filename, 1 );
	if( img.empty() ) return -1;
	(*img_rows) = img.rows;
	(*img_cols) = img.cols;

	return 0;
}

int getimagedatafromfile(char *filename, int *data, uchar *data8) {
	Mat img = imread( filename, 1 );
	Mat img24_to_LV(img.rows, img.cols, CV_8UC4, &data[0]);
	Mat img8_to_LV(img.rows, img.cols, CV_8U, &data8[0]);
	cvtColor(img, img24_to_LV, CV_BGR2BGRA );
	cvtColor(img, img8_to_LV, CV_BGR2GRAY );

	return 0;
}

int color_detect(uchar *data,uchar Alow_h,uchar Alow_s,uchar Alow_v,uchar Aupp_h,uchar Aupp_s,uchar Aupp_v,uchar Blow_h,uchar Blow_s,uchar Blow_v,uchar Bupp_h,uchar Bupp_s,uchar Bupp_v,int *found)
{
    Mat img_to_LV(mywebcam.img.rows, mywebcam.img.cols, CV_8U, &data[0]);
    //img_to_LV = img_to_LV > 128;

	Mat imgHSV;

	cvtColor(mywebcam.img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	Mat lower_red_hue_range;
	Mat upper_red_hue_range;
	//inRange(imgHSV, Scalar(0, 100, 100), Scalar(10, 255, 255), lower_red_hue_range);
	//inRange(imgHSV, Scalar(160, 100, 100), Scalar(179, 255, 255), upper_red_hue_range);
	inRange(imgHSV, Scalar(Alow_h, Alow_s, Alow_v), Scalar(Aupp_h, Aupp_s, Aupp_v), lower_red_hue_range);
	inRange(imgHSV, Scalar(Blow_h, Blow_s, Blow_v), Scalar(Bupp_h, Bupp_s, Bupp_v), upper_red_hue_range);
	Mat red_hue_image;
	addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, red_hue_image);
	GaussianBlur(red_hue_image, red_hue_image, Size(9, 9), 2, 2);

	HoughCircles(red_hue_image, mywebcam.circles, CV_HOUGH_GRADIENT, 1, red_hue_image.rows/8, 100, 20, 0, 0);

	(*found) = mywebcam.circles.size();

	// Note: For HSV, Hue range is [0,179], Saturation range is [0,255] and Value range is [0,255]
	Mat hsv_channels[3];
	split( red_hue_image, hsv_channels );
	img_to_LV = hsv_channels[0] & 255;

    return 0;
}

void color_found(int *data) {
	int ii=0;
	for(size_t current_circle = 0; current_circle < mywebcam.circles.size(); ++current_circle) {
		data[ii++] = round(mywebcam.circles[current_circle][0]);
		data[ii++] = round(mywebcam.circles[current_circle][1]);
		data[ii++] = round(mywebcam.circles[current_circle][2]);
	}
}

int MyPatternMatch(uchar *img, uchar *templ, int img_cols, int img_rows, int templ_cols, int templ_rows, int *xL, int *xR, int *yT, int *yB, double *score)
{
	// store images in Mat type
	Mat src_image(img_rows,img_cols,CV_8U,&img[0]);
	Mat templ_image(templ_rows,templ_cols,CV_8U,&templ[0]);

	// create result matrix
	Mat result;
	int result_cols =  src_image.cols - templ_image.cols + 1;
	int result_rows = src_image.rows - templ_image.rows + 1;
	result.create( result_cols, result_rows, CV_32FC1 );
	// match and normalize
	matchTemplate(src_image, templ_image, result, CV_TM_CCORR_NORMED);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	// Locate the best match
	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	rectangle( src_image, maxLoc, Point( maxLoc.x + templ_image.cols , maxLoc.y + templ_image.rows ), Scalar::all(0), 2, 8, 0 );

	// pass the pointer(s) to the bounding box value and match score
	(*xL) = maxLoc.x;
	(*xR) = maxLoc.x + templ_image.cols;
	(*yT) = maxLoc.y;
	(*yB) = maxLoc.y + templ_image.rows;
	(*score) = maxVal;

	return 0;
}
