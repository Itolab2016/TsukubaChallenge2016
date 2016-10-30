#ifndef TSUKUBA_DEF_H
#define TSUKUBA_DEF_H

//using namespace std;

/*デバイス設定*/
#define TKK "/dev/SERIAL_TKK"
#define TKK_BAUD_RATE    B921600              // RS232C通信ボーレート
#define TKK_BUFF_SIZE    4096                 // 適当

#define MAX_V 0.75 //m/s
#define MAX_OMEGA 0.5 //m/s
#define SERIAL_PORT1 "/dev/MOTOR_R"
#define SERIAL_PORT2 "/dev/MOTOR_L" 


/*txt保存 読み込み*/
#define DATA1 "/media/ubuntu/itolab/1030data/idokeido.txt"
#define DATA2 "/media/ubuntu/itolab/1030data/kouho.txt"
#define DATA3 "/media/ubuntu/itolab/1030data/manualidokeido.txt"
#define DATA4 "/media/ubuntu/itolab/1030data/latitude_goal.txt"
#define DATA5 "/media/ubuntu/itolab/1030data/longitude_goal.txt"
#define DATA6 "/media/ubuntu/itolab/1030data/takasa_goal.txt"

#define READ1 "/media/ubuntu/itolab/1030data/latitude_goal.txt"
#define READ2 "/media/ubuntu/itolab/1030data/longitude_goal.txt"
#define READ3 "/media/ubuntu/itolab/1030data/takasa_goal.txt"


/*--- 定数 */
#define	MAXN	12

/*--- 2乗、3乗 */
#define SQR(x)		((x)*(x))
#define CUB(y)		((y)*(y)*(y))

/*--- WGS84座標パラメータ */
#define	PI				3.1415926535898
#define A					6378137.0				/* Semi-major axis */ 
#define ONE_F			298.257223563   /* 1/F */
#define B					(A*(1.0 - 1.0/ONE_F))
#define E2				((1.0/ONE_F)*(2-(1.0/ONE_F)))
#define ED2				(E2*A*A/(B*B))
#define NN(p)			(A/sqrt(1.0 - (E2)*SQR(sin(p*PI/180.0))))

#define C					2.99792458E+08  /* Speed of light */
#define MU				3.986005E+14    /* Earth's universal gravity */
#define	OMEGADOTE	7.2921151467E-05 /* Earth's rotation rate (rad/s) */
#define F					-4.442807633E-10 /* F sec/m^(1/2) */



/*--- ベクトルの定義 */
typedef struct {
	int n;            /* size of vector */
	double a[MAXN];   /* elements of vector */
	int err;          /* err=1: error */ 
} vectar;

/*--- 行列の定義 */
typedef struct {
	int n;            		/* size of raw */
	int m;            		/* size of columb */
	double a[MAXN][MAXN]; /* elements of matrix */
	char message[80];     /* error report */
	int err;							/* err=1: error */
} matrix;

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
