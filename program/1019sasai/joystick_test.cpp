#include"joystick.h"
int main(){
	joy_open();
	while(1){
		float a=get_joy_stickY ();
			if(a!=0){
				if(a>0.9){
				cout<<"end"<<endl;
				break;
				}
				cout<<a<<endl;
				}
		}
}

