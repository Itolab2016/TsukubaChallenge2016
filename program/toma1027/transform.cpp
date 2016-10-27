#include "tsukuba_tkk.h"
#include "tsukuba_time.h"


int main(int argc, char *argv[]){
	
	open_TKK(argc, argv);
	while(1){
		if(on2Hz()==1){
			get_navi_data(argc, argv);
			axis_transform();
			printf("\n");
		}
	}
}
