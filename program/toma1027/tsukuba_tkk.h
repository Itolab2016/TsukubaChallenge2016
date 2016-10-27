#ifndef TSUKUBA_TKK_H
#define TSUKUBA_TKK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <time.h>

#include <sys/time.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "def01.h"
#include "str01.h"


int open_TKK(int argc, char *argv[]);			//TKKデバイスをオープン

int get_navi_data(int argc, char *argv[]);		//航法データをファイルに記録
int save_wp(int argc, char *argv[]);			//wpとなる緯度経度を記録

int axis_transform(void);				//座標変換

#endif
