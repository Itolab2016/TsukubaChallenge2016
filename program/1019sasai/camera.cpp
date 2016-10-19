#include "camera.h"

#define SAVE "/media/itolab/disk2/work/sasai/img/"

using namespace std;
using namespace cv;


Mat frame;
int frameNo=0;
//char a="SAVE";
char str[255];//フレーム画像保存用
static VideoCapture cap(0);
//static char file[]=SAVE;
int camera_open(void)
{
	char file[]=SAVE;
	
	if(!cap.isOpened())//カメラデバイスが正常にオープンしたか確認．
	{
		//読み込みに失敗したときの処理
		cout<<"読み込みエラー"<<endl;
		exit(1);
		return -1;
	}

	for(int i=0;i<100;i++)
	{
		//cout<<"capture"<<endl;
		capture(file);//写真取る
	}
}
int capture (char *save_point)
{
	cap >> frame;
	//フレーム画像を保存する．
	frameNo++;
	sprintf(str,"%s%04d.png",save_point,frameNo);
        imwrite(str, frame);
}


