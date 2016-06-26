#define TRIG   8
#define ECHO   9
#define LED    10

long measure() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, 3000) / 58;
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
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

void loop() {
  int distance = measure(); // distance in cm
  Serial.println(distance);

  if(distance < 10) {
    blink_led(100, 3);
  } else if(distance < 20) {
    blink_led(150, 2);
  }
}
