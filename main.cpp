#include <opencv2/opencv.hpp>
#include "stdio.h"

using namespace cv;
using namespace std;
#define WINDOW_NAME "Drawing Rectangle"

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& img, Rect box);

Rect g_rectangle;
bool g_bDrawingBox = false;

int main(int argc, char** argv) {
	Mat img = imread(argv[1]);
	namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
  setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*) &img);
  imshow(WINDOW_NAME, img);
  waitKey();
  return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
	Mat& image = *(Mat*) param;
  switch (event) {
  	case EVENT_MOUSEMOVE: {    // When mouse moves, get the current rectangle's width and height
  		if (g_bDrawingBox) {
  			g_rectangle.width = x - g_rectangle.x;
  			g_rectangle.height = y - g_rectangle.y;
        DrawRectangle(image, g_rectangle);
  		}
      break;
  	}
  	case EVENT_LBUTTONDOWN: {  // when the left mouse button is pressed down,
      g_bDrawingBox = true;
      g_rectangle = Rect(x, y, 0, 0);
      break;
  	}
  	case EVENT_LBUTTONUP: {   //when the left mouse button is released,
  		g_bDrawingBox = false;
      break;
  	}
	}
}

void DrawRectangle(Mat& img, Rect box){
  Mat zeros = Mat::zeros(img.size(), img.type());
	rectangle(zeros, box.tl(), box.br(), Scalar(0,255,0));
  Mat res;
  add(img, zeros, res);
  imshow(WINDOW_NAME, res);
}
