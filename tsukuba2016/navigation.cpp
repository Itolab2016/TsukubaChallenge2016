#include"navigation.h"


static double ramuda=1.0;

using namespace std;

int navigation(void)
	{	
	cout<<"navigation"<<endl;
	}

//void move(double latitude,double latitude_goal,double longitude,double longitude_goal,float *omega)
void move(robot_t *IH){
	float wide=602;
	float n=1.0;
	double h=0.5;
	double ramuda0;	
	float omega1;
	ramuda0=ramuda;
	ramuda=atan(IH->lon_goal-IH->lon/IH->lat_goal-IH->lat);
	if(change_waypoint()==0)
		{
		IH->motor_o=n*(ramuda-ramuda0)/h;
		}
	IH->motor_v=0.5;
	cout<<"omega="<<IH->motor_o<<endl;
/*
	V_left=v+omega*wide/2;			
	V_right=v-omega*wide/2;
*/

}
