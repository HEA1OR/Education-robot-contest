#include "encoder.h"


//volatile 防止编译器对这个变量进行优化
volatile int countLeft, countRight;

void encoderInit()
{
	pinMode(2, INPUT);    //设置2号脚为输入
  
	pinMode(3, INPUT);
  
	countLeft = 0;
	countRight = 0;

 //在Arduino中，中断源可选值为0或1，一般分别对应2号和3号引脚


//那么问题来了，2,3号脚为什么会电平变化

//我好像知道了，这是编码器，轮子上的黑白相间的圆盘，每次电平发生变化即为黑白变化的点，所以 路程=变化次数*弧长
 
 // 当2号脚的电平发生变化时，中断blinkLeft
 // 当3号脚的电平发生变化时，中断blinkRight
 
	attachInterrupt(0, blinkLeft, CHANGE);   //中断函数 attachInterrupt，意思是中断发生时，其他函数不执行，执行 blinkLeft这个函数
	attachInterrupt(1, blinkRight, CHANGE);
}

void blinkLeft() {
	countLeft++;
}

void blinkRight() {
	countRight++;
}
