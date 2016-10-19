#include "decode_test.h"
#include "object.h"

int main(void)
{
  char fname[]="gps.txt";
  int fd;
  int len;

  fd=object_open(fname);
    
  decode_test(fd);

  object_close(fd);
}
