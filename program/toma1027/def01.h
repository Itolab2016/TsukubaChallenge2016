/*--- 定数 */
#define	MAXN	12

/*--- 2乗、3乗 */
#define SQR(x)		((x)*(x))
#define CUB(y)		((y)*(y)*(y))

/*--- WGS84座標パラメータ */
#define	PI				3.1415926535898
#define A					6378137.0				/* Semi-major axis */ 
#define ONE_F			298.257223563   /* 1/F */
#define B					(A*(1.0 - 1.0/ONE_F))
#define E2				((1.0/ONE_F)*(2-(1.0/ONE_F)))
#define ED2				(E2*A*A/(B*B))
#define NN(p)			(A/sqrt(1.0 - (E2)*SQR(sin(p*PI/180.0))))

#define C					2.99792458E+08  /* Speed of light */
#define MU				3.986005E+14    /* Earth's universal gravity */
#define	OMEGADOTE	7.2921151467E-05 /* Earth's rotation rate (rad/s) */
#define F					-4.442807633E-10 /* F sec/m^(1/2) */
