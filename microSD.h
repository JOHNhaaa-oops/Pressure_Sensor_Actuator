#include <SPI.h>
#include <SD.h>
#include <RtcDS1302.h>      //RTC by Makuna



#include "pinSet.h"
File myFile;

char fileName[20];//避免使用string而造成的内存分配混乱问题
uint8_t DayTime,MonthTime,HourTime,MinuteTime,SecondTime,YearTime;
float myVar[3]={0};
ThreeWire myWire(16,15,17); // IO, SCLK, CE 2560:23,22,24  nano:16,15,17
RtcDS1302<ThreeWire> Rtc(myWire);

void parseDateTime(const RtcDateTime& dt);

void sdInit()
{ 
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  if (!SD.begin(CS))
  {
      Serial.println("SD initialization failed!");
      return;
  }
  Serial.println("SD initialization done.");
}



void targetpressureInit(){

myFile = SD.open("preSet.txt"); 
  if (myFile)
  {
    while (myFile.available())
    {
      //parse the next 4 values out of the file:
      myVar[0] = myFile.parseFloat();
      myVar[1] = myFile.parseFloat();
      myVar[2] = myFile.parseFloat();
      
      Serial.println(myVar[0]);
      Serial.println(myVar[1]);
      Serial.println(myVar[2]);
      delay(1000);
      //go back to the top for the next line...
      //or ....
    }//while data available
  }
  else {
    Serial.println("error opening the data file");
  }
  myFile.close();
}


void filenameInit(){
  parseDateTime(Rtc.GetDateTime());
  
  sprintf(fileName, "%d_%d_%d.txt", DayTime, MonthTime, YearTime);
  Serial.println(fileName);
  
  Serial.println("Filename generated successfully!");
  
}

void timeInit()
{
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

  if (!Rtc.IsDateTimeValid()) 
    {
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

  if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

  if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
}


void parseDateTime(const RtcDateTime& dt)
{
    DayTime= dt.Day();
    MonthTime = dt.Month();
    YearTime = dt.Year()-2000;
    HourTime = dt.Hour();
    MinuteTime = dt.Minute();
    SecondTime = dt.Second(); 
}

void timerecordInit(){
  myFile = SD.open(fileName, FILE_WRITE);
  if (!myFile)
  {
    Serial.print("Time_Record_Failed");Serial.print(",");
  }
  myFile.print(DayTime); myFile.print("/");
  myFile.print(MonthTime);myFile.print("/");
  myFile.print(YearTime);myFile.print(",");
  myFile.print(HourTime);myFile.print(":");
  myFile.print(MinuteTime);myFile.print(":");
  myFile.print(SecondTime);myFile.println(",");   

  myFile.print("Hour\t");
  myFile.print("Min\t");
  myFile.print("Sec\t");
  myFile.print("Sen1\t");
  myFile.print("Sen2\t");
  myFile.print("Sen3\t\n");
  myFile.println("------------------------------------\n"); 
  myFile.close();
  
}//每次上电都写时间并且绘制分割线
