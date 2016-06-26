#include <CapacitiveSensor.h>
#define vcc 6
CapacitiveSensor cs=CapacitiveSensor(2,4);
void setup()                    
{
   pinMode(vcc,OUTPUT);
   Serial.begin(9600);
}
void loop()                    
{
    digitalWrite(vcc,0);
    long total1 =  cs.capacitiveSensor(30);
    int touch=0;
    if(total1>50)
        touch=1;
    else
        touch=0;
    if(touch==1){
      digitalWrite(vcc,1);
      delay(300);
    }
    Serial.print(touch);
    Serial.print("\n");
    delay(10);
}

