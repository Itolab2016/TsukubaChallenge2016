#include "tsukuba_urg.h"

main(){

  urg_open();
	for(int i=0;i<10;i++){
  	get_urg_data();
	}
}
