#include "camera.h"
#include "tsukuba_time.h"

int main()
{
  robot_t robo;

  camera_open();
  capture(&robo);
  
  log(&robo);


}
