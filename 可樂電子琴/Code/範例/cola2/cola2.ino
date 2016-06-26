#include <CapacitiveSensor.h>
#include "pitches.h"
#define vcc 6
#define buzzer 10
CapacitiveSensor cs1=CapacitiveSensor(2,3);
CapacitiveSensor cs2=CapacitiveSensor(2,4);
CapacitiveSensor cs3=CapacitiveSensor(2,5);
CapacitiveSensor cs4=CapacitiveSensor(2,7);
CapacitiveSensor cs5=CapacitiveSensor(2,8);
int t[]={NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5};
void setup()                    
{
   pinMode(vcc,OUTPUT);
   pinMode(buzzer,OUTPUT);
   Serial.begin(9600);
}
void loop()                    
{
    long total[5];
    total[0]=cs1.capacitiveSensor(30);
    total[1]=cs1.capacitiveSensor(30);
    total[2]=cs1.capacitiveSensor(30);
    total[3]=cs1.capacitiveSensor(30);
    total[4]=cs1.capacitiveSensor(30);
    int touch[5];
    for(int i=0;i<5;i++){
        if(total[i]>300)
            touch[i]=1;
        else
            touch[i]=0;
        if(touch[i]==1){
            digitalWrite(vcc,1);
            tone(buzzer,t[i],100);
            digitalWrite(vcc,0);
            break;
        }
    }
    delay(10);
}

