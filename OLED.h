#include <lcdgfx.h>
#include <lcdgfx_gui.h>

DisplaySSD1306_128x64_I2C display(-1);
static char tempStr[5] = {0};


float Pres_Val[3]={0};

void OLEDInit()
{
    /* Select the font to use with menu and all font functions */
    display.setFixedFont( ssd1306xled_font6x8 );

    display.begin();

    /* Uncomment 2 lines below to rotate your ssd1306 display by 180 degrees. */
    // display.getInterface().flipVertical();
    // display.getInterface().flipHorizontal();

    display.clear();

}

void arkanoidUtoa(uint16_t b)
{
    utoa(b,tempStr,10);
}
void arkanoidFtoa(float b)
{
    String myStr = String(b);
    tempStr[0]=myStr[0];
    tempStr[1]=myStr[1];
    tempStr[2]=myStr[2];
    tempStr[3]=myStr[3];
    tempStr[4]=myStr[4];
    tempStr[5]='\0';
}

void OLEDDisplay(){


  // put your main code here, to run repeatedly:
if(buttonFlag==HIGH){
  parseDateTime(Rtc.GetDateTime());//Parse the time.
  arkanoidUtoa(DayTime);
  display.printFixed_oldStyle(0, 1, tempStr, STYLE_NORMAL);
  display.printFixed_oldStyle(15, 1, "/", STYLE_NORMAL);
  arkanoidUtoa(MonthTime);
  display.printFixed_oldStyle(20, 1, tempStr, STYLE_NORMAL);
  display.printFixed_oldStyle(35, 1, "/", STYLE_NORMAL);
  arkanoidUtoa(YearTime);
  display.printFixed_oldStyle(40, 1, tempStr, STYLE_NORMAL);

  arkanoidUtoa(HourTime);
  display.printFixed_oldStyle(70, 1, tempStr, STYLE_NORMAL);
  display.printFixed_oldStyle(85, 1, ":", STYLE_NORMAL);
  arkanoidUtoa(MinuteTime);
  display.printFixed_oldStyle(90, 1, tempStr, STYLE_NORMAL);
  display.printFixed_oldStyle(105, 1, ":", STYLE_NORMAL);
  arkanoidUtoa(SecondTime);
  display.printFixed_oldStyle(110, 1, tempStr, STYLE_NORMAL);
  
  display.printFixed_oldStyle(25, 10, "Recording...", STYLE_NORMAL);
  display.printFixed_oldStyle(40, 20, "Set", STYLE_NORMAL);
  display.printFixed_oldStyle(90, 20, "Sen", STYLE_NORMAL);
  display.drawLine(0, 25, 128, 25);
  display.printFixed_oldStyle(0, 35, "Ch1", STYLE_NORMAL);
  arkanoidFtoa(myVar[0]);
  display.printFixed_oldStyle(30, 35, tempStr, STYLE_NORMAL);
  arkanoidFtoa(Pres_Val[0]);
  display.printFixed_oldStyle(80, 35, tempStr, STYLE_NORMAL);
  
  display.printFixed_oldStyle(0, 45, "Ch2", STYLE_NORMAL);
  arkanoidFtoa(myVar[1]);
  display.printFixed_oldStyle(30, 45, tempStr, STYLE_NORMAL);
  arkanoidFtoa(Pres_Val[1]);
  display.printFixed_oldStyle(80, 45, tempStr, STYLE_NORMAL);
  
  display.printFixed_oldStyle(0, 55, "Ch3", STYLE_NORMAL);
  arkanoidFtoa(myVar[2]);
  display.printFixed_oldStyle(30, 55, tempStr, STYLE_NORMAL);
  arkanoidFtoa(Pres_Val[2]);
  display.printFixed_oldStyle(80, 55, tempStr, STYLE_NORMAL);
  
    
  }
  
  if(buttonFlag==LOW){
    display.clear();
  }
    
}


void dataRecord()//这个应该放进microSD里面，但是因为放进去感应不到全局变量，所以不放了
{    
  myFile = SD.open(fileName, FILE_WRITE);
  if (!myFile)
  {
    Serial.print("Data_Record_Failed");Serial.print(",");
  }
  myFile.print(HourTime);myFile.print("\t");
  myFile.print(MinuteTime);myFile.print("\t");
  myFile.print(SecondTime);myFile.print("\t");
  myFile.print(Pres_Val[0]);myFile.print("\t");
  myFile.print(Pres_Val[1]);myFile.print("\t");
  myFile.print(Pres_Val[2]);myFile.print("\t\n");
  
  myFile.close();
}
