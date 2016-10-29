#include"avoid.h"
#include"tsukuba_tkk.h"
static double ramuda=0;



int navigation(void)
	{	
	cout<<"navigation"<<endl;
	}

void move(double &latitude,double &latitude_goal,double &longitude,double &longitude_goal,float &omega){
	float wide=602;
	float n=8.5;
	double h=0.5;
	double ramuda0=0;	

	if(axis_transform()==0)
		{
		ramuda0=ramuda;
		}
	ramuda=atan(longitude_goal-longitude/latitude_goal-latitude);
	omega=n*(ramuda-ramuda0)/h;
cout<<"omega="<<omega<<endl;

/*
	V_left=v+omega*wide/2;			
	V_right=v-omega*wide/2;
*/

}
