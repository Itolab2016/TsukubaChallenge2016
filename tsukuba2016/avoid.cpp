#include <stdio.h>
#include <math.h>
#include "navigation.h"
#include "avoid.h"

int avoid_decide (robot_t *robo ) {


  //変数宣言
  short n = 1081;
  //int data[n];
  float dth = ( ( 3.0 * M_PI ) / 2.0 ) / n;
  float L = 3000.0;
  float W = 800.0;
  float th , phi , x , y , xx , yy , tth;
  short flag[n][181] , sflag[n] , ssflag;
  float wth;//=1.570796;	//目視線角
  float psi;

  //======== 目視線角度を計算 ======== 0~2pi
  double lat,lon,high;
  double lat_g, lon_g;
  double xt,yt;
  vectar ecef_o;  //ロボットのecef座標
  vectar ecef_t;  //ターゲットのecef座標
  vectar enu_t;   //ターゲットのenu座標

  //変数を受ける(変数の文字列が長くて見難いので)
  lat = robo->lat;
  lon = robo->lon;
  high= robo->height;
  lat_g=robo->lat_goal;
  lon_g=robo->lon_goal;

  //座標変換　緯度経度高さ->ロボット原点平面座標
  ecef_o = blh2ecef(lat, lon, high);  //ロボットの座標（ここが原点）
  ecef_t = blh2ecef(lat_g, lon_g, high);//ターゲットの座標
  enu_t = ecef2enu(ecef_t,ecef_o);  //enu座標系でのターゲットの座標
  xt=enu_t.a[0];
  yt=enu_t.a[1];
  wth = atan2(yt,xt);//平面座標系での目標の方向
  if(wth<0.0){
    wth = 2*M_PI + wth;
  }
  psi = 2*M_PI - robo->tbearing;//平面座標系での方位角
  wth =wth - psi; //ロボット座標系での目標の方向（目視線角）

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

    x = robo->urg_pt[i] * cos ( th );
    y = robo->urg_pt[i] * sin ( th );

    //urg->urg_pt[i]=data[i];


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
    return NAVIGATION;

  }
  else if ( ssflag >= n ) {

    //printf ( "2:停止\n" );
    return STOP;

  }
  else { 

    tth = wth - M_PI / 2.0;

    if ( tth >= 0.0 ) {

      //printf ( "1:左旋回\n" );
      return CCWTURN;

    }
    if ( tth < 0.0 ) {

      //printf ( "-1:右旋回\n" );
      return CWTURN;

    }

  }

  return 0;

}
