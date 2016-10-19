#include"motor.h"
#include "joystick.h"

#define MAX_V 0.5 //m/s
#define MAX_OMEGA 0.5 //m/s
#define SERIAL_PORT1 "/dev/moterL"
#define SERIAL_PORT2 "/dev/moterR" 

static int fd_L,fd_R;
static float L,R;
static char buf1[10];
static char str1[10];
static char buf2[10];
static char str2[10];


static void serial_init(int fd)
{
  struct termios tio;
  memset(&tio,0,sizeof(tio));
  tio.c_cflag = CS8 | CLOCAL | CREAD;
  tio.c_cc[VTIME] = 100;
  // ボーレートの設定
  cfsetispeed(&tio,B57600);
  cfsetospeed(&tio,B57600);
  // デバイスに設定を行う
  tcsetattr(fd,TCSANOW,&tio);
}

static void serial(int fd,char* buf,char* str,int send){
    if(fd<0){
	cout<<"no"<<endl;
	exit(1);
	}
    sprintf(str, "%d\r", send);
    strcpy(buf,str);
    write(fd, buf , sizeof(buf));
}

int motor_open(void){
	fd_L = open(SERIAL_PORT1,O_RDWR);
	fd_R = open(SERIAL_PORT2,O_RDWR);
	serial_init(fd_L);
	serial_init(fd_R);
	if(fd_L<1 or fd_R<1){
		cout<<"moter_error"<<endl;
		return 0;
	}
}

int motor_close(void){
	close(fd_L);
	close(fd_R);
}

int motor_remote(float &v, float &omega){
v=get_joy_stickY()*MAX_V;
omega=get_joy_stickX()*MAX_OMEGA;
}

int motor_comnand(float v, float omega){
	
	L=( ( v - omega ) + 1.0 )*500;
	R=( ( v + omega ) + 1.0 )*500;

	serial(fd_L,buf1,str1,L);
	serial(fd_R,buf2,str2,R);
}
