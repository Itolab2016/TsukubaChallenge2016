#include"motor.h"
#include"joystick.h"

int main(){
	float v,omega;
	joy_open();
	motor_open();
	motor_remote(v, omega);
	motor_comnand(v,omega);
}
