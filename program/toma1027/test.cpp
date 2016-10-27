#include "tsukuba_tkk.h"
#include "tsukuba_time.h"


char file1[]="TKK";
char file2[]="SAVE";

int main(int argc, char *argv[]){
	reset_time();
	open_TKK(argc, argv);

	while(1){
		if(on2Hz()==1){
			get_navi_data(file1,file2,argc, argv);
		//	save_wp(file1,file2,argc, argv);
		}
	}

}
