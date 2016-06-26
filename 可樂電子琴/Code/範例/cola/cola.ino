#include <CapacitiveSensor.h>
#include "pitches.h"
CapacitiveSensor cs=CapacitiveSensor(2,4);
#define vcc 6
#define buzzer 10
#define t NOTE_C5 //Do
void setup()                    
{
   pinMode(vcc,OUTPUT);
   pinMode(buzzer,OUTPUT);
   Serial.begin(9600);
}
void loop()                    
{
    long total1 =  cs.capacitiveSensor(30);
    int touch=0;
    if(total1>300)
        touch=1;
    else
        touch=0;
    if(touch==1){
      digitalWrite(vcc,1);
      tone(buzzer,t,100);
      digitalWrite(vcc,0);
    }
    Serial.print(touch);
    Serial.print("\n");
    delay(10);
}

