#ifndef NAVIGATION_H
#define NAVIGATION_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <fstream>


using namespace std;

int navigation(void);
void move(double &latitude,double &latitude_goal,double &longitude,double &longitude_goal,float &omega);
#endif
