#include"joystick.h"

main(){
	joy_open();
	while(1){
		joy_read();
		if(sikaku()==1){
			cout<<"sikaku"<<endl;
		}
		
		if(start()==1){
			cout<<"start"<<endl;
		}
		
		if(maru()==1){
			cout<<"maru"<<endl;
		}

		if(sankaku()==1){
			cout<<"sankaku"<<endl;
		}

		if(batu()==1){
			cout<<"batu"<<endl;
		}
//	cout<<get_joy_stickX()<<"_"<<get_joy_stickY()<<endl;

	}
}
