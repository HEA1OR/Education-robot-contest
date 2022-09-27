#include "compass.h"

  //SoftwareSerial compassSerial(10, 11);  // RX, TX 锟斤拷锟斤拷compass锟斤拷锟斤拷
float angle;
uint8_t data_rx_buff[10];

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

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
//	Serial.println(yOffset);  //锟斤拷锟斤拷殖锟斤拷懦锟斤拷锟斤拷锟叫ｏ拷锟斤拷锟街碉拷锟斤拷薷锟絚ompass.h锟叫宏定锟斤拷值
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

char SPI_SlaveReceive(void){
      while(!(SPSR & (1<<SPIF)));
      return SPDR;
}

float receive_data(void)
{
  uint8_t cnt=0,temp=0;
  float b=0;

  while(1)
  {
    temp=SPI_SlaveReceive();
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
  //接块结束
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
  pinMode(MISO, OUTPUT);
  digitalWrite(SS, LOW);
  SPCR |= _BV(SPE);
}

void get_angle(void)
{
  angle = receive_data();
  while (angle == 1)
    angle = receive_data();
  Serial.println(angle);
}
