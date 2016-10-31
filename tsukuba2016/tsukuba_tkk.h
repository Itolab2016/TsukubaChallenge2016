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

#include <iterator>
#include <vector>
#include <algorithm>
#include "navigation.h"
#include "tsukuba_def.h"


int open_TKK(void);			//TKKデバイスをオープン

int get_navi_data(robot_t *tkk);		//航法データをファイルに記録

int save_wp(robot_t *tkk);			//wpとなる緯度経度を記録

#endif
