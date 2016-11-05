#include <stdio.h>
#include <math.h>
#include "avoid.h"

int avoid_decide ( robot_t *urg ) {


	//変数宣言
	short n = 1081;
	int data[n];
	float dth = ( ( 3.0 * M_PI ) / 2.0 ) / n;
	float L = 3000.0;
	float W = 800.0;
	float th , phi , x , y , xx , yy , tth;
	short flag[n][181] , sflag[n] , ssflag;
	float wth=1.570796;	//目視線角

	//フラグ初期化
	for ( int i = 0 ; i < n ; i++ ) {
		for ( int j = 0 ; j < 181 ; j++ ) {
			flag[i][j] = 0;
		}
		sflag[i] = 0;
	}
	ssflag = 0;

	//フラグ建築
	for ( int i = 0 ; i < n ; i++ ) {

		th = dth * i - M_PI / 4.0;

		x = data[i] * cos ( th );
		y = data[i] * sin ( th );

		urg->urg_pt[i]=data[i];
		

		//printf ( "th=%f,x=%f,y=%f\n" ,th ,x ,y );

		for ( int j = 45 ; j < 136 ; j++ ) {

			phi = th - M_PI / 2.0 + j / 180.0 * M_PI;

			yy = x * cos ( phi ) + y * sin ( phi );
			xx = - x * sin ( phi ) + y * cos ( phi );

			//printf ( "phi=%f,xx=%f,yy=%f," ,phi ,xx ,yy );

			if ( xx > - W / 2.0 && xx < W / 2.0 && yy < L ) {

				flag[i][j] = 1;

			}
			else {

				flag[i][j] = 0;

			}

			//printf ( "i=%d,j=%d,flag[i][j]=%d\n" ,i ,j ,flag[i][j] );

			sflag[i] = sflag[i] + flag[i][j];
 
		}

		ssflag = ssflag + sflag[i];

	}

	//移動方向指定
	if ( sflag[(n-1)/2] == 0 ) {

		//printf ( "0:直進\n" );
		return 0;

	}
	else if ( ssflag >= n ) {

		//printf ( "2:停止\n" );
		return 2;

	}
	else { 

		tth = wth - M_PI / 2.0;

		if ( tth >= 0.0 ) {

			//printf ( "1:左旋回\n" );
			return 1;

		}
		if ( tth < 0.0 ) {

			//printf ( "-1:右旋回\n" );
			return -1;

		}

	}

	return 0;

}
