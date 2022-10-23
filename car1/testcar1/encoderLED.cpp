#include "encoderLED.h"
#include <SPI.h>

uint8_t data_rx_buff[10];   // unit8_t 就是 unsigned char
volatile long int sideLength = 0;     // 一定时间内左右轮所走长度
float angle = 0;
#define LEDModePin0 2
#define LEDModePin1 3              // 译码法选择灯带显示模式

//下面四行的作用是将数据拆分为字节的形式

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

//SPI双机通信 SPI有三个寄存器分别为：控制寄存器SPCR，状态寄存器SPSR，数据寄存器SPDR。

void encoderLEDInit(){

  // 需要指出的是，小车的SPI是将nano板作为Master，openduino作为slave
  // 理论上来说openduino作为Master更好，也符合常识，但往届学长的代码已经写成这样
  // 既然能用，就没必要再改，如果有想法想改，应该不难。
    pinMode(MISO, OUTPUT);
    pinMode(MOSI, INPUT);
    pinMode(LEDModePin0, OUTPUT);
    pinMode(LEDModePin1, OUTPUT);
    //将使能端设置为低电平，使其工作
    digitalWrite(SS, LOW);

    // 将SPI设置为从机

    SPCR |= _BV(SPE);
}

void getEncoder(){
  //调用该函数将外部的leftLength和rightLength修改为最新检测到的。
  //i的作用?
    int well = receive_data();
    for(int i = 0; i < 10; i ++){
        if(well == 1){
                well = receive_data();
                Serial.print("1");            
        }
        else 
        {
            break;
        }
    }
}



void setLightMode(int x){
  // 译码法指定nano板上的LED灯模式
  // 目前只接了两根线，能够输出四种模式
  // 还可以采用的方法：软件模拟串口通讯、SPI主从机通讯等
  // 因为时间原因选择了最简单的实现模式。
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


char SPI_SlaveReceive(void){
  
   //就当这句话是检验SPIF是否发生了置位，发生了说明发送完成
   
      while(!(SPSR & (1<<SPIF)));//SPI是双向通讯，发送完成后，从机要发送的数据会存入SPDR中
      return SPDR;
}


//这个函数的返回值不是0就是1
int receive_data(void)
{
  uint8_t cnt=0,temp=0;
  long int lengthTemp;
  float angleTemp;

  while(1)
  {

//想要理解这块代码，就要好好理解SPI_SlaveReceive()这个函数及其SPI模块内部的东西

    // temp 获得传输的数据
    
    temp=SPI_SlaveReceive();

    //只要temp不是0xAA ,这个while(1)就会一直执行，直到temp为0xAA
    //为什么是0xAA，还不知道
    //看nano的代码，0xAA是数据起始标志，0xDD是数据结束标志
    
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
      BYTE3(lengthTemp)=data_rx_buff[0];
      // Serial.write(BYTE3(b));
      BYTE2(lengthTemp)=data_rx_buff[1];
      //  Serial.write(BYTE2(b));
      BYTE1(lengthTemp)=data_rx_buff[2];
      // Serial.write(BYTE1(b));
      BYTE0(lengthTemp)=data_rx_buff[3];
      // Serial.write(BYTE0(b));
      BYTE3(angleTemp)=data_rx_buff[4];
      // Serial.write(BYTE3(b));
      BYTE2(angleTemp)=data_rx_buff[5];
      //  Serial.write(BYTE2(b));
      BYTE1(angleTemp)=data_rx_buff[6];
      // Serial.write(BYTE1(b));
      BYTE0(angleTemp)=data_rx_buff[7];
      // Serial.write(BYTE0(b));

      sideLength = lengthTemp;
      angle = angleTemp;
//      Serial.print("Tempangle:");
//      Serial.println(angle); 
//      Serial.print("Templength: ");
//      Serial.println(sideLength);
//      Serial.println("");      
      return 0;   // 表示数据获取成功
  }
    else
    {
      //Serial.println(cnt);
      return 1; //返回函数为值为1时代表数据获取失败
    }
}
