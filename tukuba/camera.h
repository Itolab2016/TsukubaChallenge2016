#ifndef CAPTURE_H
#define CAPTURE_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "vo_features.h"

using namespace cv;
int camera_open();
int capture (VideoCapture cap,char *save_point);

#endif
