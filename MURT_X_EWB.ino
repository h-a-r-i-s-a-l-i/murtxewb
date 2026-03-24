//MURT X EWB Workshop
#include <Servo.h>

#define ECHO_PIN 4
#define TRIG_PIN 2
#define SERVO_PIN 9

#define THRESHOLD 20

Servo  murt;

void setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  murt.attach(SERVO_PIN);
  
  Serial.begin(9600);
}

int calc_dist() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(4);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long signal = pulseIn(ECHO_PIN, HIGH);
  // long inches = signal / 74 / 2; 
  long cm = signal / 29 / 2; 
  delay(100);
  return cm;
}

int ready = 0;

void loop() {
  if (ready == 0) {
    float distance = calc_dist();
    if (distance < THRESHOLD) {
      ready = 1;
    }
  }
  
  if (ready == 1) {
    murt.write(180);
    delay(5000);
    murt.write(0);
    ready = 0;
    delay(100);
  }
}