#include"capture.h"
VideoCapture cap(0);
char file[]=SAVE;
int main()
{

	camera_open();
	capture(cap,file);

}
