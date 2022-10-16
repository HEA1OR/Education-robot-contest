#include<Servo.h>
Servo S;

void setup() {
  Serial.begin(9600);
  S.attach(13);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
}

void loop() {
 /******************空指令：xbee调整 *******************/
   delay(10000);
   Serial.flush();
   Serial.write(0x90);
   Serial.flush();
   delay(3000);
   
//   delay(5000);
//
////  /*****************第一阶段********************/
//
//   //测试，作为第一阶段开始的信号
//  Serial.flush();
//  Serial.write(0xA0);
//  Serial.flush();
//  delay(3000);
//

//  
//   //直走
//   
  Serial.flush();
  Serial.write(0xA1);
  Serial.flush();
  
  delay(7000);
  
  //同时右转
  
  Serial.flush(); 
  Serial.write(0xA2);
  Serial.flush();    
  delay(4000);
  
//五辆车去各自的地点
   
  Serial.flush(); 
  Serial.write(0xA3);
   Serial.flush();
  delay(14000);

//// 第一阶段结束信号
//   Serial.flush(); 
//  Serial.write(0xA4);
//   Serial.flush();
//  delay(3000);


//第二阶段  
  //这是私家车，救护车AB先出来
  Serial.flush(); 
  Serial.write(0xB1);
  Serial.flush();
  delay(10000);
  
  //救护车AB交互信号，私家车不应该有这个信号
  Serial.flush(); 
  Serial.write(0xB2);
  Serial.flush();
  delay(5000);

  //这个地方时间可能不够
  Serial.flush(); 
  Serial.write(0xB3);
  Serial.flush();
  delay(13000);

  // 救护车A 和 私家车的交互信号
  Serial.flush(); 
  Serial.write(0xB4);
  Serial.flush();
  delay(5000);
  
 // 继续走，给了这个信号之后，每个车的第二阶段结束
  Serial.flush(); 
  Serial.write(0xB5);
  Serial.flush();
  delay(32000);

  //私家车医院卸货信号
  Serial.flush(); 
  Serial.write(0xB6);
  Serial.flush();
  delay(6000);


// 第三阶段开始
  Serial.flush(); 
  Serial.write(0xC1);
  Serial.flush();
  delay(13000);
  
// 救护车AB均不接受 0xc2  0xc3 这两个信号

// 私家车和政府车交互信号
  Serial.flush(); 
  Serial.write(0xC2);
  Serial.flush();
  delay(7000);

// 私家车继续信号，政府社区车交互并继续信号，直到第三段结束
  Serial.flush(); 
  Serial.write(0xC3);
  Serial.flush();
  delay(45000);

//  // 第三阶段结束测试信号
//  Serial.flush(); 
//  Serial.write(0xC4);
//  Serial.flush();
//  delay(4000);


  // 第四阶段，回家啦
  Serial.flush(); 
  Serial.write(0xD1);
  Serial.flush();
  delay(9000);

// 转弯
  Serial.flush(); 
  Serial.write(0xD2);
  Serial.flush();
  delay(3000);
//直走
  Serial.flush(); 
  Serial.write(0xD3);
  Serial.flush();
  delay(7000);
//结束撒花
  Serial.flush(); 
  Serial.write(0xD4);
  Serial.flush();
  delay(10000);

}
