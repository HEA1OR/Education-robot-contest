#include "ult_wall.h"

float distance_cm = 0; //与墙的距离

//u16 就是两字节的无符号整型，u8 一字节；
static u8 __FilterFlush_r=0;

//这是变量声明，是告诉编译器应该到该文件外部去找这个文件的定义
extern int countLeft, countRight;  //encoder
/*
	Name: ultrasonic_init()
	Function: Initialize the ultrasonic
*/
void ultrasonic_init()
{
	pinMode(TRIG_LEFT, OUTPUT);  //16号脚
	pinMode(ECHO_LEFT, INPUT);   //17号脚
}

/*
	Name: getDistance(void)
	Function: get the distance between car and wall by ultrasonic
*/

//getDistance是一个没有返回值的函数，只不过他把测得的距离值放在了全局变量distance_cm中

void getDistance(void)
{
	digitalWrite(TRIG_LEFT,LOW);
  //延时函数，以微秒为单位，1毫秒为1000微秒
  delayMicroseconds(2);
  digitalWrite(TRIG_LEFT,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_LEFT,LOW);//设置引脚的输出电压为高电平或者低电平
  
  distance_cm = pulseIn(ECHO_LEFT,HIGH)/58.0;//算成厘米
  //Serial.println(distance_cm);
  //卡尔曼滤波
  kalmanfilter_r(&distance_cm);
  
  distance_cm = (int(distance_cm * 100.0))/100.0;//保留两位小
  //3delay(50);
}

//这是个卡尔曼滤波的函数，不作研究了，直接用
void kalmanfilter_r(float *z_measure) //卡尔曼滤波
{
  static float x_mid1,x_last1=0,p_mid1,p_last1=0,p_now1,x_now1=0;
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
