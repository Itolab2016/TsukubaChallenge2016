#ifndef AVOID_H
#define AVOID_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "tsukuba_def.h"

#define NAVIGATION 0
#define CWTURN 1
#define CCWTURN -1
#define STOP 2

using namespace std;

int avoid_decide(robot_t *robo);

#endif
