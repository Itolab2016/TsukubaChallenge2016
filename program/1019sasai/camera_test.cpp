#include"camera.h"

char file[]="/media/itolab/disk2/work";
int main (){
	camera_open();
	for(int i=0;i<11;i++){
	capture(file);
	}
}

