#include <stdio.h>
#include <math.h>
#include "avoid.h"

int avoid ( int data[1080] ) {

	//変数宣言
	short n = 1080;
	float dth = ( ( 3.0 * M_PI ) / 2.0 ) / n;
	float L = 3000.0;
	float W = 800.0;
	float th , phi , x , y , xx , yy , tth;
	short flag[n+1][181] , sflag[n+1] , ssflag;

	//フラグ初期化
	for ( int i = 0 ; i < n+1 ; i++ ) {
		for ( int j = 0 ; j < 181 ; j++ ) {
			flag[i][j] = 0;
		}
		sflag[i] = 0;
	}
	ssflag = 0;
/*
	//仮データ
	float data[n+1];
	for ( int i = 0 ; i < n+1 ; i++ ) {
		data[i] = 4000.0;
		if ( i == n / 2 ) {
			data[i] = 2000.0; //前方2mに物体有
		}
	}
	//float wth = 1.396263; //WPは80deg
	//float wth = 1.645329; //WPは100deg
	float wth = 1.570796; //WPは90deg
*/
	//フラグ建築
	for ( int i = 0 ; i < n+1 ; i++ ) {

		th = dth * i - M_PI / 4.0;

		x = data[i] * cos ( th );
		y = data[i] * sin ( th );

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
	if ( sflag[n/2] == 0 ) {

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

}
