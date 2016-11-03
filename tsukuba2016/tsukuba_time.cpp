#include "tsukuba_time.h"

//ログデータ1行の文字数の最大値（大きめに）
#define MAX 100000

//ログデータの行数
#define ROW 10000

//ログデータ1行の要素数(2以上)
#define COL 25+1081

 
static double Dt,Kt,Ut,Lt,Init_time1,Init_time2,Init_time3;
static unsigned long Previoustime, Currenttime;
static char save_point[]=READLOG;
//static char timedata2[255];
//static char timedata3[255];
//static char timedata4[255];
static ofstream fs(LOGFILE);

static struct timeval Tv;



int reset_time(void){		//時刻をリセット
	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = 1000000 * Tv.tv_sec + Tv.tv_usec;

	Init_time1=Currenttime;
	Init_time2=Currenttime;
	Init_time3=Currenttime;

}

double get_delta_time(void){	//時刻差(Dt)を返す

	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = 1000000 * Tv.tv_sec + Tv.tv_usec;
	Dt = (Currenttime - Previoustime) / 1000000.0;
//	printf("Dt=%06f\n",Dt);
	return Dt;

}

double get_time(void){		//絶対時刻(Kt)を返す

	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = 1000000 * Tv.tv_sec + Tv.tv_usec;
	Kt=(Currenttime-Init_time1)/1000000.0;
	Ut=(Currenttime-Init_time2)/1000000.0;
	Lt=(Currenttime-Init_time3)/1000000.0;
	//printf("%f\n",Kt);
	return Kt;

}

int on100Hz(void){		//0.01秒(Ut)経った時1を返す

	get_time();
//	printf("%f\n",Ut);
	if(Ut>=0.01){
		Init_time2=Currenttime;
		return 1;
	}
	else return 0;
}


int on2Hz(void){		//0.5秒(Lt)経った時1を返す
	get_time();
//	printf("%f\n",Lt);
	if(Lt>=0.5){
		Init_time3=Currenttime;
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
  char str[1024];
	sprintf(
              str, 
             "%lf,%lf,%lf,%lf,%lf,"
             "%lf,%lf,%lf,%lf,%lf,"
             "%lf,%lf,%lf,%lf,%lf,"
             "%lf,%lf,%d,%d,%lf,"
             "%lf,%d,%lf,%lf,%s",

              IH->time, IH->lat, IH->lon, IH->vx, IH->vy,
              IH->vz, IH->accelx, IH->accely, IH->accelz, IH->angx,
              IH->angy, IH->angvx, IH->angvy, IH->angvz, IH->height,
              IH->tbearing, IH->scale, IH->motor_l, IH->motor_r, IH->motor_v,
              IH->motor_o,IH->mode,IH->lat_goal,IH->lon_goal,IH->image
  );//<--sprintf終わり

	fs<<str;
/*
	for(int i=0;i<(sizeof IH->img_pt/sizeof (double))/3;i++){
		sprintf(str,"%lf,%lf,%lf,",IH->img_pt[i].x,IH->img_pt[i].y,IH->img_pt[i].z);
		fs<<str;
	}
*/
	for (int i=0;i<(sizeof IH->urg_pt/sizeof (int));i++){
		sprintf(str,"%d,",IH->urg_pt[i]);
		fs<<str;
  	}

	fs<<endl;
	//fs.close();
	return 0;
}

int fs_close(void){
	fs.close();
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
    sprintf(logname,"%s/test.log",save_point);
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
	char *p;
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

/*
	FILE *fp;
	char *p;
	char buf[200000]={0};
	char filename[1024];
	char save_point[]=READFILE;
	char *ary[24];
	double data[24]={0};
	int i=1;
	int k=0;
	int j=0;
	int l=0;
	int camera=(sizeof IH->img_pt/sizeof (double))+23;
	int urg=camera+(sizeof IH->urg_pt/sizeof (int));
	sprintf(filename,"%s",save_point);
	if((fp=fopen(filename,"r"))!=NULL){
	cout<<"a"<<endl;
	while(fgets(buf,200000,fp)){
	//puts(buf);
//	printf("%s\n",buf);

	p=strtok(buf,",");
	ary[0]=p;
	data[0]=atof(ary[0]);
	//for(int y=0;*frame>y;y++){
	//	i=0;
	while(1){
			p=strtok(NULL,",");
			if(i<24){
				ary[i]=p;
				data[i]=atof(ary[i]);
		
			}
			else if(i==24){
				sprintf(IH->image,"%s",p);
		
			}
			else if(i<camera){
				if(j==0){
					IH->img_pt[k].x=atof(p);
					j=1;
					}
				else if(j==1){
					IH->img_pt[k].y=atof(p);
					j=2;
					}
				else if(j==2){
					IH->img_pt[k].z=atof(p);
					j=0;
					k++;
					}
				}
			else if(i<urg){
					IH->urg_pt[l]=atoi(p);
					l++;
				}			


			else if(i<urg+1){
					data[0]=atof(p);
			}
			else break;
			i++;
			
			//if(i>7000)cout<<i<<endl;
		}
	//cout<<"ccc"<<endl;
	}
	//	}
	

	IH->time=data[0];
	IH->lat=data[1];
	IH->lon=data[2];
	IH->vx=data[3];
	IH->vy=data[4];
	IH->vz=data[5];
	IH->accelx=data[6];
	IH->accely=data[7];
	IH->accelz=data[8];
	IH->angx=data[9];
	IH->angy=data[10];
	IH->angvx=data[11];
	IH->angvy=data[12];
	IH->angvz=data[13];
	IH->height=data[14];
	IH->tbearing=data[15];
	IH->scale=data[16];
	IH->motor_l=data[17];
	IH->motor_r=data[18];
	IH->motor_v=data[19];
	IH->motor_o=data[20];
	IH->mode=data[21];
	IH->lat_goal=data[22];
	IH->lon_goal=data[23];
	}


}
*/






































