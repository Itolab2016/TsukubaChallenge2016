//TKKのセンサCSM-MG100のデータをデコードするためのプログラム
//Copy right Kouhei Ito 2016
//C++を勉強しつつもほとんどCで書いていてわかりづらいかも
//
#ifndef DECODE_TEST_H
#define DECODE_TEST_H

#include <stdio.h>
#include <unistd.h>

typedef struct{
  double lat;
  double lon;
} navidata_s;


int get_navi_data(navidata_s* navi);


#endif
