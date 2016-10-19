#ifndef OBJECT_H
#define OBJECT_H
////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int object_open(char *filename);
int object_close(int fd);

////////////////////////////////////////
#endif
