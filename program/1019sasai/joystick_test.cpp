#include"joystick.h"
int main(){
	joy_open();
	while(1){
//		float a=get_joy_stickY ();
		float a=get_joy_button ();
			if(a!=0){
				if(a==3){
//				if(a>0.9){
				cout<<"end"<<endl;
				break;
				}
				cout<<a<<endl;
				}
		}
}

