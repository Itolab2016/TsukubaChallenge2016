#include "joystick.h"

#define MAX_V 0.3
#define JOY_DEV "/dev/input/js0"

int joy_fd( -1 ) , num_of_axis( 0 ) , num_of_buttons( 0 );
char name_of_joystick[80];
vector<char> joy_button;
vector<int> joy_axis;
int count_button[17];
float x;
float y;
int L,R;
js_event js;
int joy_open(void)
{
	if ( ( joy_fd = open( JOY_DEV, O_RDONLY ) ) < 0 ) 
	{
		printf( "Failed to open %s" ,JOY_DEV );
		cerr << "Failed to open " << JOY_DEV << endl;
		exit(1);
		return -1;
	}


	ioctl( joy_fd , JSIOCGAXES , &num_of_axis );
	ioctl( joy_fd , JSIOCGBUTTONS , &num_of_buttons );
	ioctl( joy_fd , JSIOCGNAME(80) , &name_of_joystick );

	joy_button.resize( num_of_buttons , 0 );
	joy_axis.resize( num_of_axis , 0 );

	printf( "Joystick: %s axis: %d buttons: %d\n" ,name_of_joystick ,num_of_axis ,num_of_buttons );

	fcntl( joy_fd, F_SETFL, O_NONBLOCK ); // using non-blocking mode
	for(int i=0;i<=num_of_buttons;i++){
		read ( joy_fd , &js , sizeof ( js_event ) );
		}

}


float joy_read (void)
{
	read ( joy_fd , &js , sizeof ( js_event ) );
}
float get_joy_stickX (void)
{
	//read ( joy_fd , &js , sizeof ( js_event ) );
	switch ( js.type & ~JS_EVENT_INIT ) {
		case JS_EVENT_AXIS:
			joy_axis[( int )js.number] = js.value;
			return -joy_axis[0]/32768.0;//MAX32768.0 m/s 
			break;
		case JS_EVENT_BUTTON:
			joy_button[( int )js.number] = js.value;
			return 0;//( int )js.number;
			break;
	}
}

float get_joy_stickY (void)
{
	//read ( joy_fd , &js , sizeof ( js_event ) );
	switch ( js.type & ~JS_EVENT_INIT ) {
		case JS_EVENT_AXIS:
			joy_axis[( int )js.number] = js.value;
			return -joy_axis[1]/32768.0;
			break;
		case JS_EVENT_BUTTON:
			joy_button[( int )js.number] = js.value;
			return 0;//( int )js.number;
			break;
	}
}

int get_joy_button (void)
{
	//read ( joy_fd , &js , sizeof ( js_event ) );
		switch ( js.type & ~JS_EVENT_INIT ) {
			case JS_EVENT_BUTTON:
				if(js.value==1){
					joy_button[( int )js.number] = js.value;
					return ( int )js.number;
					break;
				}
				else return 0;
	}
}


