#include "object.h"

int object_open(char *filename)
{
  int fd;
  if((fd=open(filename, O_RDWR))==-1){
    printf("%s open error !\n",filename);
    exit(1);
  }
  return fd;
}

int object_close(int fd)
{
  if(close(fd)==-1){
    printf("File descripter No.=%d close error !\n",fd);
  }
  return 0;
}
