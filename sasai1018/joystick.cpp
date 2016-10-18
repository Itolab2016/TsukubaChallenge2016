#include "joystick.h"

#define JOY_DEV "/dev/input/js0"

int joy_fd( -1 ) , num_of_axis( 0 ) , num_of_buttons( 0 );
char name_of_joystick[80];
vector<char> joy_button;
vector<int> joy_axis;
int count_button[17];
js_event js;
int joy_open()
{
	js_event js;
	if ( ( joy_fd = open( JOY_DEV, O_RDONLY ) ) < 0 ) {
		printf( "Failed to open %s" ,JOY_DEV );
		cerr << "Failed to open " << JOY_DEV << endl;
		return -1;
	}


	ioctl( joy_fd , JSIOCGAXES , &num_of_axis );
	ioctl( joy_fd , JSIOCGBUTTONS , &num_of_buttons );
	ioctl( joy_fd , JSIOCGNAME(80) , &name_of_joystick );

	joy_button.resize( num_of_buttons , 0 );
	joy_axis.resize( num_of_axis , 0 );

	printf( "Joystick: %s axis: %d buttons: %d\n" ,name_of_joystick ,num_of_axis ,num_of_buttons );

	fcntl( joy_fd, F_SETFL, O_NONBLOCK ); // using non-blocking mode
}

int get_joy_stickX (js_event js)
{
read ( joy_fd , &js , sizeof ( js_event ) );
	switch ( js.type & ~JS_EVENT_INIT ) {
		case JS_EVENT_AXIS:
			joy_axis[0] = js.value;
			return js.value;
			break;
		case JS_EVENT_BUTTON:
			joy_button[( int )js.number] = js.value;
			return 0;
			break;
	}
}

int get_joy_stickY (js_event js)
{
read ( joy_fd , &js , sizeof ( js_event ) );
	switch ( js.type & ~JS_EVENT_INIT ) {
		case JS_EVENT_AXIS:
			joy_axis[1] = js.value;
			return js.value;
			break;
		case JS_EVENT_BUTTON:
			joy_button[( int )js.number] = js.value;
			return 0;
			break;
	}
}

int get_joy_button (js_event js)
{
	read ( joy_fd , &js , sizeof ( js_event ) );
		switch ( js.type & ~JS_EVENT_INIT ) {
			case JS_EVENT_AXIS:
				joy_axis[( int )js.number] = js.value;
				return 0;
				break;
			case JS_EVENT_BUTTON:
				joy_button[( int )js.number] = js.value;
				return ( int )js.number;
				break;
	}
}

int main (){
	joy_open();
while(1){
	int c=get_joy_stickY(js);
	int g=get_joy_stickX(js);
	int s=get_joy_button (js);
	if(s!=0){
		cout<<s<<endl;
	}
	if(g!=0){
		cout<<g<<endl;
	}
	}
}

