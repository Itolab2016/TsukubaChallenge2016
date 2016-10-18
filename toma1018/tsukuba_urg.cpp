#include "tsukuba_urg.h"

#define URG /dev/ttyUSB0
#define SAVE /home/work

char file[]="URG";
char file1[]="SAVE";

int get_urg_data(char *urg_pointer,char *save_point){

	Urg_driver urg;
	vector<long> data;
	long time_stamp = 0;

	Connection_information information(argc, argv);
	if(!urg.open(information.device_or_ip_name(), information.baudrate_or_port_number(), information.connection_type())){
		cout << "Urg_driver::open(): " << information.device_or_ip_name() << ": " << urg.what() << endl;
		return 1;
	}
// Gets measurement data
#if 1
    // Case where the measurement range (start/end steps) is defined
    urg.set_scanning_parameter(urg.deg2step(-60), urg.deg2step(+60), 0);
#endif
urg.start_measurement(Urg_driver::Distance, Urg_driver::Infinity_times, 0);

	if(!urg.get_distance(data, &time_stamp)){
		cout << "Urg_driver::get_distance(): " << urg.what() << endl;
		//cout << data.size() << endl;
		return 1;
	}


	//cout << data.size() << endl;
	cout << data[256] << endl;
	short j;
	double angle = 120.0 / (data.size() - 1);
	for(j=0;j<data.size();j++){
		if(data[j] <= 20) continue;
		double theta,pi,x,y;
		pi=3.14159265359;
		double now = angle * j - 90;
		theta = now * pi / 180.0;
		//cout << "distance " << data[j] << "[mm] , angle " << now <<"[deg]" <<  endl;
		x=-data[j]*sin(theta);
		y=data[j]*cos(theta);
		//cout << "x" << x << ", y" << y << endl;
		if(x<150 && y<150 && x > -150 && y > -150){;
			return 1;
		}
	}
	return 0;


}

main(){

	get_urg_data( file, file1);

}
