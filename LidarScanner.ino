#include <ros.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <sensor_msgs/Range.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

#define    LIDARLite_ADDRESS   0x62         
#define    RegisterMeasure     0x00         
#define    MeasureValue        0x04       
#define    RegisterHighLowB    0x8f

#define USB_USBCON

LIDARLite myLidarLite;

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;

ros::Publisher pub_range("lidarScanner", &range_msg);
unsigned long range_timer;
char frameid[] = "lidar_lite_v3";



void setup()
{
  Serial.begin(115200);
  //delay(1000);
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);

  nh.initNode();
  nh.advertise(pub_range);
  range_msg.radiation_type = sensor_msgs::Range::INFRARED;
  range_msg.header.frame_id = frameid;
  range_msg.header.stamp = nh.now();
  range_msg.field_of_view = 0.1;
  range_msg.min_range = 0.01;
  range_msg.max_range = 40.0;
}

void loop()
{
  range_msg.range = myLidarLite.distance()/100.0;
  range_msg.header.stamp = nh.now();
  pub_range.publish(&range_msg);
  range_timer = millis();
  nh.spinOnce();
  delay(10);
}
