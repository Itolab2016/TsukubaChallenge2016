#include"motor.h"
#include"joystick.h"

int main(){
	float v,omega;
	int button;
	joy_open();
	motor_open();
	while(1){
		joy_read();
		button=get_joy_button ();
		motor_remote(v, omega);
		motor_comnand(v,omega);
		 if(button==3)
                        {
                                cout<<"break"<<endl;
                                break;
                        }

		//cout<<v<<"__"<<omega<<endl;
	}
}
