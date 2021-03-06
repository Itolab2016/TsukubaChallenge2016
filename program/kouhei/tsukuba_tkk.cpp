#include "tsukuba_tkk.h"

#define TKK "/dev/SERIAL_TKK"
#define TKK_BAUD_RATE    B921600              // RS232C通信ボーレート
#define TKK_BUFF_SIZE    4096                 // 適当
#define SAVE "/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data"

using namespace std;

int TOMAfd; //global
int TOMAlen;

unsigned char TOMAbuffer[TKK_BUFF_SIZE];    // データ受信バッファ

int Counter1=1;
int Counter2=1;

int rcounter1=0;
int rcounter2=0;
int mojicount=0;

int *TOMAaddrX,*TOMAaddrY,*TOMAaddrZ,*TOMAaddrCRC;
long long *TOMAaddrido1,*TOMAaddrkeido1;
long long *TOMAaddrido2,*TOMAaddrkeido2;
int *TOMAaddrtakasa;

unsigned char *TOMAdummyX,*TOMAdummyY,*TOMAdummyZ,*TOMAdummyCRC;
unsigned char *TOMAdummyido1,*TOMAdummykeido1;
unsigned char *TOMAdummyido2,*TOMAdummykeido2;
unsigned char *TOMAdummytakasa;

int p=0;

double lat, lon, hig, lat_o, lon_o, hig_o;


ofstream GPSidokeido("/media/ubuntu/itolab/1029data2/idokeido.txt");		//outo
ofstream GPSKOUHO("/media/ubuntu/itolab/1029data2/kouho.txt");
ofstream GPSaccel("/media/ubuntu/itolab/1029data2/accel.txt");

ofstream GPSmanualidokeido("/media/ubuntu/itolab/1029data2/manualidokeido.txt"); //manual
ofstream GPSido("/media/ubuntu/itolab/1029data2/latitude_goal.txt");		
ofstream GPSkeido("/media/ubuntu/itolab/1029data2/longitude_goal.txt");
ofstream GPStakasa("/media/ubuntu/itolab/1029data2/takasa_goal.txt");

int TKK_serial(void);
vectar blh2ecef(double phi, double ramda, double height);
vectar ecef2blh(vectar ec);
int set_waypoint(void);

extern vectar blh2ecef(double, double, double);
extern vectar ecef2blh(vectar);
extern matrix matmat(matrix *, matrix *);
extern vectar matvec(matrix, vectar);

matrix ret_mat;
typedef double (*daryp)[MAXN][MAXN];
typedef double (dary)[MAXN][MAXN];

double abs1(double);

ifstream latifs("/home/ubuntu/Desktop/1028data/latitude_goal.txt");
ifstream lonifs("/home/ubuntu/Desktop/1028data/longitude_goal.txt");
ifstream takasaifs("/home/ubuntu/Desktop/1028data/takasa_goal.txt");

vector<double> latwaydata;
vector<double> lonwaydata;
vector<double> takasawaydata;

int open_TKK(int argc, char *argv[]){

	// デバイスファイル（シリアルポート）オープン
	TOMAfd = open(TKK,O_RDWR);
	if(TOMAfd<0){
		// デバイスの open() に失敗したら
		perror(argv[1]);
		exit(1);
	}
	TKK_serial();

}

int TKK_serial(void){

	struct termios tio;
	memset(&tio,0,sizeof(tio));
	tio.c_cflag = CS8 | CLOCAL | CREAD;
	tio.c_cc[VTIME] = 100;
	// ボーレートの設定
	cfsetispeed(&tio,TKK_BAUD_RATE);
	cfsetospeed(&tio,TKK_BAUD_RATE);
	// デバイスに設定を行う
	tcsetattr(TOMAfd,TCSANOW,&tio);


} 

vectar blh2ecef(double phi, double ramda, double height)
/* 緯度,経度,高さからECEF座標に変換 */
{
	vectar ecef;

	ecef.n = 3;
	ecef.a[0] = (NN(phi)+height)*cos(phi*PI/180)*cos(ramda*PI/180);
	ecef.a[1] = (NN(phi)+height)*cos(phi*PI/180)*sin(ramda*PI/180);
	ecef.a[2] = (NN(phi)*(1-E2)+height)*sin(phi*PI/180);

	return ecef;
}

vectar ecef2blh(vectar ec)
/* ECEF座標からWGS84の{緯度,経度,楕円体高}へ変換 */
{
	vectar blh;
	int i = 0;
	double phi, ramda, height, p; 
	double x, y, z;
	double sita;

	ec.n = 3; blh.n = 3;
	x = ec.a[0], y = ec.a[1], z = ec.a[2];

	p = sqrt(x*x + y*y);
	sita = (180/PI) * atan2(z*A, p*B);

/*--- 緯度 */
	phi = (180/PI) * atan2(z+ED2*B*(CUB(sin(sita*PI/180))),(p-E2*A*(CUB(cos(sita*PI/180)))));	

/*--- 経度 */
	ramda = (180/PI) * atan2(y,x);

/*--- 高さ */	
	height = (p / cos(phi*PI/180)) - NN(phi);   

	blh.a[0] = phi; blh.a[1] = ramda; blh.a[2] = height;
	return blh;
}

matrix rotx(double sita)
/* x軸回りのsita度の回転変換：右ねじの方向 */
{
	matrix rota;
	rota.n = rota.m = 3;

	rota.a[0][0] = 1;
	rota.a[0][1] = 0;
	rota.a[0][2] = 0;
	
	rota.a[1][0] = 0;
	rota.a[1][1] = cos(sita*PI/180.0);
	rota.a[1][2] = sin(sita*PI/180.0);
		
	rota.a[2][0] = 0;
	rota.a[2][1] = -sin(sita*PI/180.0);
	rota.a[2][2] = cos(sita*PI/180.0);
	
	return rota;
}

matrix roty(double sita)
{
	matrix rota;
	rota.n = rota.m = 3;
		
	rota.a[0][0] = cos(sita*PI/180.0);
	rota.a[0][1] = 0;
	rota.a[0][2] = -sin(sita*PI/180.0);
	
	rota.a[1][0] = 0;
	rota.a[1][1] = 1;
	rota.a[1][2] = 0;
		
	rota.a[2][0] = sin(sita*PI/180.0);
	rota.a[2][1] = 0;
	rota.a[2][2] = cos(sita*PI/180.0);

	return rota;
}
	
matrix rotz(double sita)
{
	matrix rota;
	rota.n = rota.m = 3;
	
	rota.a[0][0] = cos(sita*PI/180.0);
	rota.a[0][1] = sin(sita*PI/180.0);
	rota.a[0][2] = 0;
	
	rota.a[1][0] = -sin(sita*PI/180.0);
	rota.a[1][1] = cos(sita*PI/180.0);
	rota.a[1][2] = 0;
		
	rota.a[2][0] = 0;
	rota.a[2][1] = 0;
	rota.a[2][2] = 1;
	
	return rota;
}

vectar matvec(matrix inmat, vectar v1)
/*--- 行列とベクトルの積 */
{
	int i, j;
	vectar ret_v;

	for (i=0;i<MAXN;i++) ret_v.a[i]=0.0;
	ret_v.err = 0;
	if((inmat.n>MAXN)||(inmat.n<0)||(inmat.m>MAXN)||(inmat.m<0))
		ret_v.err=1;
	if((v1.n > MAXN) || (v1.n<0)) ret_v.err=1;
	if((v1.n) != (inmat.m)) ret_v.err=1;
	if(ret_v.err == 1){ ret_v.n=0; return ret_v; }
	ret_v.n=inmat.n;
	for (i=0;i<inmat.n;i++){
		for (j=0;j<inmat.m;j++) ret_v.a[i] = ret_v.a[i] + inmat.a[i][j] * v1.a[j];
	}
	return ret_v;
}

matrix matmat(matrix *m1, matrix *m2)
/*--- 行列の積 */
{
	int i, j, k, mcount;

   ret_mat.err = 0;
   if ((m1->n>MAXN)||(m1->n<0)||(m1->m>MAXN)||(m1->m<0)) ret_mat.err=1;
   if ((m2->n>MAXN)||(m2->n<0)||(m2->m>MAXN)||(m2->m<0)) ret_mat.err=1;

   if  ((m1->m) != (m2->n))  ret_mat.err=1;
   mcount = m1->m;
   if (ret_mat.err == 1){
      strcpy(ret_mat.message,"Something went wrong.");
			printf("Something went wrong!\n");
      ret_mat.n = 0;
      ret_mat.m = 0;
      return ret_mat; 
   }

   ret_mat.n = m1->n;
   ret_mat.m = m2->m;

   for (i=0;i<ret_mat.n;i++)  {
      for (j=0;j<ret_mat.m;j++) ret_mat.a[i][j]=0.0;
   }

   for (i=0;i<ret_mat.n;i++){
      for (j=0;j<ret_mat.m;j++){
	 			for (k=0;k<mcount;k++){
	    		ret_mat.a[i][j] += m1->a[i][k] * m2->a[k][j] ;
	 			}
      }
   }
   return ret_mat;
}

vectar ecef2enu(vectar dest, vectar origin)
/*--- ECEF座標を水平線座標(ENU)へ変換する */ 
{
	int i, j;
	vectar mov, ret, blh;
	matrix rotyp, rotzp1, rotzp2;
	matrix mat_conv1, mat_conv2;

	origin.n  = 3;		origin.err  = 0;	
	mov.n 	  = 3;		mov.err     = 0; 
	ret.n 	  = 3; 	ret.err     = 0; 

	blh = ecef2blh(origin);

	rotzp1 = rotz(90.0);
	rotyp  = roty(90.0 - blh.a[0]);
	rotzp2 = rotz(blh.a[1]);

	mat_conv1 = matmat(&rotzp1, &rotyp);
	mat_conv2 = matmat(&mat_conv1, &rotzp2);

	for(i=0;i<3;i++) mov.a[i] = dest.a[i] - origin.a[i];
	ret = matvec(mat_conv2, mov);
	return ret;
}

int get_navi_data(int argc, char *argv[],double &latitude,double &longitude,double &latitude_goal,double &longitude_goal){

	int i,k=1;
	int kouho=0,INS=0;

	float scale1;

	char str[1024];

	int takasa1;
	int accelX,accelY,accelZ;
	long long ido1,keido1;
	double ido3,keido3,ido4,keido4;
	double idoscale,keidoscale,takasa2;
	float aX,aY,aZ;

	float pi=3.1415926535897;

	TOMAaddrX=&accelX;
	TOMAaddrY=&accelY;
	TOMAaddrZ=&accelZ;

	TOMAaddrido1=&ido1;
	TOMAaddrkeido1=&keido1;
	TOMAaddrtakasa=&takasa1;

	TOMAdummyX= (unsigned char *)TOMAaddrX;
	TOMAdummyY= (unsigned char *)TOMAaddrY;
	TOMAdummyZ= (unsigned char *)TOMAaddrZ;

	TOMAdummyido1= (unsigned char *)TOMAaddrido1;
	TOMAdummykeido1= (unsigned char *)TOMAaddrkeido1;
	TOMAdummytakasa= (unsigned char *)TOMAaddrtakasa;

	for(i=0;i<=TOMAlen;i++){ //受信データ初期化
		TOMAbuffer[i]=0;
	}

	// ここで受信待ち
	TOMAlen=read(TOMAfd,TOMAbuffer,TKK_BUFF_SIZE);

	if(TOMAlen==0){
		// read()が0を返したら、end of file
		// 通常は正常終了するのだが今回は無限ループ
		//     continue;
	}
	if(TOMAlen<0){
		printf("%s: ERROR\n",argv[0]);
		// read()が負を返したら何らかのI/Oエラー
		perror("");
		exit(2);
	}
	// read()が正を返したら受信データ数

	// 受信したデータを 16進数形式で表示    
	for(i=0; i<TOMAlen; i++){
		unsigned char data=TOMAbuffer[i];
	//	printf("%02X ",TOMAbuffer[i]);

		//受信データは意味の塊ごとに先頭に16進数で　16 16 06 02　と言うデータがつくことになっているので
		//以下でそのデータを受信するごとに改行して表示するようになっている．
		switch(rcounter1){
			case 0:
				if (data==0x16)rcounter1++;
				else rcounter1=0;
				break;
			case 1:
				if (data==0x16)rcounter1++;
				else rcounter1=0;
				break;
			case 2:
				if (data==0x06)rcounter1++;
				else rcounter1=0;
				break;
			case 3:
				if (data==0x02){
			//		printf("%d %d\n",TOMAlen,mojicount);
			//		printf("\n");

					if(TOMAbuffer[i+7]==0x40){
						kouho=i+1;
					}
					else if(TOMAbuffer[i+7]==0x20){
						INS=i+1;
					//	printf("%d\n ",i);
					}
				
				}
				rcounter1=0;
				mojicount=0;
				break;
		}
		mojicount++;
	} 

	lat=0.0;
	lon=0.0;
	hig=0.0;

	if(TOMAbuffer[kouho+6]==0x40 && TOMAbuffer[INS+7+38]==0x04/* && TOMAbuffer[kouho+7]==0x48 && TOMAbuffer[INS+7]==0x30*/){ 
		//航法データ受け取っているか、GPSが有効であるか、INSデータと航法データが全部入っているか

		ido1=0.0;
		keido1=0.0;
		takasa1=0.0;

		for(i=0;i<=3;i++){  		//加速度を抽出

			*TOMAdummyX=TOMAbuffer[kouho+i+7+17];
			*TOMAdummyY=TOMAbuffer[kouho+i+7+21];
			*TOMAdummyZ=TOMAbuffer[kouho+i+7+25];
			*TOMAdummytakasa=TOMAbuffer[kouho+i+7+57];

			*TOMAdummyX++;
			*TOMAdummyY++;
			*TOMAdummyZ++;
			*TOMAdummytakasa++;
		}


		for(i=0;i<=7;i++){  		//緯度,経度を抽出

			*TOMAdummyido1=TOMAbuffer[kouho+i+7+41];
			*TOMAdummykeido1=TOMAbuffer[kouho+i+7+49];

			*TOMAdummyido1++;
			*TOMAdummykeido1++;


		}

		aX=accelX;
		aY=accelY;
		aZ=accelZ;

		aX=aX/(10*10*10);
		aY=aY/(10*10*10);
		aZ=aZ/(10*10*10);

		takasa2= (double)takasa1;
		takasa2=takasa2/(10*10*10*10);

		ido3= (double)ido1;		  //long→double
		keido3= (double)keido1;

		ido3=ido3*(180/pi);		  //ラジアン→度
		keido3=keido3*(180/pi);	

		ido3=ido3/(10*10*10*10*10*10*10*10*10);
		ido3=ido3/10;

		keido3=keido3/(10*10*10*10*10*10*10*10*10);
		keido3=keido3/10;

		ido3=latitude;
		keido3=longitude;
		lat_o=latitude_goal;
		lon_o=longitude_goal;

		lat=ido3;
		lon=keido3;
		hig=takasa2;

	//	printf("緯度1=%lf 経度1=%lf 高さ1=%lf\n",ido3,keido3,takasa2);
	//	fflush(stdout);


		//加速度データをtxt化
		sprintf(str,"%f %f %f",aX,aY,aZ);
		GPSaccel<<str<<endl;
				
		//緯度経度データをtxt化
		sprintf(str,"%d\t%lf\t%lf\t%d",Counter1++,ido3,keido3,k);
		GPSidokeido<<str<<endl;
						
		//航法データをtxt化
		for(i=0;i<=86;i++){
			sprintf(str,"%02X ",TOMAbuffer[kouho+i]);
			GPSKOUHO<<str;
		}
		GPSKOUHO<<endl;	

		scale1=0.0;

		return 1;


	}
	else return 0;

}


int save_wp(int argc, char *argv[]){

	int i,t,k=1;
	int kouho=0,INS=0;
	int rcounter=0;
	int takasa1;
	
	float scale1;

	char str[1024];

	long long ido1,keido1;
	double ido3,keido3,ido4,keido4,takasa2;
	double idoscale,keidoscale;

	float pi=3.1415926535897;

	TOMAaddrido2=&ido1;
	TOMAaddrkeido2=&keido1;
	TOMAaddrtakasa=&takasa1;

	TOMAdummyido2= (unsigned char *)TOMAaddrido2;
	TOMAdummykeido2= (unsigned char *)TOMAaddrkeido2;
	TOMAdummytakasa= (unsigned char *)TOMAaddrtakasa;

	for(i=0;i<=TOMAlen;i++){ //受信データ初期化
		TOMAbuffer[i]=0;
	}

	// ここで受信待ち
	TOMAlen=read(TOMAfd,TOMAbuffer,TKK_BUFF_SIZE);

	if(TOMAlen==0){
		// read()が0を返したら、end of file
		// 通常は正常終了するのだが今回は無限ループ
		//     continue;
	}
	if(TOMAlen<0){
		printf("%s: ERROR\n",argv[0]);
		// read()が負を返したら何らかのI/Oエラー
		perror("");
		exit(2);
	}
	// read()が正を返したら受信データ数

	// 受信したデータを 16進数形式で表示    
	for(i=0; i<TOMAlen; i++){
		unsigned char data=TOMAbuffer[i];
	//	printf("%02X ",TOMAbuffer[i]);

		//受信データは意味の塊ごとに先頭に16進数で　16 16 06 02　と言うデータがつくことになっているので
		//以下でそのデータを受信するごとに改行して表示するようになっている．
		switch(rcounter2){
			case 0:
				if (data==0x16)rcounter2++;
				else rcounter2=0;
				break;
			case 1:
				if (data==0x16)rcounter2++;
				else rcounter2=0;
				break;
			case 2:
				if (data==0x06)rcounter2++;
				else rcounter2=0;
				break;
			case 3:
				if (data==0x02){

			//		printf("\n");

					if(TOMAbuffer[i+7]==0x40){
						kouho=i+1;
					}
					else if(TOMAbuffer[i+7]==0x20){
						INS=i+1;
					//	printf("%d\n ",i);
					}
				
				}
				rcounter2=0;
				break;
		}
	} 

	if(TOMAbuffer[kouho+6]==0x40 && TOMAbuffer[INS+7+38]==0x04/* && TOMAbuffer[kouho+7]==0x48 && TOMAbuffer[INS+7]==0x30*/){ 
		//航法データ受け取っているか、GPSが有効であるか、INSデータと航法データが全部入っているか

		ido1=0.0;
		keido1=0.0;
		takasa1=0.0;

		for(i=0;i<=7;i++){  		//緯度,経度を抽出

			*TOMAdummyido2=TOMAbuffer[kouho+i+7+41];
			*TOMAdummykeido2=TOMAbuffer[kouho+i+7+49];
			*TOMAdummytakasa=TOMAbuffer[kouho+i+7+57];

			*TOMAdummyido2++;
			*TOMAdummykeido2++;
			*TOMAdummytakasa++;


		}

		ido3= (double)ido1;		  //long→double
		keido3= (double)keido1;

		takasa2= (double)takasa1;
		takasa2=takasa2/(10*10*10*10);

		ido3=ido3*(180/pi);		  //ラジアン→度
		keido3=keido3*(180/pi);	

		ido3=ido3/(10*10*10*10*10*10*10*10*10);
		ido3=ido3/10;

		keido3=keido3/(10*10*10*10*10*10*10*10*10);
		keido3=keido3/10;

		printf("緯度2=%lf 経度2=%lf 高度=%lf \n",ido3,keido3,takasa2);


		//緯度データをtxt化
		sprintf(str,"%lf ",ido3);
		GPSido<<str<<endl;

		//経度データをtxt化
		sprintf(str,"%lf ",keido3);
		GPSkeido<<str<<endl;
		
		//高度データをtxt化
		sprintf(str,"%lf ",takasa2);
		GPStakasa<<str<<endl;

		//緯度経度データをtxt化
		sprintf(str,"%d\t%lf\t%lf\t%d",Counter2++,ido3,keido3,k);
		GPSmanualidokeido<<str<<endl;
						
		scale1=0.0;


	}


}

int set_waypoint(void){

	copy(istream_iterator<double>(latifs), istream_iterator<double>(),back_inserter(latwaydata));
	copy(istream_iterator<double>(lonifs), istream_iterator<double>(),back_inserter(lonwaydata));
	copy(istream_iterator<double>(takasaifs), istream_iterator<double>(),back_inserter(takasawaydata));

	lat_o=latwaydata[p];
	lon_o=lonwaydata[p];
	hig_o=takasawaydata[p];
	

	printf("%lf %lf %lf\n",lat_o,lon_o,hig_o);
	p++;
}

int axis_transform(void){

		vectar ecef, ecef_o, enu;
		double point1,point2;

/*		lat	= 36.532931;			//--- 変換する位置座標
		lon	= 136.629335; 
		hig	= 45.664;

		lat_o	= 36.533275;			//--- 原点の座標
		lon_o	= 136.629541;
		hig_o	= 57.829900;
*/
		ecef = blh2ecef(lat, lon, hig);
		ecef_o = blh2ecef(lat_o, lon_o, hig_o);
		enu = ecef2enu(ecef, ecef_o);		

		if(enu.a[0]<=0.5 && enu.a[1]<=0.5){
			set_waypoint();
			return 1;
		}

//		printf("result= %.3f %.3f %.3f\n", enu.a[0], enu.a[1], enu.a[2]);
//		printf("length= %.3f, angle(deg)= %.3f\n",
//		sqrt(SQR(enu.a[0])+SQR(enu.a[1])), (180.0/PI)*atan(enu.a[1]/ enu.a[0]));

		return 0;
}





