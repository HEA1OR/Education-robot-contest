#include "led_matrix.h"

//这句话是什么意思，离谱
//找到了，实例化
//实例化软串口

//找不到很多关于SoftwareSerial的资料,找不到具体其函数是什么意思，如write  flush

SoftwareSerial led_matrix_serial(RX2, TX2);//RX,TX

void sendData2(byte data)
{

  //没搞懂这里的flush是什么意思
  // flush 等待正在发送的数据发送完成
  led_matrix_serial.flush();
  // write 以字节形式输出数据到串口，返回输出的字节数
  led_matrix_serial.write(data);
  led_matrix_serial.flush();
}
byte getData2()
{
  byte data = -1;
  led_matrix_serial.flush();
  // available 返回串口接收缓冲区的字节数
  if (led_matrix_serial.available())
    data = led_matrix_serial.read();
  return data;
}

void led_matrix_init()
{
  led_matrix_serial.begin(9600);
  led_matrix_serial.flush();
}
void open_flash(byte index)
{
  sendData2(index);
}
void close_flash()
{
  //这里为什么发送的是0xFF

  //0xFF 貌似是结束标志
  sendData2('Z');
}

//判断是否结束
int flash_over_judge()
{
  //如果不等于0xFF 则表明没有结束
  //等于0xFF，表明flash应该结束
  if (getData2() != 0xFF)
    return 1;
  else
    return 0;
}
