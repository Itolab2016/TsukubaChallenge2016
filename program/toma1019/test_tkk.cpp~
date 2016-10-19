#include "tsukuba_tkk.h"


char file1[]="TKK";
char file2[]="SAVE";

main(){
	set_TKK();
	TKK_serial();

	while(1){
		get_navi_data(file1,file2);
		save_wp(file1,file2);
	}

}
