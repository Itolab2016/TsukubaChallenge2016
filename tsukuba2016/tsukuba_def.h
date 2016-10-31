#ifndef TSUKUBA_DEF_H
#define TSUKUBA_DEF_H

/*デバイス設定*/
#define TKK "/dev/SERIAL_TKK"
#define TKK_BAUD_RATE    B921600              // RS232C通信ボーレート
#define TKK_BUFF_SIZE    4096                 // 適当

#define MAX_V 0.75 //m/s
#define MAX_OMEGA 0.5 //m/s
#define SERIAL_PORT1 "/dev/MOTOR_R"
#define SERIAL_PORT2 "/dev/MOTOR_L" 


/*txt保存 読み込み*/
#define LOGFILE "/media/ubuntu/itolab/log/test.log"

#define GPSDATA "/media/ubuntu/itolab/1030data/manualidokeido.txt"


#define SAVE_IMG "/home/itolab/Desktop/1028sasai/test_img/"


#define READ1 "/media/ubuntu/itolab/1030data/latitude_goal.txt"
#define READ2 "/media/ubuntu/itolab/1030data/longitude_goal.txt"
#define READ3 "/media/ubuntu/itolab/1030data/takasa_goal.txt"

/*カメラ情報*/
#define CAMERA 440.9741,0,290.2624,0,443.2639,242.4028,0,0,1
#define DISTORTION -0.39703,0.14661,0.001369,-0.0075874,-0.016642

typedef struct{

	double x,y,z;

} point3d_t;


typedef struct {

	float time;			//0.時間
	double lat;			//1.緯度
	double lon;			//2.経度
	float vx,vy,vz;			//3.速度
	float accelx,accely,accelz; 	//4.加速度
	float angx,angy;		//5.角度
	float angvx,angvy,angvz; 	//6.角速度
	double height;			//7.高度
	float tbearing; 		//8.真方位角
	double scale;			//9.スケール
	int motor_l,motor_r;		//10.モーターへの指令
	float motor_v,motor_o;		//11.航法指令
	int mode;			//12.モード
	char image[80];			//13.画像名
	point3d_t img_pt[2000];		//14.カメラ点群
	unsigned int urg_pt[1081];	//15.URG点群	
	double lat_goal,lon_goal;
	

} robot_t;



#endif
