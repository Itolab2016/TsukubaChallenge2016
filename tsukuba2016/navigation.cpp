//つくばチャレンジ2016用プログラム
//誘導関連のプログラム
//
#include"navigation.h"

using namespace std;

static double lambda=1.0;
matrix ret_mat;
double xt_old;
double yt_old;

vectar blh2ecef(double phi, double ramda, double height)
/* 緯度,経度,高さからECEF座標に変換 */
{
	vectar ecef;

	ecef.n = 3;
	ecef.a[0] = (NN(phi)+height)*cos(phi*PI/180)*cos(ramda*PI/180);
	ecef.a[1] = (NN(phi)+height)*cos(phi*PI/180)*sin(ramda*PI/180);
	ecef.a[2] = (NN(phi)*(1-E2)+height)*sin(phi*PI/180);

	return ecef;
}

vectar ecef2blh(vectar ec)
/* ECEF座標からWGS84の{緯度,経度,楕円体高}へ変換 */
{
	vectar blh;
	int i = 0;
	double phi, ramda, height, p; 
	double x, y, z;
	double sita;

	ec.n = 3; blh.n = 3;
	x = ec.a[0], y = ec.a[1], z = ec.a[2];

	p = sqrt(x*x + y*y);
	sita = (180/PI) * atan2(z*AAA, p*BBB);

/*--- 緯度 */
	phi = (180/PI) * atan2(z+ED2*BBB*(CUB(sin(sita*PI/180))),(p-E2*AAA*(CUB(cos(sita*PI/180)))));	

/*--- 経度 */
	ramda = (180/PI) * atan2(y,x);

/*--- 高さ */	
	height = (p / cos(phi*PI/180)) - NN(phi);   

	blh.a[0] = phi; blh.a[1] = ramda; blh.a[2] = height;
	return blh;
}

matrix rotx(double sita)
/* x軸回りのsita度の回転変換：右ねじの方向 */
{
	matrix rota;
	rota.n = rota.m = 3;

	rota.a[0][0] = 1;
	rota.a[0][1] = 0;
	rota.a[0][2] = 0;
	
	rota.a[1][0] = 0;
	rota.a[1][1] = cos(sita*PI/180.0);
	rota.a[1][2] = sin(sita*PI/180.0);
		
	rota.a[2][0] = 0;
	rota.a[2][1] = -sin(sita*PI/180.0);
	rota.a[2][2] = cos(sita*PI/180.0);
	
	return rota;
}

matrix roty(double sita)
{
	matrix rota;
	rota.n = rota.m = 3;
		
	rota.a[0][0] = cos(sita*PI/180.0);
	rota.a[0][1] = 0;
	rota.a[0][2] = -sin(sita*PI/180.0);
	
	rota.a[1][0] = 0;
	rota.a[1][1] = 1;
	rota.a[1][2] = 0;
		
	rota.a[2][0] = sin(sita*PI/180.0);
	rota.a[2][1] = 0;
	rota.a[2][2] = cos(sita*PI/180.0);

	return rota;
}
	
matrix rotz(double sita)
{
	matrix rota;
	rota.n = rota.m = 3;
	
	rota.a[0][0] = cos(sita*PI/180.0);
	rota.a[0][1] = sin(sita*PI/180.0);
	rota.a[0][2] = 0;
	
	rota.a[1][0] = -sin(sita*PI/180.0);
	rota.a[1][1] = cos(sita*PI/180.0);
	rota.a[1][2] = 0;
		
	rota.a[2][0] = 0;
	rota.a[2][1] = 0;
	rota.a[2][2] = 1;
	
	return rota;
}

vectar matvec(matrix inmat, vectar v1)
/*--- 行列とベクトルの積 */
{
	int i, j;
	vectar ret_v;

	for (i=0;i<MAXN;i++) ret_v.a[i]=0.0;
	ret_v.err = 0;
	if((inmat.n>MAXN)||(inmat.n<0)||(inmat.m>MAXN)||(inmat.m<0))
		ret_v.err=1;
	if((v1.n > MAXN) || (v1.n<0)) ret_v.err=1;
	if((v1.n) != (inmat.m)) ret_v.err=1;
	if(ret_v.err == 1){ ret_v.n=0; return ret_v; }
	ret_v.n=inmat.n;
	for (i=0;i<inmat.n;i++){
		for (j=0;j<inmat.m;j++) ret_v.a[i] = ret_v.a[i] + inmat.a[i][j] * v1.a[j];
	}
	return ret_v;
}

matrix matmat(matrix *m1, matrix *m2)
/*--- 行列の積 */
{
	int i, j, k, mcount;

   ret_mat.err = 0;
   if ((m1->n>MAXN)||(m1->n<0)||(m1->m>MAXN)||(m1->m<0)) ret_mat.err=1;
   if ((m2->n>MAXN)||(m2->n<0)||(m2->m>MAXN)||(m2->m<0)) ret_mat.err=1;

   if  ((m1->m) != (m2->n))  ret_mat.err=1;
   mcount = m1->m;
   if (ret_mat.err == 1){
      strcpy(ret_mat.message,"Something went wrong.");
			printf("Something went wrong!\n");
      ret_mat.n = 0;
      ret_mat.m = 0;
      return ret_mat; 
   }

   ret_mat.n = m1->n;
   ret_mat.m = m2->m;

   for (i=0;i<ret_mat.n;i++)  {
      for (j=0;j<ret_mat.m;j++) ret_mat.a[i][j]=0.0;
   }

   for (i=0;i<ret_mat.n;i++){
      for (j=0;j<ret_mat.m;j++){
	 			for (k=0;k<mcount;k++){
	    		ret_mat.a[i][j] += m1->a[i][k] * m2->a[k][j] ;
	 			}
      }
   }
   return ret_mat;
}

vectar ecef2enu(vectar dest, vectar origin)
/*--- ECEF座標を水平線座標(ENU)へ変換する */ 
{
	int i, j;
	vectar mov, ret, blh;
	matrix rotyp, rotzp1, rotzp2;
	matrix mat_conv1, mat_conv2;

	origin.n  = 3;		origin.err  = 0;	
	mov.n 	  = 3;		mov.err     = 0; 
	ret.n 	  = 3; 	ret.err     = 0;

	blh = ecef2blh(origin);

	rotzp1 = rotz(90.0);
	rotyp  = roty(90.0 - blh.a[0]);
	rotzp2 = rotz(blh.a[1]);

	mat_conv1 = matmat(&rotzp1, &rotyp);
	mat_conv2 = matmat(&mat_conv1, &rotzp2);

	for(i=0;i<3;i++) mov.a[i] = dest.a[i] - origin.a[i];
	ret = matvec(mat_conv2, mov);
	return ret;
}

int set_waypoint(void){

	copy(istream_iterator<double>(latifs), istream_iterator<double>(),back_inserter(latwaydata));
	copy(istream_iterator<double>(lonifs), istream_iterator<double>(),back_inserter(lonwaydata));
	copy(istream_iterator<double>(takasaifs), istream_iterator<double>(),back_inserter(takasawaydata));

	lat_o=latwaydata[p];
	lon_o=lonwaydata[p];
	hig_o=takasawaydata[p];
	

	printf("%lf %lf %lf\n",lat_o,lon_o,hig_o);
	p++;
}

int change_waypoint(void){

		vectar ecef, ecef_o, enu;

		ecef = blh2ecef(lat, lon, hig);
		ecef_o = blh2ecef(lat_o, lon_o, hig_o);
		enu = ecef2enu(ecef, ecef_o);		

		if(enu.a[0]<=0.5 && enu.a[1]<=0.5){
			set_waypoint();
			return 1;
		}
	

		return 0;
}


int navigation(robot_t *robo)
//比例航法を用いてロボットを誘導（navigation）する。

{	
  double wide=602.0;
	double n=1.0;
	double h=0.5;
	double lambda_old;	
	double omega1;
  double lat,lon,high,x,y;
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
  x=0.0;
  y=0.0;
  xt=enu_t.a[0];
  yt=enu_t.a[1];
  
  //======== 比例航法 ========
  //比例航法は参考文献
  
  
  
  //終了前に現在の値を記憶する（数値微分のため）
  xt_old = xt;
  yt_old = yt;

	cout<<"navigation"<<endl;
	
	return 0;
}

//void move(double latitude,double latitude_goal,double longitude,double longitude_goal,float *omega)
int move(robot_t *IH){
//関数名がmoveでは英語の意味から何をしようとしているかわからなくなる可能性があるので
//以下の機能はnavigation()の方に移します。
//それに伴ってメイン関数を修正しました。(2016.10.30 ITO)

#if 0
  double wide=602.0;
	double n=1.0;
	double h=0.5;
	double lambda_old;	
	double omega1;
  double lat,lon,high,x,y,xt,yt;

  //以下の計算は平面座標系に変換されていないので正しくありません。（2016.10.31 ITO）
	lambda_old=lambda;
	lambda=atan(IH->lon_goal-IH->lon/IH->lat_goal-IH->lat);
	if(change_waypoint()==0)
		{
		IH->motor_o = n*(lambda - lambda_old)/h;
		}
	IH->motor_v = 0.5;
	cout<<"omega="<<IH->motor_o<<endl;
/*
	V_left=v+omega*wide/2;			
	V_right=v-omega*wide/2;
*/
#endif
  cout << "Called move() function."<<endl;
  return 0;
}
