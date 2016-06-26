#include <CapacitiveSensor.h>
CapacitiveSensor cs= CapacitiveSensor(2,4);
void setup()                    
{
   Serial.begin(9600);
}
void loop()                    
{
    long total1 =  cs.capacitiveSensor(30);
    int touch=0;
    if(total1>50){
      touch=1;
    }
    else{
      touch=0;
    }
    Serial.print(touch);
    Serial.print("\n");
    delay(10);
}
