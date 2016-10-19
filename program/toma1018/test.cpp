#include "tsukuba_time.h"

main(){
	reset_time();
	while(1){
		on2Hz();
		if(on2Hz()==1){
			printf("a\n");
			
		}
	}
}
