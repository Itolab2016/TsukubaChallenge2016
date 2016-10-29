/*--- �٥��ȥ����� */
typedef struct {
	int n;            /* size of vector */
	double a[MAXN];   /* elements of vector */
	int err;          /* err=1: error */ 
} vectar;

/*--- �������� */
typedef struct {
	int n;            		/* size of raw */
	int m;            		/* size of columb */
	double a[MAXN][MAXN]; /* elements of matrix */
	char message[80];     /* error report */
	int err;							/* err=1: error */
} matrix;

