#include "Urg_driver.h"
//#include "Connection_information.h"
#include "math_utilities.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "tsukuba_urg.h"
#define SAVEPOINT "urg_data.txt"
#define MEASURMENTANGLE 180.0

using namespace std;
using namespace qrk;

Urg_driver urg;
ofstream urg_point(SAVEPOINT);


void print_data(const Urg_driver& urg, const vector<long>& data, long time_stamp)
{
#if 1
  // Shows only the front step
  int front_index = urg.step2index(0);
  cout << data[front_index] << " [mm], ("
    << time_stamp << " [msec])" << endl;

#else
  // Prints the X-Y coordinates for all the measurement points
  long min_distance = urg.min_distance();
  long max_distance = urg.max_distance();
  size_t data_n = data.size();
  for (size_t i = 0; i < data_n; ++i) {
    long l = data[i];
    if ((l <= min_distance) || (l >= max_distance)) {
      continue;
    }

    double radian = urg.index2rad(i);
    long x = static_cast<long>(l * cos(radian));
    long y = static_cast<long>(l * sin(radian));
    cout << "(" << x << ", " << y << ")" << endl;
  }
  cout << endl;
#endif
}



int urg_open()
{

  long baudrate=115200;    
  Urg_driver::connection_type_t c_type=Urg_driver::Serial;
  char device[]="/dev/ttyACM0";

  if ( !urg.open(device, baudrate, c_type) ) {
    cout << "Urg_driver::open() error"<< endl;
    return 1;
  }
  urg.set_scanning_parameter(urg.deg2step(-MEASURMENTANGLE/2), urg.deg2step(+MEASURMENTANGLE/2), 0);
}



int get_urg_data()
{
  vector<long> data;
	char str[255];
  long time_stamp = 0;

	//計測司令
  urg.start_measurement(Urg_driver::Distance, 1, 0);
	
	//計測データ取得
  if (!urg.get_distance(data, &time_stamp)) {
    cout << "Urg_driver::get_distance(): error" << endl;
    return 1;
  }
	cout << data.size() << endl;
  //print_data(urg, data, time_stamp);

	double angle_step = MEASURMENTANGLE / (data.size() - 1);
	
	int k=0;	

	for(int j=0;j<data.size();j++){
		if(data[j] <= 20) continue;
		double theta,pi,x,y;
		pi=3.14159265359;
		theta = angle_step*j + (-(MEASURMENTANGLE -180.0)/2.0);
		x= data[j]*cos(theta*pi/180.0);
		y= data[j]*sin(theta*pi/180.0);

		sprintf(str,"%d %ld %lf %lf %lf,%ld",k,data[j],x,y,theta,time_stamp);
		urg_point<<str<<endl;
		k++;
	}
  return 0;
}
