

void pressInit()
{
  
    pinMode(14, INPUT);               // Pressure sensor setup
    pinMode(A6, INPUT); 
    pinMode(A7, INPUT); 
}


void pressRead(){ 
  Pres_Val[0] = 0.054*(analogRead(PresSen_1)-41);     //Transfer to Kpa       
  Pres_Val[1] = 0.054*(analogRead(PresSen_2)-41);      //Transfer to Kpa
  Pres_Val[2] = 0.054*(analogRead(PresSen_3)-41);      //Adding the error

}
