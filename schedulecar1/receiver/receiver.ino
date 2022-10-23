#include <SPI.h>
#include "Servo.h"
uint8_t data_rx_buff[10];   // unit8_t 就是 unsigned char
extern float leftLength = 0, rightLength = 0;     // 一定时间内左右轮所走长度
#define LEDModePin0 2
#define LEDModePin1 3              // 译码法选择灯带显示模式
int valL = 1500, valR = -1500;


Servo motorL, motorR;

//下面四行的作用是将数据拆分为字节的形式

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

//SPI双机通信 SPI有三个寄存器分别为：控制寄存器SPCR，状态寄存器SPSR，数据寄存器SPDR。

char SPI_SlaveReceive(void){
  
   //就当这句话是检验SPIF是否发生了置位，发生了说明发送完成
   
      while(!(SPSR & (1<<SPIF)));//SPI是双向通讯，发送完成后，从机要发送的数据会存入SPDR中
      return SPDR;
}


//这个函数的返回值不是0就是1
float receive_data(void)
{
  uint8_t cnt=0,temp=0;
  float leftLengthTemp, rightLengthTemp;

  while(1)
  {

//想要理解这块代码，就要好好理解SPI_SlaveReceive()这个函数及其SPI模块内部的东西

    // temp 获得传输的数据
    
    temp=SPI_SlaveReceive();

    //只要temp不是0xAA ,这个while(1)就会一直执行，直到temp为0xAA
    //为什么是0xAA，还不知道
    //看nano的代码，算了，我还是重写一版代码吧
    
    if(temp==0xAA)
    {
      break;
    }
      
   }
  while(cnt<10)
  {
    temp=SPI_SlaveReceive();
    
    if(temp!=0xDD)
      data_rx_buff[cnt++]=temp;
    else
      break;
  }
  
  if(cnt==8)
  {
      BYTE3(leftLengthTemp)=data_rx_buff[0];
      // Serial.write(BYTE3(b));
      BYTE2(leftLengthTemp)=data_rx_buff[1];
      //  Serial.write(BYTE2(b));
      BYTE1(leftLengthTemp)=data_rx_buff[2];
      // Serial.write(BYTE1(b));
      BYTE0(leftLengthTemp)=data_rx_buff[3];
      // Serial.write(BYTE0(b));
      BYTE3(rightLengthTemp)=data_rx_buff[4];
      // Serial.write(BYTE3(b));
      BYTE2(rightLengthTemp)=data_rx_buff[5];
      //  Serial.write(BYTE2(b));
      BYTE1(rightLengthTemp)=data_rx_buff[6];
      // Serial.write(BYTE1(b));
      BYTE0(rightLengthTemp)=data_rx_buff[7];
      // Serial.write(BYTE0(b));

      leftLength = leftLengthTemp;
      rightLength = rightLengthTemp;
      
      return 0;   // 表示数据获取成功
  }
    else
    {
      //Serial.println(cnt);
      return 1;
    }
}

void setup()
{
  Serial.begin(115200);
  motorL.attach(7);
  motorL.writeMicroseconds(1500);
  motorR.attach(8);
  motorR.writeMicroseconds(-1500);

// MISO SS 都是什么管脚？

  // MISO 代表数据输出，SS代表使能端
  
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(LEDModePin0, OUTPUT);
  pinMode(LEDModePin1, OUTPUT);

  //将使能端设置为低电平，使其工作
  digitalWrite(SS, LOW);

// 将SPI设置为从机
  
  SPCR |= _BV(SPE);
  
}
//ISR (SPI_STC_vect)
//  {
//    Slavereceived = SPDR;                  
//    received = true;                       
//  }
void loop(){
  getEncoder();
  Serial.print(leftLength);
  Serial.print(" ");
  Serial.println(rightLength);
//  setLightMode(0);
//  delay(2000);
//  setLightMode(1);
//  delay(3000);
  int speeeeed = 8;
  if(leftLength < speeeeed)
    valL += speeeeed - leftLength;
  if(leftLength > speeeeed)
    valL -= leftLength - speeeeed;
  if(rightLength < speeeeed)
    valR -= 10 - rightLength;
  if(rightLength > speeeeed)
    valR += rightLength - speeeeed;
  motorL.writeMicroseconds(valL);
  motorR.writeMicroseconds(valR);
}

void getEncoder(){
  int well = receive_data();
  for(int i = 0; i < 10; i ++){
    if(well == 1){
      well = receive_data();
    }
    else break;
  }
}

void setLightMode(int x){
  if(x == 0){
    digitalWrite(LEDModePin0, LOW);
    digitalWrite(LEDModePin1, LOW);
  }
  else if(x == 1){
    digitalWrite(LEDModePin0, HIGH);
    digitalWrite(LEDModePin1, LOW);
  }
  else if(x == 2){
    digitalWrite(LEDModePin0, LOW);
    digitalWrite(LEDModePin1, HIGH);
  }
  else if(x == 3){
    digitalWrite(LEDModePin0, HIGH);
    digitalWrite(LEDModePin1, HIGH);
  }
}
