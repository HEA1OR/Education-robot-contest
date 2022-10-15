#include "compass.h"

//SoftwareSerial compassSerial(10, 11); 

   
float angle;
uint8_t data_rx_buff[10];   // unit8_t 就是 unsigned char


//下面四行的作用是将数据拆分为字节的形式

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )


//这一大段注释的代码没看

//extern Servo motorL, motorR;
//float currentAngle = 0;
//int x, y, z;
//int xOffset, yOffset;
//
//void compassInit()
//{
//	Serial.begin(115200);//bluetooth
//	Wire.begin();
//	//Put the HMC5883 IC into the correct operating mode
//	Wire.beginTransmission(address); //open communication with HMC58837
//	Wire.write(0x02); //select mode register
//	Wire.write(0x00); //continuous measurement mode
//	Wire.endTransmission();
//}
//
//void compassCalibration() {
//	int Xmin, Xmax, Ymin, Ymax, count = 0;
//	motorL.write(180);
//	motorR.write(180);
//	for (; count<4000; count++)
//	{
//		Wire.beginTransmission(address);
//		Wire.write(0x03); //select register 3, X MSB register
//		Wire.endTransmission();
//
//
//		//Read data from each axis, 2 registers per axis
//		Wire.requestFrom(address, 6);
//		if (6 <= Wire.available()) {
//			x = Wire.read() << 8; //X msb
//			x |= Wire.read(); //X lsb
//			z = Wire.read() << 8; //Z msb
//			z |= Wire.read(); //Z lsb
//			y = Wire.read() << 8; //Y msb
//			y |= Wire.read(); //Y lsb
//		}
//		if (count == 0)
//			Xmin = Xmax = x, Ymin = Ymax = y;
//		else {
//			if (x>Xmax) Xmax = x;
//			else if (x<Xmin) Xmin = x;
//			if (y>Ymax) Ymax = y;
//			else if (y<Ymin) Ymin = y;
//		}
//		delay(1);
//	}
//	xOffset = (Xmin + Xmax) / 2;
//	yOffset = (Ymin + Ymax) / 2;
//	//Serial.listen();
//	Serial.println(xOffset);
//	Serial.println(yOffset);  
//}
//
//float getAngle() {
//	//Tell the HMC5883 where to begin reading data
//	Wire.beginTransmission(address);
//	Wire.write(0x03); //select register 3, X MSB register
//	Wire.endTransmission();
//
//	//Read data from each axis, 2 registers per axis
//	Wire.requestFrom(address, 6);
//	if (6 <= Wire.available()) {
//		x = Wire.read() << 8; //X msb
//		x |= Wire.read(); //X lsb
//		z = Wire.read() << 8; //Z msb
//		z |= Wire.read(); //Z lsb
//		y = Wire.read() << 8; //Y msb
//		y |= Wire.read(); //Y lsb
//	}
//	float angle = atan2((y - Yoffset), (x - Xoffset)) * 180 / PI + 180;
//	return angle;
//}


//好像是SPI双机通信的代码，串口结束传输数据时就结束程序。pad上做了一点笔记

//看不太懂这块代码，串口发送结束时SPSR为0x80，这是循环结束，停止接受信息。
//SPSR寄存器的SPIF标志位如果为0 ，就继续等待，直到数据发送完du成或者接收完成
//但是这里还是不太懂

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
  float b=0;

  while(1)
  {

//想要理解这块代码，就要好好理解SPI_SlaveReceive()这个函数及其SPI模块内部的东西

    // temp 获得传输的数据
    
    temp=SPI_SlaveReceive();

    //只要temp不是0xAA ,这个while(1)就会一直执行，直到temp为0xAA
    //为什么是0xAA，还不知道
    
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
  
  //猜测cnt==4时为传输数据成功，其他情况不成功
  
  if(cnt==4)
  {
    BYTE3(b)=data_rx_buff[0];
   // Serial.write(BYTE3(b));
    BYTE2(b)=data_rx_buff[1];
  //  Serial.write(BYTE2(b));
    BYTE1(b)=data_rx_buff[2];
   // Serial.write(BYTE1(b));
    BYTE0(b)=data_rx_buff[3];
   // Serial.write(BYTE0(b));

   // b的值是0
    return b;
  }
    else
    {
      //Serial.println(cnt);
      return 1;
    }
}

void compassInit()
{
  //Serial.begin(115200);

// MISO SS 都是什么管脚？

  // MISO 代表数据输出，SS代表使能端

  
//car3这里加个delay试试
  delay(5000);

  
  pinMode(MISO, OUTPUT);

  //将使能端设置为低电平，使其工作
  digitalWrite(SS, LOW);

// 将SPI设置为从机
  
  SPCR |= _BV(SPE);
}

//获得陀螺仪传回的角度
void get_angle(void)
{
  //这是一个void函数，它也是直接把测得的角度直接传进了全局变量angle中
  Serial.println("step");
  angle = receive_data();
  
  //angle==1代表接受数据不成功
  while (angle == 1)
    {
      
      angle = receive_data();
    }

   //不成功就一直做
  //Serial.println(angle);
}
