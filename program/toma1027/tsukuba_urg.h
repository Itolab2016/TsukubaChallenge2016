#ifndef TSUKUBA_URG_H
#define TSUKUBA_URG_H

#include "Urg_driver.h"
#include "Connection_information.h"
#include "math_utilities.h"
#include <stdio.h>
#include <string>
#include <sysexits.h>
#include <math.h>
#include <iostream>
#include <fstream>


int open_URG(int argc, char *argv[]);
int get_urg_data();	//約1080この距離データを記録

#endif
