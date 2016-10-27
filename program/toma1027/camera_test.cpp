#include"camera.h"
#include"joystick.h"
#define SAVE "/home/ubuntu/Desktop/img/"
#define SAVE_TXT "/home/ubuntu/Desktop/data/"
char file0[]=SAVE;
char file1[]=SAVE_TXT;
double scale=100;
int main (){
	int count=0;
	camera_open();
	joy_open();
	while(1)
	{
		if(get_joy_button ()==12&&count==0)
		{
			cout<<"cap"<<endl;
			capture(file0);
			count++;
		}
		if(get_joy_button ()==13)
		{
			capture2(file0);
			cout<<"sfm_start"<<endl;
			sfm(file0,file1,scale);
			cout<<"sfm_ok"<<endl;	
		}
		if(get_joy_button ()==14)break;
	}
}
