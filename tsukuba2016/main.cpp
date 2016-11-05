//つくばチャレンジ2016用プログラム
//メイン関数
//
//======== Memo ========
//SSDのUUID="96da4cce-7db5-406d-b155-5f14b50e49fb"
//
// SSDを起動時にマウントするためには
// /etc/fstabファイルに以下の情報を記述する
/*
   UUID="96da4cce-7db5-406d-b155-5f14b50e49fb" /media/ubuntu/itolab ext4 defaults 0 0


 */
//
//
//
//

#include "motor.h"
#include "joystick.h"
#include "tsukuba_time.h"
#include "camera.h"
#include "tsukuba_tkk.h"
#include "tsukuba_urg.h"
#include "navigation.h"
#include "avoid.h"
#include "localization.h"
#include "tsukuba_def.h"
//#include <thread>



#define FILE_TIME "/media/ubuntu/Transcend/1027data/"

using namespace std; 
//=========================================
//timeval t;
//unsigned long il,l;
//unsigned long long ill,ll,old=0;
//========================================


robot_t robo;

enum{WAIT,MANUAL_RUN,AUTO_RUN};

void motor_control(robot_t *robo){
  motor_remote(robo);
  motor_command(robo);
}



int main(){

  camera_open();
  motor_open();
  joy_open();
  dummy_open();
  open_TKK();
  open_URG();

  //========================================
  //gettimeofday(&t,NULL);
  //printf("%ld,%ld\n",t.tv_sec,t.tv_usec);
  //il = (unsigned long)t.tv_sec*1000000 + (unsigned long)t.tv_usec;
  //ill= (unsigned long long)t.tv_sec*1000000 + (unsigned long long)t.tv_usec;
  //========================================

  reset_time();
  cout<<"Start !"<<endl;
  system("aplay -q /home/ubuntu/Desktop/voice/program.wav");

  robo.mode=WAIT;
  int count=0;

  //Main loop
  while(1){
    //ジョイスティック読み込み
    joy_read();

    //モード分岐

    //======== 待機モード ========
    if(robo.mode==WAIT){

      if(sikaku()==1/*SHIKAKU*/){			//手動走行に変更
        robo.mode=MANUAL_RUN;
        reset_time();
        cout<<"data_pick_mode"<<endl;
      }

      else if(sankaku()==1/*SANKAKU*/){	//自立走行に変更
        robo.mode=AUTO_RUN;
        init_waypoint(&robo);
        reset_time();
      }

      else if(batu())break;//終了

    }

    //======== 手動モード ========
    else if(robo.mode==MANUAL_RUN){

      if(start()/*START*/)
      {
        cout<<"break"<<endl;
        robo.mode=WAIT;
      }
      
      //100Hzループ
      if( on100Hz() ){
        printf("%lf",get_time());
        printf(":Motor control.\n");
        motor_remote(&robo);  
        motor_command(&robo);

        switch(count){
        case 0:
          break; 
        case 1:
          printf("%lf",get_time());
          printf(":Cam capture.\n");
          //capture(&robo);
          break;
        case 5:
          printf("%lf",get_time());
          printf(":Get navi data.\n");
          get_navi_data(&robo);
          break;
        case 7:
          printf("%lf",get_time());
          printf(":Get URG data.\n");
          get_urg_data(&robo);
          break;
        }
        count++;
        if(count==10)count=0;

        time_stamp(&robo);
        log(&robo);
      }

      //WP記録
      if(maru()){

        time_stamp(&robo);
        //  save_wp(&robo);
        cout<<"way_get"<<endl;
      }
    }//<--Manual mode end

    //======== 自律モード ========
    else if(robo.mode==AUTO_RUN){
      if(on2Hz()==1)
      {
        get_navi_data(&robo);     //モーションセンサーから航法データ取得
        get_urg_data(&robo);      //LIDER(URG)のデータ取得
        change_waypoint(&robo);    //Waypointの変更を判断
        int d = avoid_decide(&robo);     //回避判定
        if(d==0){
          navigation(&robo);      //比例航法
        }
        else if(d == 1){//停止＆右旋回
          robo.motor_v =  0.0;
          robo.motor_o = -0.2;
        }
        else if(d ==-1){//停止＆左旋回
          robo.motor_v =  0.0;
          robo.motor_o =  0.2;
        }
        else if(d == 2){//停止
          robo.motor_v =  0.0;
          robo.motor_o =  0.0;
        }
        time_stamp(&robo);
        log(&robo);           //ログ記録
      }
      motor_command(&robo);

      if(start()==1/*START*/)
      {
        cout<<"break"<<endl;
        robo.mode=WAIT;
      }
    }//<--Autonomus mode end

  }//<--while(1)に対応

  //停止して終了
  robo.motor_v=0;
  robo.motor_o=0;
  motor_command(&robo);
  motor_close();
}	
