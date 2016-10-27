#include "tsukuba_tkk.h"


char file1[]="TKK";
char file2[]="SAVE";

main(int argc, char *argv[]){
	open_TKK();

	while(1){
		get_navi_data(file1,file2,argc, argv);
	//	save_wp(file1,file2,argc, argv);
	}

}
