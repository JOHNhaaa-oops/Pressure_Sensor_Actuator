
volatile bool buttonFlag = 0; 

void buttonInterrupt();
void buttonInit(){
  pinMode(buttonPin, INPUT_PULLUP);  // 设置按钮引脚为输入模式，使用内部上拉电阻
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, CHANGE);
  
}

void buttonInterrupt() {
  unsigned long currentMillis = millis();
  volatile bool buttonState = 0;
  volatile bool lastButtonState = 0; 
  volatile unsigned long lastDebounceTime = 0;
  volatile unsigned long debounceDelay = 20;
  if (currentMillis - lastDebounceTime > debounceDelay) {
    // 获取按钮当前状态
    bool reading = digitalRead(buttonPin);
 
    // 如果按钮状态发生改变，更新按钮状态
    if (reading != lastButtonState) {
      lastDebounceTime = currentMillis; // 更新上次检测时间
      lastButtonState = reading; // 更新上次按钮状态
      buttonState = reading; // 更新当前按钮状态
      buttonFlag = !buttonFlag;
    }
  }


  
}
