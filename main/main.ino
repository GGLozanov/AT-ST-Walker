#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 575 // this is the 'maximum' pulse length count (out of 4096)
#define SERVO_COUNT 4 // TODO: Change to 2 legs
#define MAX_ANGLE 180

#define LEG_WAIT 2000 // delay for 1 leg movement
#define CYCLE_WAIT 1000 // delay for 1 cycle (1 dual servo movement)
#define MOVE_WAIT 200 // delay for 1 movement

// TODO: Make it function for both legs at the same time (pass in servo % 2 == 0 and servo % 2 != 0)

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!

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

void move_two(int calf, int foot, int angle) {
  pwm.setPWM(calf, 0, angle_to_pulse(angle));
  delay(MOVE_WAIT);
  pwm.setPWM(foot, 0, angle_to_pulse(angle));
}

void move_leg(int calf, int foot, int leg_angle_offset) { // 0 in 45* => 45* in 135*
  /* move_two(calf, foot, 85);
  
  delay(CYCLE_WAIT);
  
  move_two(calf, foot, 75);
  
  delay(CYCLE_WAIT);
  
  move_two(calf, foot, 65);
  
  delay(CYCLE_WAIT);
  
  move_two(calf, foot, 55);
  
  delay(CYCLE_WAIT);
  
  move_two(calf, foot, 45); // TODO: Optimise in loop */

  for(float angle = 85 + leg_angle_offset; angle > 45 + leg_angle_offset; angle -= 10) {
    move_two(calf, foot, angle);  
  }
}

// 45 -> 90 -> move

// 90 -> 45 -> rebalance

// 90 -> 135

// 135 -> 90

void rebalance_leg(int calf, int foot, int leg_angle_offset) { // 45* in 135*
  /* move_two(calf, foot, 55);

  delay(CYCLE_WAIT);

  move_two(calf, foot, 65);
   
  delay(CYCLE_WAIT);

  move_two(calf, foot, 75);

  delay(CYCLE_WAIT);
  
  move_two(calf, foot, 90); // TODO: Optimise in loop */

   for(float angle = 55 + leg_angle_offset; angle < 90 + leg_angle_offset; angle += 11.6) {
    move_two(calf, foot, angle);  
  }
}

void walk_cycle(int calf, int foot, int leg_angle_offset) {
  move_leg(foot, calf, leg_angle_offset); // start with secondary servo (foot)
  rebalance_leg(foot, calf, leg_angle_offset);
}

// the code inside loop() has been updated by Robojax
void loop() {
  Serial.println("Start of pwm");

  // 125 - 0 degrees
  // 575 - 180 degrees

  int angle_offset = 0;
  for(int servo = 0; servo < SERVO_COUNT; servo += 2, angle_offset += 45) { // go by 2 servos
      // servo = calf
      // servo + 1 = foot
      walk_cycle(servo, servo + 1, angle_offset);
  }
  

 
}
