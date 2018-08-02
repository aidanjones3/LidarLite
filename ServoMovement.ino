#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>

// Globals
LIDARLite lidarLite;
int cal_cnt = 0;
const int HOR_SERVO_PIN = 3;    // Pin number for the horizontal rotation servo - will not change

Servo servo1;

void setup()
{
  Serial.begin(9600); // Initialize serial connection to display distance readings

  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations

  servo1.attach(HOR_SERVO_PIN); //attach the servo on pin SERVO_PIN

    
  servo1.write(0);  //send the servo to '0' degrees
  delay(1000);      //wait for the servo to move before moving again
  
  servo1.write(90);  //send the servo to '90' degrees
  delay(1000);       //wait for the servo to move before moving again
    
  servo1.write(180);  //send the servo to '180' degrees

}

void loop()
{
  int dist;

  // At the beginning of every 100 readings,
  // take a measurement with receiver bias correction
  if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }

  // Increment reading counter
  cal_cnt++;
  cal_cnt = cal_cnt % 100;

  // Display distance
  Serial.print(dist);
  Serial.println(" cm");



  delay(10);
}
