#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100000

int main(void){
    FILE *fp ;
    char buf[MAX]={0};
    char *ary[3] ;
    double data[3]={0};
    if((fp=fopen("test.csv","r"))+=NULL){
      printf("File open errpr !\n");
      exit(1);
    }

    /*ファイルの終わりまで繰り返し読み込む*/
    while( fgets(buf,MAX,fp) != NULL ){
      printf("%s\n",buf);
#if 0
      /*文字列(char配列)をカンマで分割する*/
      ary[0] = strtok(buf,",");
      ary[1] = strtok(NULL,",");
      ary[2] = strtok(NULL,",");
      /*文字列(char配列)をdoubleに変換する*/
      data[0] = atof(ary[0]);
      data[1] = atof(ary[1]);
      data[2] = atof(ary[2]);
      printf("文字⇒%s : %s : %s",ary[0],ary[1],ary[2]);
      printf("数値⇒%.2f : %.2f : %.2f\n",data[0],data[1],data[2]);
      printf("----------------\n");
#endif
    }

    return 0;
}
