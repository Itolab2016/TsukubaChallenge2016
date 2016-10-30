#include"avoid.h"
#include"tsukuba_tkk.h"
static double ramuda=1.0;



int navigation(void)
	{	
	cout<<"navigation"<<endl;
	}

void move(double latitude,double latitude_goal,double longitude,double longitude_goal,float *omega){
	float wide=602;
	float n=1.0;
	double h=0.5;
	double ramuda0=0;	
	float omega1;
	ramuda0=ramuda;
	ramuda=atan(longitude_goal-longitude/latitude_goal-latitude);
	if(change_way()==0)
		{
		omega1=n*(ramuda-ramuda0)/h;
		*omega=omega1;
		}
	cout<<"omega="<<omega<<endl;
/*
	V_left=v+omega*wide/2;			
	V_right=v-omega*wide/2;
*/

}
