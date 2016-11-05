//つくばチャレンジ2016
//誘導関連ヘッダーファイル
//
//
//
#ifndef NAVIGATION_H
#define NAVIGATION_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "tsukuba_tkk.h"
#include "tsukuba_def.h"



//======== 以下は座標変換関係の定数や構造体の定義やマクロです。
/*--- 定数 */
#define	MAXN	12

/*--- 2乗、3乗 */
#define SQR(x)		((x)*(x))
#define CUB(y)		((y)*(y)*(y))

/*--- WGS84座標パラメータ */
#define	PI				3.1415926535898
#define AAA					6378137.0				/* Semi-major axis */ 
#define ONE_F			298.257223563   /* 1/F */
#define BBB					(AAA*(1.0 - 1.0/ONE_F))
#define E2				((1.0/ONE_F)*(2-(1.0/ONE_F)))
#define ED2				(E2*AAA*AAA/(BBB*BBB))
#define NN(p)			(AAA/sqrt(1.0 - (E2)*SQR(sin(p*PI/180.0))))

#define CCC					2.99792458E+08  /* Speed of light */
#define MU				3.986005E+14    /* Earth's universal gravity */
#define	OMEGADOTE	7.2921151467E-05 /* Earth's rotation rate (rad/s) */
#define FFF					-4.442807633E-10 /* F sec/m^(1/2) */


/*--- ベクトルの定義 */
typedef struct {
	int n;            /* size of vector */
	double a[MAXN];   /* elements of vector */
	int err;          /* err=1: error */ 
} vectar;

/*--- 行列の定義 */
typedef struct {
	int n;            		/* size of raw */
	int m;            		/* size of columb */
	double a[MAXN][MAXN]; /* elements of matrix */
	char message[80];     /* error report */
	int err;							/* err=1: error */
} matrix;

vectar ecef2enu(vectar dest, vectar origin);
vectar blh2ecef(double phi, double ramda, double height);
vectar ecef2blh(vectar ec);

vectar blh2ecef(double, double, double);
vectar ecef2blh(vectar);
matrix matmat(matrix *, matrix *);
vectar matvec(matrix, vectar);
double abs1(double);

//typedef double (*daryp)[MAXN][MAXN];
//typedef double (dary)[MAXN][MAXN];

int axis_transform(void);				//座標変換

//========以上が座標変換関連

int init_waypoint(robot_t *robo);
int set_waypoint(robot_t *robo);					//wpを設定
int change_waypoint(robot_t *robo);

int navigation(robot_t *robo);
int move(robot_t *IH);
#endif
