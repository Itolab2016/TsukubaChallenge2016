#include "decode_test.h"

//定数定義
//メッセージIndex
#define N (1024*3)
#define TT_INDEX 0
#define RSV_INDEX 4
#define LBL_INDEX 6
#define WC_INDEX  7
#define DC_INDEX 8
#define FTR_INDEX 8
#define CRC_INDEX 10

//Label
#define STATUS 0x20
#define NAVIGATIONDATA 0x40
#define PRECISION 0x41
#define SENSORDATA 0x43
#define GPSDATA 0x60

//ステータスデータIndex
#define S_DATASTATUS 0
#define S_TYPE 4
#define S_SERIAL 8
#define S_VERSION 12
#define S_PLD 14
#define S_YEAR 16
#define S_MONTH 18
#define S_DAY 19
#define S_HOUR 20
#define S_MIN 21
#define S_SEC 22
#define S_UTC_MOD 24
#define S_DATA_CONFIG 28
#define S_CALC_TYPE 30
#define S_SENSOR_STATE 32
#define S_CALIB_ALART 33
#define S_ALIGNMENT_STATUS 36
#define S_GPS_STATUS 37
#define S_INIT_ACC_STATUS 38
#define S_FAILURE_STATUS 40
#define S_ATTACHMENT_ANGLE_STATUS 44

//航法データIndex
#define N_DATASTATUS 0
#define N_P 4
#define N_Q 8
#define N_R 12
#define N_X_ACC 16
#define N_Y_ACC 20
#define N_Z_ACC 24
#define N_ROLL_ANG 28
#define N_PITCH_ANG 32
#define N_YAW_ANG 36
#define N_LAT 40
#define N_LON 48
#define N_HEIGHT 56
#define N_NS_VEL 60
#define N_EW_VEL 65
#define N_DU_VEL 68

#define RAD2DEG (180.0/3.141592653589793)

int decode_test(int fd)
{

  enum {TT,RSV,LBL,WC,DC,FTR,CRC} mode;
  unsigned char buf[N];
  unsigned char statusdata[63];
  unsigned char navigationdata[87];
  unsigned char value;
  int len;
  char str[2];
  unsigned int data;
  int index=0;
  int subindex=0;
  int dc_size=0;
  int init_flag=0;
  int timetag;
  int label=0;
  int counter=0;
  unsigned char* dummy_ptr;


  //デコード値格納変数
  //ステータス
  unsigned char s_datastatus;
  unsigned short product_type;
  unsigned int serial_number;
  unsigned short version;
  unsigned short PLD_version;
  unsigned short year;
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char min;
  unsigned char sec;
  unsigned short utcmod;
  unsigned short outputdata_config;
  unsigned short caliculation_type;
  unsigned char sensor_state;
  unsigned char calib_alart;
  unsigned char alignment_status;
  unsigned char gps_status;
  unsigned char init_accel_status;
  unsigned int failure_status;
  unsigned int attachment_angle_config;

  //航法データ
  unsigned char n_datastatus;
  int p_rate;
  int q_rate;
  int r_rate;
  int x_accel;
  int y_accel;
  int z_accel;
  int roll_angle;
  int pitch_angle;
  int yaw_angle;
  long long latitude;
  long long longitude;
  int height;
  int NS_vel;
  int EW_vel;
  int DU_vel;  

  while((len=read(fd, buf, sizeof(buf)))==N){

    int rcounter=0;
    for (int i=0;i<len;i=i+3){

      //文字列を数値に変換
      str[0]=buf[i];
      str[1]=buf[i+1];
      sscanf(str,"%x",&data);
      //printf("%02X ",data);

      if(init_flag==1){
        if(index==TT_INDEX){
          mode=TT;
          timetag=0;
        }
        else if(index==RSV_INDEX){
          //printf("\rTime=%f",timetag/100.0);//起動からの経過時間表示
          mode=RSV;
        }
        else if(index==LBL_INDEX){
          mode=LBL;
          label=data;
        }
        else if(index==WC_INDEX){
          mode=WC;
          dc_size=data;
        }
        else if(index==DC_INDEX){
          mode=DC;
          subindex=0;
        }
        else if(index==FTR_INDEX+dc_size){
          mode=FTR;
          //データ取り出し
          switch(label){
          case STATUS:
            s_datastatus=statusdata[S_DATASTATUS];
            year=statusdata[S_YEAR]+statusdata[S_YEAR+1]*0x100;
            month=statusdata[S_MONTH];
            day=statusdata[S_DAY];
            hour=statusdata[S_HOUR];
            min=statusdata[S_MIN];
            sec=statusdata[S_SEC];
            utcmod=statusdata[S_UTC_MOD]
              +statusdata[S_UTC_MOD+1]*0x100;
            outputdata_config=statusdata[S_DATA_CONFIG]
              +statusdata[S_DATA_CONFIG+1]*0x100;
            caliculation_type=statusdata[S_CALC_TYPE]
              +statusdata[S_CALC_TYPE+1]*0x100;
            sensor_state=statusdata[S_SENSOR_STATE];
            calib_alart=statusdata[S_CALIB_ALART];
            alignment_status=statusdata[S_ALIGNMENT_STATUS];
            gps_status=statusdata[S_GPS_STATUS];
            init_accel_status=statusdata[S_INIT_ACC_STATUS];
            failure_status=statusdata[S_FAILURE_STATUS]
              +statusdata[S_FAILURE_STATUS+1]*0x100
              +statusdata[S_FAILURE_STATUS+2]*0x10000
              +statusdata[S_FAILURE_STATUS+3]*0x1000000;
            attachment_angle_config=statusdata[S_ATTACHMENT_ANGLE_STATUS]
              +statusdata[S_ATTACHMENT_ANGLE_STATUS+1]*0x100
              +statusdata[S_ATTACHMENT_ANGLE_STATUS+2]*0x10000
              +statusdata[S_ATTACHMENT_ANGLE_STATUS+3]*0x1000000;
            //printf("%02X,%4d/%02d/%02d,%02d:%02d:%02d,%05d,",s_datastatus,year,month,day,hour,min,sec,utcmod);
            //printf("%04X,%02X,%08X\r",caliculation_type,gps_status,failure_status);
            break;
          case NAVIGATIONDATA:
            n_datastatus=navigationdata[N_DATASTATUS];
            //P
            dummy_ptr=(unsigned char*)(&p_rate);
            *(dummy_ptr)=navigationdata[N_P];
            *(++dummy_ptr)=navigationdata[N_P+1];
            *(++dummy_ptr)=navigationdata[N_P+2];
            *(++dummy_ptr)=navigationdata[N_P+3];
            //Q
            dummy_ptr=(unsigned char*)(&q_rate);
            *(dummy_ptr)=navigationdata[N_Q];
            *(++dummy_ptr)=navigationdata[N_Q+1];
            *(++dummy_ptr)=navigationdata[N_Q+2];
            *(++dummy_ptr)=navigationdata[N_Q+3];
            //R
            dummy_ptr=(unsigned char*)(&r_rate);
            *(dummy_ptr)=navigationdata[N_R];
            *(++dummy_ptr)=navigationdata[N_R+1];
            *(++dummy_ptr)=navigationdata[N_R+2];
            *(++dummy_ptr)=navigationdata[N_R+3];
            //x_accel
            dummy_ptr=(unsigned char*)(&x_accel);
            *(dummy_ptr)=navigationdata[N_X_ACC];
            *(++dummy_ptr)=navigationdata[N_X_ACC+1];
            *(++dummy_ptr)=navigationdata[N_X_ACC+2];
            *(++dummy_ptr)=navigationdata[N_X_ACC+3];
            //y_accel
            dummy_ptr=(unsigned char*)(&y_accel);
            *(dummy_ptr)=navigationdata[N_Y_ACC];
            *(++dummy_ptr)=navigationdata[N_Y_ACC+1];
            *(++dummy_ptr)=navigationdata[N_Y_ACC+2];
            *(++dummy_ptr)=navigationdata[N_Y_ACC+3];
            //z_accel
            dummy_ptr=(unsigned char*)(&z_accel);
            *(dummy_ptr)=navigationdata[N_Z_ACC];
            *(++dummy_ptr)=navigationdata[N_Z_ACC+1];
            *(++dummy_ptr)=navigationdata[N_Z_ACC+2];
            *(++dummy_ptr)=navigationdata[N_Z_ACC+3];
            //roll_angle
            dummy_ptr=(unsigned char*)(&roll_angle);
            *(dummy_ptr)=navigationdata[N_ROLL_ANG];
            *(++dummy_ptr)=navigationdata[N_ROLL_ANG+1];
            *(++dummy_ptr)=navigationdata[N_ROLL_ANG+2];
            *(++dummy_ptr)=navigationdata[N_ROLL_ANG+3];
            //pitch_angle
            dummy_ptr=(unsigned char*)(&pitch_angle);
            *(dummy_ptr)=navigationdata[N_PITCH_ANG];
            *(++dummy_ptr)=navigationdata[N_PITCH_ANG+1];
            *(++dummy_ptr)=navigationdata[N_PITCH_ANG+2];
            *(++dummy_ptr)=navigationdata[N_PITCH_ANG+3];
            //yaw_angle
            dummy_ptr=(unsigned char*)(&pitch_angle);
            *(dummy_ptr)=navigationdata[N_YAW_ANG];
            *(++dummy_ptr)=navigationdata[N_YAW_ANG+1];
            *(++dummy_ptr)=navigationdata[N_YAW_ANG+2];
            *(++dummy_ptr)=navigationdata[N_YAW_ANG+3];
            //latitude
            dummy_ptr=(unsigned char*)(&latitude);
            *(dummy_ptr)=navigationdata[N_LAT];
            *(++dummy_ptr)=navigationdata[N_LAT+1];
            *(++dummy_ptr)=navigationdata[N_LAT+2];
            *(++dummy_ptr)=navigationdata[N_LAT+3];
            *(++dummy_ptr)=navigationdata[N_LAT+4];
            *(++dummy_ptr)=navigationdata[N_LAT+5];
            *(++dummy_ptr)=navigationdata[N_LAT+6];
            *(++dummy_ptr)=navigationdata[N_LAT+7];
            //longitude
            dummy_ptr=(unsigned char*)(&longitude);
            *(dummy_ptr)=navigationdata[N_LON];
            *(++dummy_ptr)=navigationdata[N_LON+1];
            *(++dummy_ptr)=navigationdata[N_LON+2];
            *(++dummy_ptr)=navigationdata[N_LON+3];
            *(++dummy_ptr)=navigationdata[N_LON+4];
            *(++dummy_ptr)=navigationdata[N_LON+5];
            *(++dummy_ptr)=navigationdata[N_LON+6];
            *(++dummy_ptr)=navigationdata[N_LON+7];
            //height
            dummy_ptr=(unsigned char*)(&height);
            *(dummy_ptr)=navigationdata[N_HEIGHT];
            *(++dummy_ptr)=navigationdata[N_HEIGHT+1];
            *(++dummy_ptr)=navigationdata[N_HEIGHT+2];
            *(++dummy_ptr)=navigationdata[N_HEIGHT+3];
            //NS velocity
            dummy_ptr=(unsigned char*)(&NS_vel);
            *(dummy_ptr)=navigationdata[N_NS_VEL];
            *(++dummy_ptr)=navigationdata[N_NS_VEL+1];
            *(++dummy_ptr)=navigationdata[N_NS_VEL+2];
            *(++dummy_ptr)=navigationdata[N_NS_VEL+3];
            //EW velocity
            dummy_ptr=(unsigned char*)(&EW_vel);
            *(dummy_ptr)=navigationdata[N_EW_VEL];
            *(++dummy_ptr)=navigationdata[N_EW_VEL+1];
            *(++dummy_ptr)=navigationdata[N_EW_VEL+2];
            *(++dummy_ptr)=navigationdata[N_EW_VEL+3];
            //DU velocity
            dummy_ptr=(unsigned char*)(&DU_vel);
            *(dummy_ptr)=navigationdata[N_DU_VEL];
            *(++dummy_ptr)=navigationdata[N_DU_VEL+1];
            *(++dummy_ptr)=navigationdata[N_DU_VEL+2];
            *(++dummy_ptr)=navigationdata[N_DU_VEL+3];

            if(counter%100==0){
              printf("%d\t%.20lf\t%.20lf\t1\n",counter,RAD2DEG*latitude*1.0e-10,(RAD2DEG)*longitude*1.0e-10);
            }
            counter++;
            break;
          }
        }
        else if(index==CRC_INDEX+dc_size){
          mode=CRC;
        }
        //printf("mode=%d\n",mode);


        switch(mode){
        case TT://起動からの経過時間計算
          timetag=timetag+(data<<(index*8));
          break;
        case RSV:
          break;
        case LBL:
          break;
        case WC:
          break;
        case DC:
          switch(label){
          case STATUS:
            statusdata[subindex++]=data;
            break;
          case NAVIGATIONDATA:
            navigationdata[subindex++]=data;
            break;
          case PRECISION:
            break;
          case SENSORDATA:
            break;
          case GPSDATA:
            break;
          }
          break;
        case FTR:
          break;
        case CRC:
          break;
        }

      }//if(init_flag==1)の最後



      index++;
      //データの先頭を見つける
      switch(rcounter){
      case 0:
        if (data==0x16)rcounter++;
        else rcounter=0;
        break;
      case 1:
        if (data==0x16)rcounter++;
        else rcounter=0;
        break;
      case 2:
        if (data==0x06)rcounter++;
        else rcounter=0;
        break;
      case 3:
        if (data==0x02){
          //printf("\n");
          index=0;
          init_flag=1;
        }
        rcounter=0;
        break;
      }


    }//bufの大きさ分ループ最後
  }//データ終了までループ最後
  return 0;
}


