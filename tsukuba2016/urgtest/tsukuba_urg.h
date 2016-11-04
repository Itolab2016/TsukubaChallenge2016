#ifndef GET_URG_DATA
#define GET_URG_DATA

#include "tsukuba_def.h"
#include "Urg_driver.h"
#include "math_utilities.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>


int open_URG(void);
int get_urg_data(robot_t* robo);

#endif
