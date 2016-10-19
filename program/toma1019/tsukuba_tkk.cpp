#include "tsukuba_tkk.h"

#define TKK "/dev/ttyUSB0"
#define TKK_BAUD_RATE    B921600              // RS232C通信ボーレート
#define TKK_BUFF_SIZE    4096                 // 適当
#define SAVE "/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data"

using namespace std;

int TOMAfd; //global
int TOMAlen;
int TOMACounter=1;//global

unsigned char TOMAbuffer[TKK_BUFF_SIZE];    // データ受信バッファ
char *TOMAargv[0];

int *TOMAaddrX,*TOMAaddrY,*TOMAaddrZ,*TOMAaddrCRC;
long *TOMAaddrido,*TOMAaddrkeido;
unsigned char *TOMAdummyX,*TOMAdummyY,*TOMAdummyZ,*TOMAdummyCRC;
unsigned char *TOMAdummyido,*TOMAdummykeido;
//int j=0;


ofstream GPSido("/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data/latitude_goal.txt");
ofstream GPSkeido("/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data/longitude_goal.txt");
ofstream GPSkyori("/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data/scale.txt");
ofstream GPSidokeido("/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data/idokeido.txt");
ofstream GPSKOUHO("/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data/kouho.txt");
ofstream GPSaccel("/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data/accel.txt");

ofstream GPSmanualkyori("/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data/manualscale.txt");
ofstream GPSmanualidokeido("/home/itolab/work/toma/tsukuba/TsukubaChallenge2016/toma1018/data/manualidokeido.txt");


int set_TKK(void){

	// デバイスファイル（シリアルポート）オープン
	TOMAfd = open(TKK,O_RDWR);
	if(TOMAfd<0){
		// デバイスの open() に失敗したら
		perror(TOMAargv[1]);
		exit(1);
	}

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

int get_navi_data(char *motion_senser_pointer,char *save_point){

	int i,t,k=1;
	int kouho=0,INS=0;
	int rcounter=0;
	int Counter;

	float scale,scale1;

	char str[1024];

	int accelX,accelY,accelZ;
	long ido1,keido1;
	double ido3,keido3,ido4,keido4;
	double idoscale,keidoscale;
	float aX,aY,aZ;

	float pi=3.1415926535897;

	TOMAaddrX=&accelX;
	TOMAaddrY=&accelY;
	TOMAaddrZ=&accelZ;

	TOMAaddrido=&ido1;
	TOMAaddrkeido=&keido1;

	TOMAdummyX= (unsigned char *)TOMAaddrX;
	TOMAdummyY= (unsigned char *)TOMAaddrY;
	TOMAdummyZ= (unsigned char *)TOMAaddrZ;

	TOMAdummyCRC= (unsigned char *)TOMAaddrCRC;

	TOMAdummyido= (unsigned char *)TOMAaddrido;
	TOMAdummykeido= (unsigned char *)TOMAaddrkeido;

	for(i=0;i<=TOMAlen;i++){ //受信データ初期化
		TOMAbuffer[i]=0;
	}

	// ここで受信待ち
	TOMAlen=read(TOMAfd,TOMAbuffer,TKK_BUFF_SIZE);
	//printf("LEN %d\n",TOMAlen);


	if(TOMAlen==0){
		// read()が0を返したら、end of file
		// 通常は正常終了するのだが今回は無限ループ
		//     continue;
	}
	if(TOMAlen<0){
		printf("%s: ERROR\n",TOMAargv[0]);
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
		switch(rcounter){
			case 0:
				if (data==0x16)rcounter++;
				else rcounter=0;
				break;
			case 1:
				if (data==0x16)rcounter++;
				else rcounter=0;
				break;
			case 2:
				if (data==0x06)rcounter++;
				else rcounter=0;
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
				rcounter=0;
				break;
		}
	} 

	if(TOMAbuffer[kouho+6]==0x40 /*&& TOMAbuffer[INS+7+38]==0x04 */&& TOMAbuffer[kouho+83]==0x16 && TOMAbuffer[INS+59]==0x16){ 
		//航法データ受け取っているか、GPSが有効であるか、INSデータと航法データが全部入っているか
		for(i=0;i<=3;i++){  		//加速度を抽出

			*TOMAdummyX=TOMAbuffer[kouho+i+7+17];
			*TOMAdummyY=TOMAbuffer[kouho+i+7+21];
			*TOMAdummyZ=TOMAbuffer[kouho+i+7+25];

			*TOMAdummyX++;
			*TOMAdummyY++;
			*TOMAdummyZ++;
		}


		for(i=0;i<=7;i++){  		//緯度,経度を抽出

			*TOMAdummyido=TOMAbuffer[kouho+i+7+41];
			*TOMAdummykeido=TOMAbuffer[kouho+i+7+49];

			*TOMAdummyido++;
			*TOMAdummykeido++;


		}
		aX=accelX;
		aY=accelY;
		aZ=accelZ;

		aX=aX/(10*10*10);
		aY=aY/(10*10*10);
		aZ=aZ/(10*10*10);
	
		

		ido3= (double)ido1;		  //long→double
		keido3= (double)keido1;

		ido3=ido3*(180/pi);		  //ラジアン→度
		keido3=keido3*(180/pi);	

		ido3=ido3/(10*10*10*10*10*10*10*10*10);
		ido3=ido3/10;

		keido3=keido3/(10*10*10*10*10*10*10*10*10);
		keido3=keido3/10;

		printf("緯度1=%lf 経度1=%lf \n",ido3,keido3);
	//	printf("%d\n",j);
	//	fflush(stdout);


		idoscale=111316.205*(ido3-ido4);				//緯度1度あたりの距離111253m
		keidoscale=91000*(keido3-keido4);				//経度1度あたりの距離(東京)約91000m

		ido4=ido3;
		keido4=keido3;

		scale1=scale1+sqrt(idoscale*idoscale+keidoscale*keidoscale);

		Counter++;

		//緯度データをtxt化
		sprintf(str,"%lf ",ido3);
		GPSido<<str<<endl;

		//経度データをtxt化
		sprintf(str,"%lf ",keido3);
		GPSkeido<<str<<endl;

		//加速度データをtxt化
		sprintf(str,"%f %f %f",aX,aY,aZ);
		GPSaccel<<str<<endl;
			
		//移動距離をtxt化
		sprintf(str,"%lf ",scale1);
		GPSkyori<<str<<endl;
				
		//緯度経度データをtxt化
		sprintf(str,"%d\t%lf\t%lf\t%d",Counter++,ido3,keido3,k);
		GPSidokeido<<str<<endl;
						
		//航法データをtxt化
		for(i=0;i<=86;i++){
			sprintf(str,"%02X ",TOMAbuffer[kouho+i]);
			GPSKOUHO<<str;
		}
		GPSKOUHO<<endl;	

		scale1=0.0;

		ido3=0.0;
		keido3=0.0;

	}
}


int save_wp(char *motion_sensor_pointer,char *save_point){

	int i,t,k=1;
	int kouho=0,INS=0;
	int rcounter=0;
	int Counter;

	float scale,scale1;

	char str[1024];

	long ido1,keido1;
	double ido3,keido3,ido4,keido4;
	double idoscale,keidoscale;

	float pi=3.1415926535897;

	TOMAaddrido=&ido1;
	TOMAaddrkeido=&keido1;

	TOMAdummyido= (unsigned char *)TOMAaddrido;
	TOMAdummykeido= (unsigned char *)TOMAaddrkeido;

	for(i=0;i<=TOMAlen;i++){ //受信データ初期化
		TOMAbuffer[i]=0;
	}

	// ここで受信待ち
	TOMAlen=read(TOMAfd,TOMAbuffer,TKK_BUFF_SIZE);
	//printf("LEN %d\n",TOMAlen);


	if(TOMAlen==0){
		// read()が0を返したら、end of file
		// 通常は正常終了するのだが今回は無限ループ
		//     continue;
	}
	if(TOMAlen<0){
		printf("%s: ERROR\n",TOMAargv[0]);
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
		switch(rcounter){
			case 0:
				if (data==0x16)rcounter++;
				else rcounter=0;
				break;
			case 1:
				if (data==0x16)rcounter++;
				else rcounter=0;
				break;
			case 2:
				if (data==0x06)rcounter++;
				else rcounter=0;
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
				rcounter=0;
				break;
		}
	} 

	if(TOMAbuffer[kouho+6]==0x40 /*&& TOMAbuffer[INS+7+38]==0x04 */&& TOMAbuffer[kouho+83]==0x16 && TOMAbuffer[INS+59]==0x16){ 
		//航法データ受け取っているか、GPSが有効であるか、INSデータと航法データが全部入っているか

		for(i=0;i<=7;i++){  		//緯度,経度を抽出

			*TOMAdummyido=TOMAbuffer[kouho+i+7+41];
			*TOMAdummykeido=TOMAbuffer[kouho+i+7+49];

			*TOMAdummyido++;
			*TOMAdummykeido++;


		}

		ido3= (double)ido1;		  //long→double
		keido3= (double)keido1;

		ido3=ido3*(180/pi);		  //ラジアン→度
		keido3=keido3*(180/pi);	

		ido3=ido3/(10*10*10*10*10*10*10*10*10);
		ido3=ido3/10;

		keido3=keido3/(10*10*10*10*10*10*10*10*10);
		keido3=keido3/10;

		printf("緯度2=%lf 経度2=%lf \n",ido3,keido3);

		idoscale=111316.205*(ido3-ido4);				//緯度1度あたりの距離111253m
		keidoscale=91000*(keido3-keido4);				//経度1度あたりの距離(東京)約91000m

		ido4=ido3;
		keido4=keido3;

		scale1=scale1+sqrt(idoscale*idoscale+keidoscale*keidoscale);


			
		//移動距離をtxt化
		sprintf(str,"%lf ",scale1);
		GPSmanualkyori<<str<<endl;
				
		//緯度経度データをtxt化
		sprintf(str,"%d\t%lf\t%lf\t%d",Counter++,ido3,keido3,k);
		GPSmanualidokeido<<str<<endl;
						
		scale1=0.0;

		ido3=0.0;
		keido3=0.0;

	}


}
		

