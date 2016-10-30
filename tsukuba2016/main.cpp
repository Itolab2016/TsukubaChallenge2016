#include "motor.h"
#include "joystick.h"
#include "tsukuba_time.h"
#include "camera.h"
#include "tsukuba_tkk.h"
#include "tsukuba_urg.h"
#include "navigation.h"
#include "avoid.h"
#include "localization.h"
#include "tsukuba_def.h"


#define SAVE_PHOTO "/home/itolab/Desktop/1028sasai/test_img/"
#define SAVE_TXT "/home/itolab/Desktop/1028sasai/test_txt/"
//#define SAVE_CAMERA_TXT "/home/ubuntu/Desktop/data/"
#define SAVE_TIME "/media/ubuntu/Transcend/1027data/"


static char way[]="way";
static char noway[]="noway";

int main(int argc, char *argv[]){
	int count=0;
	float v,omega;
	double scale=100;
	double latitude,latitude_goal,longitude,longitude_goal;
	int button;
	vector<float> way_time;
	vector<float> auto_time;
	char save_photo[]=SAVE_PHOTO;
	char save_txt[]=SAVE_TXT;
	char save_time[]=SAVE_TIME;
//	camera_open();
	motor_open();
	joy_open();
	open_TKK(argc, argv);
	cout<<"TKK_open"<<endl;
	//open_URG(argc, argv);
	cout<<"URG_open"<<endl;
	reset_time();
	cout<<"start"<<endl;
while(1){
	count=0;
	joy_read();
	button=get_joy_button ();
	if(button==14)break;
	if(button==12)//自律走行
	{
		set_waypoint();
		reset_time();
		while(1)
		{
			joy_read();
			if(on2Hz()==1)
				{
					save(save_time,noway,auto_time);
/*					capture2(save_photo);
					
					if(count!=0)
						{
						localization();//未完成
						axis_trarnsform();//未完成
						sfm(save_photo,save_txt,scale);
					}*/
				count++;
				}
	
			if(on100Hz()==1)
				{
					save(save_time,noway,auto_time);
					//get_urg_data();
					//avoid_decide();//未完成
					get_navi_data(argc, argv,&latitude,&longitude,&latitude_goal,&longitude_goal);
					move(latitude,latitude_goal,longitude,longitude_goal,&omega);
					//navigation();//未完成
					motor_command(v,omega);
				}
			if(button==3)
				{
					cout<<"break"<<endl;
					break;
				}
		}
	}
	if(button==15)//手動走行
	{
		reset_time();
		cout<<"data_pick_mode"<<endl;
		while(1)
		{
			joy_read();
			button=get_joy_button ();
			motor_remote(v,omega);
			motor_command(v,omega);

			

			if(button==3)
			{
				cout<<"break"<<endl;
				break;
			}

			
			if(on2Hz()==1)
			{
				save(save_time,noway,auto_time);
			//	capture(save_photo);
			//	cout<<"ok"<<endl;
				get_navi_data(argc, argv,latitude,longitude,latitude_goal,longitude_goal);
				//get_urg_data();
			}

			if(button==13){
				save(save_time,way,way_time);
			//	save_wp(argc, argv);
				cout<<"way_get"<<endl;
			}
			
		}
	}

	}
	v=0;
	omega=0;
	motor_command(v,omega);
	motor_close();
}	
