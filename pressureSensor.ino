/**********************************************************************
程序名称/Program name     : pressureSensor
团队/Team                : CUHK_BME
作者/Author              : johnZhou
日期/Date（YYYYMMDD）     : 2022/04/20
程序目的/Purpose          :  
三通道随身携带压力计，功能包括数据存储，压力显示，压力控制，时间设定
在主程序中主要包括以下内容：
setup：
1、串口初始化，波特率9600，最为稳定
2、SD卡初始化
3、时间模块初始化
4、文件名称初始化
5、OLED屏幕初始化

loop：
时间和压力串口显示，
时间和压力记录，
屏幕显示

-----------------------------------------------------------------------
修订历史/Revision History  
日期/Date    作者/Author      参考号/Ref    修订说明/Revision Description
30/7/2024   JZ              1             加入SD卡读写
31/7/2024   JZ              2             按键中断函数编写，加入软件消抖。文件名创建，文件名创建依据是时间,取消add_s法叠加string，直接采用sprintf。
31/7/2024   JZ              3             改用SD卡存储目标气压，取消EEPROM，气压值存在preSet.txt中，利用targetpressureInit传入单片机
1/8/2024    JZ              4             SD卡文件创建并写入完整时间，同一天的数据放在同一个TXT中，每一次上电写入时间并且绘制分割线
1/8/2024    JZ              5             加入LCD屏幕显示，显示时间的同时显示气压设定值，现在气压值，方案一：按钮触发屏幕显示，显示时间可以调整；方案二按钮触发数据记录
7/8/2024    JZ              6             加入呼吸式控制算法
-----------------------------------------------------------------------
其它说明：

***********************************************************************/


#include "microSD.h"
#include "buttonInterrupt.h"
#include "OLED.h"
#include "sensor.h"
#include "Control.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sdInit();
  timeInit();
  filenameInit();//仅仅是创建一个字符串供文件使用
  buttonInit();
  targetpressureInit();

  timerecordInit();//记录本次记录的时间和表格头,如果是当天第一次记录，会同时打开一份文件，并创建新的表格

  //OLED模块初始化
  OLEDInit();

  valveInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  OLEDDisplay();
  pressRead();
  dataRecord();
  pressInit();
  control();
  delay(100);

  

}

void testFunction(){
  if (buttonFlag==HIGH){
    parseDateTime(Rtc.GetDateTime());//Parse the time.
    Serial.print(SecondTime);
    OLEDDisplay();
    buttonFlag=LOW;
  }
  
}
