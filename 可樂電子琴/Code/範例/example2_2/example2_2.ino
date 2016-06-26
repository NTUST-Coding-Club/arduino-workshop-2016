#include <CapacitiveSensor.h>
#define vcc 6
CapacitiveSensor cs=CapacitiveSensor(2,4);
int led=0;
void setup()                    
{
   pinMode(vcc,OUTPUT);
   Serial.begin(9600);
}
void loop()                    
{
    long total1 = cs.capacitiveSensor(30);
    int touch=0;
    if(total1>50)
        touch=1;
    else
        touch=0;
    if(touch==1){
      if(led==0){
        digitalWrite(vcc,1);
        led=1;
      }
      else{
        digitalWrite(vcc,0);
        led=0;
      }
      delay(300);
    }
    Serial.print(touch);
    Serial.print("\n");
    delay(10);
}



