//このサンプルではログデータはすべて配列に読み込まれます。
//読み込みのループが終われば任意場所のデータを配列から読み込むことが可能です
//ただし配列に全データを読み込むプログラムはメモリを大量に消費する可能性があるので
//注意しなければなりません。


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//ログデータ1行の文字数の最大値（大きめに）
#define MAX 100000

//ログデータの行数
#define ROW 10000

//ログデータ1行の要素数(2以上)
#define COL 10


int main(void){
    FILE *fp ;
    char buf[MAX]={0};
    char *ary[COL] ;

    int data0[ROW],data1[ROW],data2[ROW],data3[ROW],data4[ROW];
    double data5[ROW],data6[ROW],data7[ROW],data8[ROW];
    char *data9[ROW];


    if((fp=fopen("test.log","r"))==NULL){
      printf("File open errpr !\n");
      exit(1);
    }
     int index=0;
    /*ファイルの終わりまで繰り返し読み込む*/
    while( fgets(buf,MAX,fp) != NULL ){


      /*文字列(char配列)をカンマで分割する*/
      for(int i=0; i < COL; i++){
        if(i==0) ary[i] = strtok(buf,",");
        else ary[i] = strtok(NULL,",");
        //printf("%s\n",ary[i]);
      }


      /*文字列(char配列)をdoubleに変換する*/
      int c=0;
      data0[index] = atoi(ary[c++]);
      data1[index] = atoi(ary[c++]);
      data2[index] = atoi(ary[c++]);
      data3[index] = atoi(ary[c++]);
      data4[index] = atoi(ary[c++]);
      data5[index] = atof(ary[c++]);
      data6[index] = atof(ary[c++]);
      data7[index] = atof(ary[c++]);
      data8[index] = atof(ary[c++]);
      data9[index] = ary[c++];

      printf("%d,%d,%d,%d,%d,%f,%f,%f,%f,%s",
        data0[index],data1[index],data2[index],data3[index],data4[index],
        data5[index],data6[index],data7[index],data8[index],data9[index]
      );

    }

    return 0;
}
