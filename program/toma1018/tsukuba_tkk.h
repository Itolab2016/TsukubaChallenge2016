#ifndef KANSU_H
#define KANSU_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <string.h>

int get_navi_data(char *motion_senser_pointer,char *save_point);	//航法データをファイルに記録
int save_wp(char *motion_sensor_pointer,char *save_point);		//wpとなる緯度経度を記録

#endif
