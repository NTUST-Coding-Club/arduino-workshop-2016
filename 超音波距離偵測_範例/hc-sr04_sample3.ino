#define TRIG   8
#define ECHO   9
#define LED    10
#define BUZZER 11

long measure() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH) / 58;
}

void blink_led(int delay_t, int n)
{
  for(int i = 0; i < n; i++) {
    digitalWrite(LED, HIGH);
    delay(delay_t);
    digitalWrite(LED, LOW);
    delay(delay_t);
  }
}

void beep(int freq, int delay_time, int n) {
  for(int i = 0; i < n; i++) {
    tone(BUZZER, freq);
    blink_led(delay_time / 2, 2);
    noTone(BUZZER);
    blink_led(delay_time / 2, 2);
  }
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int distance = measure(); // in cm
  Serial.println(distance);
  if(distance < 10) {
    beep(1000, 100, 1);
  } else if (distance < 15) {
    beep(950, 200, 3);
  } else if (distance < 18) {
    beep(900, 300, 3);
  }
}
