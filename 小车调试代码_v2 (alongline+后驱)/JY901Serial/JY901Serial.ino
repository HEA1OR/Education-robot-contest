//#include <Wire.h>
#include "JY901.h"
#define MeasureNoise_R 2.91
#define ProcessNoise_Q 0.06
#include <SoftwareSerial.h>
static u8 __FilterFlush_r=0;
SoftwareSerial mySerial(10, 11);
float last = 0;
/*
http://item.taobao.com/item.htm?id=43511899945
Test on mega2560.
JY901   mega2560
TX <---> 0(Rx)
*/
void setup() 
{
  Serial.begin(115200);  
//  mySerial.begin(115200);/
}

void loop() 
{

//  mySerial.listen();
  while (Serial.available()) 
  {
    JY901.CopeSerialData(Serial.read()); //Call JY901 data cope function
  }
//  Serial.listen();
  //print received data. Data was received in serialEvent;
//  Serial.print("Time:20");Serial.print(JY901.stcTime.ucYear);Serial.print("-");Serial.print(JY901.stcTime.ucMonth);Serial.print("-");Serial.print(JY901.stcTime.ucDay);
//  Serial.print(" ");Serial.print(JY901.stcTime.ucHour);Serial.print(":");Serial.print(JY901.stcTime.ucMinute);Serial.print(":");Serial.println((float)JY901.stcTime.ucSecond+(float)JY901.stcTime.usMiliSecond/1000);
//               
//  Serial.print("Acc:");Serial.print((float)JY901.stcAcc.a[0]/32768*16);Serial.print(" ");Serial.print((float)JY901.stcAcc.a[1]/32768*16);Serial.print(" ");Serial.println((float)JY901.stcAcc.a[2]/32768*16);
//  
//  Serial.print("Gyro:");Serial.print((float)JY901.stcGyro.w[0]/32768*2000);Serial.print(" ");Serial.print((float)JY901.stcGyro.w[1]/32768*2000);Serial.print(" ");Serial.println((float)JY901.stcGyro.w[2]/32768*2000);
//  
float x = (float)JY901.stcAngle.Angle[0]/32768*180 + 180;
//if(abs(last - x) > 60)
//  x = last;
//last = x;
float y = (float)JY901.stcAngle.Angle[1]/32768*180;
float z = (float)JY901.stcAngle.Angle[2]/32768*180;

float xx = x;
kalmanfilter_r(&xx);
//kalmanfilter_r(&y);
//kalmanfilter_r(&z);
Serial.print("Angle:");Serial.print(x);Serial.print(" ");Serial.println(xx);
  
//  Serial.print("Mag:");Serial.print(JY901.stcMag.h[0]);Serial.print(" ");Serial.print(JY901.stcMag.h[1]);Serial.print(" ");Serial.println(JY901.stcMag.h[2]);
//  
//  Serial.print("Pressure:");Serial.print(JY901.stcPress.lPressure);Serial.print(" ");Serial.println((float)JY901.stcPress.lAltitude/100);
//  
//  Serial.print("DStatus:");Serial.print(JY901.stcDStatus.sDStatus[0]);Serial.print(" ");Serial.print(JY901.stcDStatus.sDStatus[1]);Serial.print(" ");Serial.print(JY901.stcDStatus.sDStatus[2]);Serial.print(" ");Serial.println(JY901.stcDStatus.sDStatus[3]);
//  
//  Serial.print("Longitude:");Serial.print(JY901.stcLonLat.lLon/10000000);Serial.print("Deg");Serial.print((double)(JY901.stcLonLat.lLon % 10000000)/1e5);Serial.print("m Lattitude:");
//  Serial.print(JY901.stcLonLat.lLat/10000000);Serial.print("Deg");Serial.print((double)(JY901.stcLonLat.lLat % 10000000)/1e5);Serial.println("m");
//  
//  Serial.print("GPSHeight:");Serial.print((float)JY901.stcGPSV.sGPSHeight/10);Serial.print("m GPSYaw:");Serial.print((float)JY901.stcGPSV.sGPSYaw/10);Serial.print("Deg GPSV:");Serial.print((float)JY901.stcGPSV.lGPSVelocity/1000);Serial.println("km/h");
//  
  Serial.println("");
//  Serial.println((float)JY901.stcAngle.Angle[0]/32768*180);
  delay(100);
  

}
static float x_mid1,x_last1=0,p_mid1,p_last1=0,p_now1,x_now1=0;
void kalmanfilter_r(float *z_measure) //卡尔曼滤波
{
  
  static float Q1=ProcessNoise_Q,kg1,R1=MeasureNoise_R;

  if(!__FilterFlush_r)
  {
    __FilterFlush_r=1;
    x_last1=*z_measure;
  }
  x_mid1=x_last1;                         //预测与上一时刻一致
  p_mid1=p_last1+Q1;                      //预测协方差为上一时刻协方差+Q_Noise
  kg1=p_mid1/(p_mid1+R1);                 //kg为kalman filter，R 为测量噪声
  x_now1=x_mid1+kg1*(*z_measure-x_mid1);  //计算出的最优值
  p_now1=(1-kg1)*p_mid1;                  //最优值对应的covariance
  p_last1=p_now1;                         //更新covariance 值
  x_last1=x_now1;                         //更新系统状态值
  *z_measure=x_now1;
}
