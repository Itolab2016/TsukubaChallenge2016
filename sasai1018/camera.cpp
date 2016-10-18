#include "capture.h"

#define SAVE "/home/ubuntu/Desktop/img/"

using namespace std;
using namespace cv;

//media/ubuntu/Transcend/tukuba_img

Mat frame;
int frameNo=0;
//char a="SAVE";
char str[255];//フレーム画像保存用
VideoCapture cap(0);
char file[]=SAVE;
int camera_open()
{
	//VideoCapture cap(0);
	if(!cap.isOpened())//カメラデバイスが正常にオープンしたか確認．
	{
		//読み込みに失敗したときの処理
		cout<<"読み込みエラー"<<endl;
		return -1;
	}

	for(int i=0;i<100;i++)
	{
		//cout<<"capture"<<endl;
		capture(cap,file);//写真取る
	}
}
int capture (VideoCapture cap,char *save_point)
{
	cap >> frame;
	//フレーム画像を保存する．
	frameNo++;
	sprintf(str,"%s%04d.png",save_point,frameNo);
        imwrite(str, frame);
}

int main (){
	camera_open();
	//for(int i=0;i<100;i++){
	//for(long j=0;j<100000;j++);
	capture(cap,file);
	//}
}


