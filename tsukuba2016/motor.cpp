#include"motor.h"
#include "joystick.h"
#include "tsukuba_time.h"

using namespace std;

static int fd_L,fd_R;

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


static void serialA(int fd){
    if(fd<0){
	cout<<"no"<<endl;
	exit(1);
	}
    char bufA[4];
    char strA[4];
    sprintf(strA, "350\r");
    strcpy(bufA,strA);
    write(fd, bufA , sizeof(bufA));
}

static void serialB(int fd){
    if(fd<0){
	cout<<"no"<<endl;
	exit(1);
	}
    char bufB[4];
    char strB[4];
    sprintf(strB, "800\r");
    strcpy(bufB,strB);
    write(fd, bufB , sizeof(bufB));
}

int motor_open(void){
	fd_L = open(SERIAL_PORT1,O_RDWR);
	fd_R = open(SERIAL_PORT2,O_RDWR);
	serial_init(fd_L);
	serial_init(fd_R);
	if(fd_L<1 or fd_R<1){
		cout<<"moter_error"<<endl;
		exit(1);
		return 0;
	}
}

int motor_close(void){
	close(fd_L);
	close(fd_R);
}

int motor_remote(robot_t *IH){

	IH->motor_v=get_joy_stickY()*MAX_V;
	IH->motor_o=-get_joy_stickX()*MAX_OMEGA;
}

int motor_command(robot_t *IH){
	int L,R;
	float v=IH->motor_v;
	float omega=IH->motor_o;	

	L=( ( v - omega ) + 1.0 )*500;
	R=( ( v + omega ) + 1.0 )*500;
	
	if ( L > 900.0 ) {
		L = 900.0;
	}
	if ( L < 100.0 ) {
		L = 100.0;
	}
	if ( R > 900.0 ) {
		R = 900.0;
	}
	if ( R < 100.0 ) {
		R = 100.0;
	}
	serial(fd_L,buf1,str1,L);
	serial(fd_R,buf2,str2,R);
	IH->motor_l=L;
	IH->motor_r=R;
		//cout<<L<<"___"<<R<<endl;
	}
