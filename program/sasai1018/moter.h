#ifndef MOTER_H
#define MOTER_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <math.h>
#include <termios.h>
#include <strings.h>
#include <iterator>
#include <algorithm>
#include <sysexits.h>
#include<string.h>

using namespace std;

int moter_comnand(float v,float omega);
#endif
