 /*
 * Original sourse: https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 * This is the Arduino code PAC6985 16 channel servo controller
 * watch the video for details and demo http://youtu.be/y8X9X10Tn1k
 *  * 
 * Written by Ahmad Nejrabi for Robojax Video channel www.Robojax.com
 * Date: Dec 15, 2017, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * 
 */
/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

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
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)
#define SERVO_COUNT 2
#define ANGLE_MARGIN 20
#define MAX_ANGLE 180
#define SERVO_LOOPS 5

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

int angle_to_pulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
  // maps from degree out of 0 to 180 and to 125 to 575
}

// the code inside loop() has been updated by Robojax
void loop() {
  Serial.println("Start of pwm");

  // 125 - 0 degrees
  // 575 - 180 degrees
  for(int servo = 0; servo < SERVO_COUNT; servo++) {
    for(int i = 0; i < SERVO_LOOPS; i++) {
      int angl = random(0, 180);
      int converted_pulse = angle_to_pulse(angl);
      // pwm.setPWM(servo, 0, SERVOMIN);
      delay(500);
      pwm.setPWM(servo, 0, converted_pulse);
      delay(500);
     //  pwm.setPWM(servo, 0, SERVOMAX);
     // delay(500); 
    }
  }

 
}
