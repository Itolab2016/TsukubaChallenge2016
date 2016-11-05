//つくばチャレンジ2016用プログラム
//誘導関連のプログラム
//
#include"navigation.h"

using namespace std;

double waypoint[149][2]={
36.0800121227,140.1156979295,
36.0800900678,140.1156486322,
36.0801866399,140.1155723429,
36.080291663,140.115500007,
36.080380821,140.1154329709,
36.0805111574,140.1153347545,
36.0806342861,140.1152309575,
36.0806297769,140.1151493511,
36.0805905236,140.1150683119,
36.0805401778,140.1149962109,
36.0804824236,140.1149254449,
36.0804466424,140.1148827825,
36.0804233803,140.114857114,
36.0803814685,140.1148590849,
36.0803227116,140.1149088922,
36.0802770412,140.1149459568,
36.0801306103,140.115061849,
36.0799952834,140.1151629588,
36.0798539863,140.115255142,
36.0797191178,140.1153483565,
36.0796517322,140.1153985304,
36.0795743944,140.1154186412,
36.0795294115,140.1153333565,
36.0794494094,140.1151634229,
36.0794103909,140.1150821775,
36.0793721861,140.1150102427,
36.0793630474,140.1149350477,
36.0794091763,140.1148601048,
36.0795193045,140.1147584564,
36.0796442952,140.114639602,
36.0797780981,140.114479764,
36.0799206958,140.1143428843,
36.0800549856,140.1142170112,
36.0801662139,140.1141105156,
36.0802828567,140.114000628,
36.0804220453,140.1139065483,
36.0805741198,140.1138341608,
36.0807237477,140.1137665518,
36.0808767847,140.1136842178,
36.0810332309,140.1135878406,
36.0811797992,140.1134941505,
36.0813201853,140.1133976988,
36.0814475366,140.1132905098,
36.0815815114,140.1132440258,
36.0817284865,140.1131627689,
36.0818733531,140.1130842278,
36.0819473449,140.1130467564,
36.0820313004,140.1130062082,
36.0821102483,140.1130140749,
36.0821629432,140.1130785097,
36.082208648,140.1131518884,
36.0822460278,140.1132203225,
36.0823013813,140.1132409547,
36.0823754017,140.1132131835,
36.0825150716,140.1131464568,
36.0826519168,140.1130843023,
36.0827846081,140.1129904748,
36.0829009759,140.1129124837,
36.0830240873,140.1128324931,
36.0831427068,140.1127527145,
36.083274722,140.1126644389,
36.0834047204,140.1125764268,
36.0835393139,140.1124826164,
36.0836824273,140.1123941861,
36.0838102198,140.1123104483,
36.0839329187,140.1122145753,
36.0840190858,140.112101101,
36.0840966013,140.1119594659,
36.0842240443,140.1118568548,
36.0842926674,140.1118088696,
36.0843504159,140.1117575326,
36.084357658,140.1116943927,
36.0843490408,140.1116243314,
36.0843575721,140.1115377575,
36.0843570965,140.1114634391,
36.0843380973,140.1113881926,
36.0842943405,140.1113308051,
36.0842369702,140.1112868879,
36.0841765976,140.1112573347,
36.0841054248,140.111253536,
36.084034951,140.1112720196,
36.0839692213,140.1113062997,
36.0838444998,140.111376086,
36.0837053055,140.1114257328,
36.0835680133,140.1114643329,
36.0835039681,140.111502681,
36.0834585956,140.1115584355,
36.0834335631,140.1116257179,
36.0834385535,140.1117033824,
36.0834574153,140.1117791904,
36.0835042202,140.1119202125,
36.0835453471,140.1119848135,
36.0836015543,140.112025631,
36.0836696962,140.1120334232,
36.083727668,140.1120115592,
36.0838252084,140.1119266984,
36.0838866695,140.111906112,
36.08395323,140.111914334,
36.0840011866,140.1119678769,
36.0839859746,140.1122011967,
36.0838670973,140.1122961015,
36.0837469996,140.1123883076,
36.0836175742,140.112478749,
36.0834871633,140.1125882928,
36.0833519739,140.112671406,
36.0832215687,140.1127574013,
36.0830844656,140.1128562938,
36.0829462682,140.112950637,
36.0828190601,140.1130359848,
36.0826944246,140.1131260595,
36.0825642543,140.1132270032,
36.0824416757,140.1133239018,
36.0823014844,140.1133693546,
36.0821777083,140.1132756359,
36.0820342626,140.1132168962,
36.0819348315,140.1130884563,
36.0819129273,140.1130308626,
36.0819278873,140.1129343822,
36.0819433285,140.1128070824,
36.0822056056,140.1127564673,
36.0821720017,140.1129271515,
36.0819620585,140.1131112256,
36.0817885955,140.1132358096,
36.0816491089,140.1133363064,
36.0815198153,140.1134311767,
36.0813949162,140.1135375119,
36.081268642,140.1136355106,
36.0811281872,140.1137218095,
36.0809941952,140.1137994568,
36.0808591147,140.1138777343,
36.0807337229,140.1139522073,
36.0806086806,140.1140211915,
36.0804846983,140.1140958249,
36.0803581261,140.1141639267,
36.0802243863,140.1142354662,
36.0800933452,140.1143542977,
36.079955904,140.1144514083,
36.079826576,140.114512371,
36.0796975803,140.1145671515,
36.0795837049,140.1146514336,
36.0794729808,140.1147861417,
36.0793611853,140.1149175438,
36.0792272163,140.1150302217,
36.0792477626,140.1150886176,
36.079332503,140.115237111,
36.0793509294,140.1154034407,
36.0793502246,140.1153984559,
36.0793499897,140.1154001347,
36.0793476979,140.1154015786
};

int waypoint_index=0;

//static double lambda=1.0;
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
	int i;
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

int init_waypoint(robot_t *robo){
  waypoint_index++;
  robo->lat_goal=waypoint[0][0];
  robo->lon_goal=waypoint[0][1];
  return 0;
}

int set_waypoint(robot_t *robo){
  waypoint_index++;
  robo->lat_goal=waypoint[waypoint_index][0];
  robo->lon_goal=waypoint[waypoint_index][1];
  return 0;
}

int change_waypoint(robot_t *robo){
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
  
  if(xt*xt+yt*yt<1.0*1.0){
    set_waypoint(robo);
  }
  
  return 0;
}


int navigation(robot_t *robo)
//比例航法を用いてロボットを誘導（navigation）する。

{	
//  double wide=602.0;
  double n=1.0;
  double h=0.5;
//  double lambda_old;	
//  double omega1;
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
  
  //======== 比例航法 ========
  //比例航法は参考文献
  robo->motor_o= n * (xt*((yt-yt_old)/h)-yt*((xt-xt_old)/h))/(pow(xt,2.0)+pow(yt,2.0));
  robo->motor_v=0.5;
  
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
