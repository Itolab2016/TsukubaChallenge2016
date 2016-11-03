#include <stdio.h>

int main(void)
{
  int a=1;
  for(int i=0; i<10; i++){
    printf("%d,%d,%d,%d,%d,%f,%f,%f,%f,hoge%02d\n",
      a++, a++, a++, a++, a++, (float)a++, (float)a++, (float)a++, (float)a++, a++);
  }
}
