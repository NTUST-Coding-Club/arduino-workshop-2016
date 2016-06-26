#include <CapacitiveSensor.h>
CapacitiveSensor cs= CapacitiveSensor(2,4);
void setup()                    
{
   Serial.begin(9600);
}
void loop()                    
{
    long total1 =  cs.capacitiveSensor(30);
    Serial.print(total1);
    Serial.print("\n");
    delay(10);
}
