#include "tsukuba_urg.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  robot_t robo;
  open_URG();
  system("aplay -q /home/ubuntu/Desktop/voice/urg.wav");
  system("aplay -q /home/ubuntu/Desktop/voice/open.wav");
  

  for(int i=0;i<10;i++){
    get_urg_data(&robo);
    printf("%d\n",i);
  }
  //urg_close();
}  
