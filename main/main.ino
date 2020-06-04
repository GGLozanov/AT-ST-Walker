#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN 125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 575 // this is the 'maximum' pulse length count (out of 4096)
#define LEG_COUNT 1 // TODO: Change to 2 legs
#define MAX_ANGLE 180

#define LEG_WAIT 2000 // delay for 1 leg movement
#define CYCLE_WAIT 1000 // delay for 1 cycle (1 dual servo movement)
#define MOVE_WAIT 500 // delay for 1 movement

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

int angle_to_pulse(int angle) {
  return map(angle, 0, MAX_ANGLE, SERVOMIN, SERVOMAX);
  // maps from degree out of 0 to 180 and to 125 to 575
}

void move_two(int servo1, int servo2, int angle) {
  pwm.setPWM(servo1, 0, angle_to_pulse(angle));
  delay(MOVE_WAIT);
  pwm.setPWM(servo2, 0, angle_to_pulse(angle));
}

void move_leg(int servo1, int servo2) {
  move_two(servo1, servo2, 85);
  
  delay(CYCLE_WAIT);
  
  move_two(servo1, servo2, 75);
  
  delay(CYCLE_WAIT);
  
  move_two(servo1, servo2, 65);
  
  delay(CYCLE_WAIT);
  
  move_two(servo1, servo2, 55);
  
  delay(CYCLE_WAIT);
  
  move_two(servo1, servo2, 45); // TODO: Optimise
}

void rebalance_leg(int servo1, int servo2) {
  move_two(servo1, servo2, 55);

  delay(CYCLE_WAIT);

  move_two(servo1, servo2, 65);
   
  delay(CYCLE_WAIT);

  move_two(servo1, servo2, 75);

  delay(CYCLE_WAIT);
  
  move_two(servo1, servo2, 90);
}

void walk_cycle(int servo1, int servo2) {
  move_leg(servo2, servo1); // start with secondary servo (lower leg)
  delay(LEG_WAIT);
  rebalance_leg(servo2, servo1);
  delay(LEG_WAIT); 
}

// the code inside loop() has been updated by Robojax
void loop() {
  Serial.println("Start of pwm");

  // 125 - 0 degrees
  // 575 - 180 degrees
  for(int servo = 0; servo < LEG_COUNT; servo += 2) { // go by 2 servos
      // int angl = random(0, 180);
      // int converted_pulse = angle_to_pulse(90);
      // pwm.setPWM(servo, 0, SERVOMIN);
      walk_cycle(servo, servo + 1);
     //  pwm.setPWM(servo, 0, SERVOMAX);
     // delay(500); 
    // }
  }

 
}
