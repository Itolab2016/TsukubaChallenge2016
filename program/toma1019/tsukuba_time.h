#ifndef KANSU_H
#define KANSU_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>
#include <string.h>


int on100Hz(void);		//0.01秒経った時1を返す
int on2Hz(void);		//0.5秒経った時1を返す

static double get_delta_time(void);	//時刻差を返す
static double get_time(void);	//絶対時刻を返す

int reset_time(void);


#endif

