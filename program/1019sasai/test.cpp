#include"camera.h"
#define SAVE "/home/ubuntu/Desktop/img/"
char file[]=SAVE;
int main (){
	camera_open();
	capture(file);
}

