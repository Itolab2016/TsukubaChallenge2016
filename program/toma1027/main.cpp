#include"motor.h"
#include "joystick.h"
#include "tsukuba_time.h"
#include"camera.h"
#include "tsukuba_tkk.h"
#include "tsukuba_urg.h"


#define SAVE_PHOTO "/media/ubuntu/TRANSCEND/1027data/img"
//#define SAVE_CAMERA_TXT "/home/ubuntu/Desktop/data/"
#define SAVE_TIME "/media/ubuntu/Transcend/1027data/"


static char way[]="way";
static char noway[]="noway";

int main(int argc, char *argv[]){
	float v,omega;
	int button;
	vector<float> way_time;
	vector<float> auto_time;
	char save_photo[]=SAVE_PHOTO;
	char save_time[]=SAVE_TIME;
	camera_open();
	motor_open();
	joy_open();
	open_TKK(argc, argv);
	cout<<"TKK_open"<<endl;
	//open_URG(argc, argv);
//	cout<<"URG_open"<<endl;
	reset_time();
	cout<<"start"<<endl;
while(1){
	joy_read();
	button=get_joy_button ();
	if(button==14)break;
	if(button==15)
	{
		reset_time();
		cout<<"data_pick_mode"<<endl;
		while(1)
		{
			joy_read();
			button=get_joy_button ();
			motor_remote(v,omega);
			motor_comnand(v,omega);

			

			if(button==3)
			{
				cout<<"break"<<endl;
				break;
			}

			
			if(on2Hz()==1)
			{
				save(save_time,noway,auto_time);
				capture(save_photo);
			//	cout<<"ok"<<endl;
				get_navi_data(argc, argv);
				//get_urg_data();
			}

			if(button==13){
				save(save_time,way,way_time);
				save_wp(argc, argv);
				cout<<"way_get"<<endl;
			}
			
		}
	}

	}
	v=0;
	omega=0;
	motor_comnand(v,omega);
	motor_close();
}	
