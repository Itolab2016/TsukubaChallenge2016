#ifndef CAPTURE_H
#define CAPTURE_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>
#include <stdio.h>


using namespace cv;
int camera_open(void);
int capture (char *save_point);

#endif
