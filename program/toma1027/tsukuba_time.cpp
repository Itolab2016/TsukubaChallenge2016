#include "tsukuba_time.h"
 
static double Dt,Kt,Ut,Lt,Init_time1,Init_time2,Init_time3;
static unsigned long Previoustime, Currenttime;
static char timedata1[255];
static char timedata2[255];
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

int save(char *save_point,char *name,vector<float>& all_time){
	get_time();
	all_time.push_back(Kt);
	sprintf(timedata1,"%s%s.txt",save_point,name);
	ofstream fs(timedata1);
	for(int i=0;i<all_time.size();i++){
		sprintf(timedata2,"%lf",all_time[i]);
		fs<<timedata2<<endl;
		}
	fs.close();
	return 0;
}



