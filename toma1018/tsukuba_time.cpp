#include "tsukuba_time.h"
 
double Dt,Kt,Ut,Init_time;
unsigned long Previoustime, Currenttime;
struct timeval Tv;

int reset_time(void){		//時刻をリセット
	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = 1000000 * Tv.tv_sec + Tv.tv_usec;
	Init_time=Currenttime;

}

double get_delta_time(){	//時刻差を返す

	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = 1000000 * Tv.tv_sec + Tv.tv_usec;
	Dt = (Currenttime - Previoustime) / 1000000.0;
//	printf("Dt=%06f\n",Dt);
	return Dt;

}

double get_time(){	//絶対時刻を返す

	gettimeofday(&Tv,NULL);  
	Previoustime = Currenttime;
	Currenttime = 1000000 * Tv.tv_sec + Tv.tv_usec;
	Ut=(Currenttime-Init_time)/1000000.0;
//	printf("%f\n",Ut);
	

	return Ut;

}

int on100Hz(){		//0.01秒経った時1を返す

	get_time();
	if(Ut>=0.01){
		Init_time=Currenttime;
		return 1;
	}
	else return 0;
}


int on2Hz(){		//0.5秒経った時1を返す

	get_time();
	if(Ut>=0.5){
		Init_time=Currenttime;
		printf("%f\n",Ut);
		return 1;
	}
	else return 0;
}









