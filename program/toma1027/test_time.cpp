#include "tsukuba_time.h"

main(){
	reset_time();
	while(1){
		//printf("%d ",on2Hz());
		//on100Hz();
		//on2Hz();
#if 1
		if(on100Hz()==1){
			//printf("100Hz %f\n",get_time());
			fflush(stdout);
			
		}
		if(on2Hz()==1){
			printf("               2Hz %f\n",get_time());
			fflush(stdout);
		}
#endif
	}
	

}
