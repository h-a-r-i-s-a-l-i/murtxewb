/*
  Light-Following Planter — EWB x MURT Component Workshop

  One sketch, three exercises. Arduino only allows one setup() and one
  loop() per sketch, so set EXERCISE below to the one you're working on
  and upload again:

    1  Exercise 01 — Read the light sensors   (Serial Monitor, 9600 baud)
    2  Exercise 02 — Servo code               (servo sweeps 0°–180°)
    3  Full code   — Integration              (tray follows the light)

  Wiring (same for every exercise):
    Left LDR   -> A0, with a 10 kΩ resistor from A0 to GND
    Right LDR  -> A1, with a 10 kΩ resistor from A1 to GND
    Servo      -> signal (orange) D9, red 5V, brown GND
    Nano 5V and GND -> the breadboard rails; bridge bottom rails to top rails
*/

#define EXERCISE 3

#include <Servo.h>


/* =====================================================================
   EXERCISE 01 — Read the light sensors
   Open Tools > Serial Monitor at 9600 baud. Cover each LDR with your
   finger: its number should drop.
   ===================================================================== */
#if EXERCISE == 1

void setup() {
  Serial.begin(9600);
}

void loop() {
  int left  = analogRead(A0);
  int right = analogRead(A1);
  Serial.print(left);
  Serial.print("\t");
  Serial.println(right);
  delay(100);
}


/* =====================================================================
   EXERCISE 02 — Servo code
   Signal (orange) -> D9. After uploading, the servo should sweep
   back and forth between 0° and 180°.
   ===================================================================== */
#elif EXERCISE == 2

Servo tray;

void setup() {
  tray.attach(9);
}

void loop() {
  tray.write(0);
  delay(400);
  tray.write(180);
  delay(400);
}


/* =====================================================================
   FULL CODE — Integration (Exercise 03)
   Shine a flashlight on one side: the servo should turn toward it.
   Turns away from the light? Swap A0 and A1.

   The logic, step by step:
     1. Start the servo at 90°
     2. Read both LDRs: diff = left - right
     3. If |diff| < DEADBAND, do nothing (stops jitter)
     4. Left brighter  -> angle - 1
     5. Right brighter -> angle + 1
     6. constrain(angle, 0, 180), then write()
     7. delay(20) and loop
   ===================================================================== */
#elif EXERCISE == 3

Servo tray;
int angle = 90;
const int DEADBAND = 30;

void setup() {
  tray.attach(9);
  tray.write(angle);
  Serial.begin(9600);
}

void loop() {
  int left  = analogRead(A0);
  int right = analogRead(A1);
  int diff  = left - right;

  Serial.print(left);
  Serial.print("\t");
  Serial.print(right);
  Serial.print("\t");
  Serial.println(diff);

  if (diff > DEADBAND) angle--;
  else if (diff < -DEADBAND) angle++;

  angle = constrain(angle, 0, 180);
  tray.write(angle);
  delay(20);
}


#else
#error "Set EXERCISE to 1, 2 or 3 at the top of the sketch."
#endif
