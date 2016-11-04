#ifndef TSUKUBA_TIME_H
#define TSUKUBA_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "tsukuba_def.h"

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

int on100Hz(void);		//0.01秒経った時1を返す
int on2Hz(void);		//0.5秒経った時1を返す

int motor_50Hz(void);

double get_delta_time(void);	//時刻差を返す
double get_time(void);		//絶対時刻を返す

int fs_close(void);
int reset_time(void);		//時間をリセット
int time_stamp(robot_t *IH);	//時間経過を記録
int log(robot_t *IH);
int read_log(robot_t *IH,int *frame);
#endif

