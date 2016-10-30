#include "tsukuba_urg.h"


using namespace qrk;
using namespace std;	

Urg_driver urg;

ofstream urg_point("/media/ubuntu/Transcend/1027data/urg_data.txt");

int open_URG(int argc, char *argv[]){
	
	Connection_information information(argc, argv);
	if(!urg.open(information.device_or_ip_name(), information.baudrate_or_port_number(), information.connection_type())){
		cout << "Urg_driver::open(): " << information.device_or_ip_name() << ": " << urg.what() << endl;
		return 1;
	}

}

int get_urg_data(){

	vector<long> data;
	long time_stamp = 0;

	char str[512];

// Gets measurement data
#if 1
    // Case where the measurement range (start/end steps) is defined
    urg.set_scanning_parameter(urg.deg2step(-135), urg.deg2step(+135), 0);
#endif
	
urg.start_measurement(Urg_driver::Distance, Urg_driver::Infinity_times, 0);

	if(!urg.get_distance(data, &time_stamp)){
		cout << "Urg_driver::get_distance(): " << urg.what() << endl;
		//cout << data.size() << endl;
		return 1;
	}


//	cout << data.size() << endl;
//	cout << data[541] << endl;
	short j;
	double angle = 270.0 / (data.size() - 1);
	int k=1;	

	for(j=0;j<data.size();j++){
		if(data[j] <= 20) continue;
		double theta,pi,x,y;
		pi=3.14159265359;
		double now = angle * j - 135;
		theta = now * pi / 180.0;
	//	cout << "distance " << data[j] << "[mm] , angle " << now <<"[deg]" <<  endl;
	//	cout << " " << data[j] << " " << now  <<  endl;
		x=-data[j]*sin(theta);
		y=data[j]*cos(theta);
	//	cout << "x" << x << ", y" << y << endl;
	//	cout << " " << x << " " << y << endl;

		sprintf(str,"%d %ld %lf",k,data[j],now);
		urg_point<<str<<endl;
		k++;


	/*	if(x<150 && y<150 && x > -150 && y > -150){;
			return 1;
		}*/
	}
	

	return 0;


}

