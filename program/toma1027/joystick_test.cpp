#include"joystick.h"
int main(){
	joy_open();
	while(1){
		joy_read ();
		float respons=get_joy_stickX ();
			//if(respons!=0){
				if(respons>0.9)
				{
					cout<<respons<<endl;
					cout<<"end"<<endl;
					break;
				}
				cout<<respons<<endl;
			//	}
		}
}

