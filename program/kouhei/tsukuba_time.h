#ifndef TSUKUBA_TIME_H
#define TSUKUBA_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

int on100Hz(void);		//0.01秒経った時1を返す
int on2Hz(void);		//0.5秒経った時1を返す

double get_delta_time(void);	//時刻差を返す
double get_time(void);		//絶対時刻を返す

int reset_time(void);		//時間をリセット
int save(char *save_point,char *name , vector<float>& all_time);	//時間経過を記録


#endif

