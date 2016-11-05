#include "tsukuba_time.h"
 
//ログデータ1行の文字数の最大値（大きめに）
#define MAX 100000

//ログデータの行数
#define ROW 10000

//ログデータ1行の要素数(2以上)
#define COL 25+1081

static char save_point[]=READLOG;
static double Dt,Kt,Ut,Lt,Motor,Init_time,Init_time_100Hz,Init_time_2Hz,Init_time_motor;
static unsigned long long Previoustime, Currenttime;
//static char timedata1[]=LOGFILE;
//static char timedata2[255];
//static char timedata3[255];
//static char timedata4[255];
static ofstream fs(LOGFILE);

static struct timeval Tv;



int reset_time(void){		//時刻をリセット
	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = (unsigned long long)1000000 * Tv.tv_sec 
		+ (unsigned long long)Tv.tv_usec;

	Init_time=Currenttime;
	Init_time_100Hz=Currenttime;
	Init_time_2Hz=Currenttime;
	Init_time_motor=Currenttime;

	return 0;

}

double get_delta_time(void){	//時刻差(Dt)を返す

	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = (unsigned long long)1000000 * Tv.tv_sec 
		+ (unsigned long long)Tv.tv_usec;
	Dt = (Currenttime - Previoustime) / 1000000.0;
//	printf("Dt=%06f\n",Dt);
	return Dt;

}

double get_time(void){		//絶対時刻(Kt)を返す

	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = (unsigned long long)1000000 * Tv.tv_sec 
		+ (unsigned long long)Tv.tv_usec;
	Kt=(Currenttime-Init_time)/1000000.0;
	Ut=(Currenttime-Init_time_100Hz)/1000000.0;
	Lt=(Currenttime-Init_time_2Hz)/1000000.0;
	Motor=(Currenttime-Init_time_motor)/1000000.0;
//	printf("%f\n",Kt);
	return Kt;

}

int on100Hz(void){		//0.01秒(Ut)経った時1を返す

	get_time();
//	printf("%f\n",Ut);
	if(Ut>=0.01){
		Init_time_100Hz=Currenttime;
		return 1;
	}
	else return 0;
}


int on2Hz(void){		//0.5秒(Lt)経った時1を返す
	get_time();
//	printf("%f\n",Kt);
	if(Lt>=0.5){
		Init_time_2Hz=Currenttime;
		return 1;
	}
	else return 0;
}

int motor_50Hz(void){
	get_time();
	if(Motor>=0.02){
		Init_time_motor=Currenttime;
		return 1;

	}
	else return 0;
}

int time_stamp(robot_t *IH){
	get_time();
	IH->time=Kt;
	return 0;
}


int log(robot_t *IH){
  char str[1024]; //整形文字列格納用変数（大きさに注意） 
	sprintf(
              str, 
             "%lf,%lf,%lf,%lf,%lf,"
             "%lf,%lf,%lf,%lf,%lf,"
             "%lf,%lf,%lf,%lf,%lf,"
             "%lf,%lf,%d,%d,%lf,"
             "%lf,%d,%lf,%lf,%s,",

              IH->time, IH->lat, IH->lon, IH->vx, IH->vy,
              IH->vz, IH->accelx, IH->accely, IH->accelz, IH->angx,
              IH->angy, IH->angvx, IH->angvy, IH->angvz, IH->height,
              IH->tbearing, IH->scale, IH->motor_l, IH->motor_r, IH->motor_v,
              IH->motor_o,IH->mode,IH->lat_goal,IH->lon_goal,IH->image
  
  );//<--sprintf終わり

	fs<<str<<flush;
#if 1 
//	for(int i=0;i<(sizeof IH->img_pt/sizeof (double))/3;i++){
	//	sprintf(str,"%lf,%lf,%lf,",IH->img_pt[i].x,IH->img_pt[i].y,IH->img_pt[i].z);
		//fs<<str<<flush;
//	}
	for (unsigned int i=0;i<(sizeof IH->urg_pt/sizeof (int));i++){
		sprintf(str,"%d,",IH->urg_pt[i]);
		fs<<str<<flush;
  }
#endif
	fs<<endl;
	//fs.close();
	return 0;
}

int fs_close(void){
	fs.close();
	return 0;
	}


int read_log(robot_t *IH,int *frame){
    FILE *fp ;
    char buf[MAX]={0};
    char *ary[COL] ;
    int n=24;
    char logname[256];
    long urg_index=1081;

    double data[n][ROW];
    char data9[ROW][256];
    //long data2[urg_index][ROW];
    sprintf(logname,"%s",save_point);
    if((fp=fopen(logname,"r"))==NULL){
      printf("File open errpr !\n");
      exit(1);
    }
     int index=0;
    /*ファイルの終わりまで繰り返し読み込む*/
    while( fgets(buf,MAX,fp) != NULL ){
      /*文字列(char配列)をカンマで分割する*/
      for(int i=0; i < COL; i++){
        if(i==0) ary[i] = strtok(buf,",");
        else ary[i] = strtok(NULL,",");
        //printf("%s\n",ary[i]);
      }
	int c=0;
	for(int i=0;i<n;i++){
		if(i==17||i==18||i==21){	
			data[i][index]=atoi(ary[c++]);
		
		}
		else{
			data[i][index]=atof(ary[c++]);
			}
	
	}
	strcpy(data9[index],ary[c++]);

	for(int j=0;j<urg_index;j++){
			IH->urg_pt[j]=atoi(ary[c++]);
	}


	   if(index==*frame)break;
      index++;
    }
    
    
	IH->time=data[0][index];
	IH->lat=data[1][index];
	IH->lon=data[2][index];
	IH->vx=data[3][index];
	IH->vy=data[4][index];
	IH->vz=data[5][index];
	IH->accelx=data[6][index];
	IH->accely=data[7][index];
	IH->accelz=data[8][index];
	IH->angx=data[9][index];
	IH->angy=data[10][index];
	IH->angvx=data[11][index];
	IH->angvy=data[12][index];
	IH->angvz=data[13][index];
	IH->height=data[14][index];
	IH->tbearing=data[15][index];
	IH->scale=data[16][index];
	IH->motor_l=data[17][index];
	IH->motor_r=data[18][index];
	IH->motor_v=data[19][index];
	IH->motor_o=data[20][index];
	IH->mode=data[21][index];
	IH->lat_goal=data[22][index];
	IH->lon_goal=data[23][index];
	sprintf(IH->image,"%s",data9[index]);			


    return 0;
}
