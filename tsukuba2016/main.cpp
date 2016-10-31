//つくばチャレンジ2016用プログラム
//メイン関数
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


#define SAVE_PHOTO "/home/itolab/Desktop/1028sasai/test_img/"
#define SAVE_TXT "/home/itolab/Desktop/1028sasai/test_txt/"
//#define SAVE_CAMERA_TXT "/home/ubuntu/Desktop/data/"
#define FILE_TIME "/media/ubuntu/Transcend/1027data/"

using namespace std; 

static char way[]="way";
static char noway[]="noway";

robot_t robo;

enum{WAIT,MANUAL_RUN,AUTO_RUN};

int main(){

  int count=0;
  //float v,omega;
  //double scale=100;
  double latitude_goal,longitude_goal;
  int button;
  vector<float> way_time;
  vector<float> auto_time;
  char save_photo[]=SAVE_PHOTO;
  char save_txt[]=SAVE_TXT;
  //	char save_time[]=FILE_TIME;
  camera_open();
  motor_open();
  joy_open();
  open_TKK();
  cout<<"TKK_open"<<endl;
  open_URG();
  cout<<"URG_open"<<endl;
  reset_time();
  cout<<"Start !"<<endl;

  robo.mode=WAIT;

  //Main loop
  while(1){
    count=0;
    joy_read();
    button=get_joy_button ();

    //モード分岐

    //======== 待機モード ========
    if(robo.mode==WAIT){

      if(button==15/*SHIKAKU*/){			//手動走行に変更
        robo.mode=MANUAL_RUN;
        reset_time();
        cout<<"data_pick_mode"<<endl;
      }

      else if(button==12/*SANKAKU*/){	//自立走行に変更
        robo.mode=AUTO_RUN;
        set_waypoint();
        reset_time();
      }

      else if(button==14/*BATU*/)break;//終了

    }

    //======== 手動モード ========
    else if(robo.mode==MANUAL_RUN){


      if(button==3/*START*/)
      {
        cout<<"break"<<endl;
        robo.mode=WAIT;
      }
      //2Hzループ
      if(on2Hz()==1)
      {
        capture(save_photo);  //画像撮影
        get_navi_data(&robo); //
        get_urg_data(&robo);  //
      }
      //100Hzループ
      if(on100Hz()==1){
        motor_remote(&robo);  //
        motor_command(&robo); //
        log(&robo);					  //状態ロギング
      }

      //WP記録
      if(button==13/*MARU*/){
        //save(FILE_TIME,way,way_time);
        save_wp();
        cout<<"way_get"<<endl;
      }
    }


    //======== 自律モード ========
    else if(robo.mode==AUTO_RUN){
      if(on2Hz()==1)
      {
        /*					capture2(save_photo);

                    if(count!=0)
                    {
                    localization();//未完成
                    axis_trarnsform();//未完成
                    sfm(save_photo,save_txt,scale);
                    }*/
        count++;
      }

      if(on100Hz()==1)
      {
        get_urg_data(&robo);  //LIDER(URG)のデータ取得
        //avoid_decide();     //未完成
        get_navi_data(&robo); //モーションセンサーから航法データ取得
        //move(&robo);
        navigation(&robo);    //比例航法
        motor_command(&robo); //モータへ司令
        log(&robo);           //ログ記録
      }
      if(button==3/*START*/)
      {
        cout<<"break"<<endl;
        robo.mode=WAIT;
      }
    }
  }//<--while(1)に対応

  //停止して終了
  robo.motor_v=0;
  robo.motor_o=0;
  motor_command(&robo);
  motor_close();
}	
