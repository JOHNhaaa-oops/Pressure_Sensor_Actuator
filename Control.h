void valveInit()
{
  pinMode(Valve_1, OUTPUT);   //airbag 1         // Valve setup
  pinMode(Valve_2, OUTPUT);   //airbag 2
  pinMode(Valve_3, OUTPUT);   //Release Valve
  pinMode(pump, OUTPUT);   //
  digitalWrite(Valve_1, LOW);
  digitalWrite(Valve_2, LOW);
  digitalWrite(Valve_3, LOW);
  digitalWrite(pump, LOW);
}

int pressure_index[2] = {0};
float pressure_history[2][3];


void control() {

//the number of airbag
    // 读取压力传感器数据
for(int i=0;i<2;i++)
{
  float TARGET_PRESSURE = myVar[i];
  
  // 根据压力值控制输出
  if (Pres_Val[i] < TARGET_PRESSURE) {
//     压力偏低,开启充气阀和泵
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5+i, HIGH);
  
  digitalWrite(pump,HIGH);
  digitalWrite(Valve_3, LOW);
  delay(250);
  } else if (Pres_Val[i] > TARGET_PRESSURE + TOLERANCE) {
    // 压力偏高,开启放气阀
    
  digitalWrite(Valve_3, HIGH);
  digitalWrite(5+i, HIGH);
  digitalWrite(pump,LOW);
  delay(250);

  } else {
    // 压力在允许范围内,关闭所有输出
  digitalWrite(Valve_1, LOW);
  digitalWrite(Valve_2, LOW);
  digitalWrite(Valve_3, LOW);
  digitalWrite(pump, LOW);

  }

}
    
  
}
