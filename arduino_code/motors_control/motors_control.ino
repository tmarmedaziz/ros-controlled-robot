#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle rh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "Hello, ROS from arduino!";

int FRONT_RIGHT_DIRECTION_1_PIN = 4;
int FRONT_LEFT_DIRECTION_1_PIN = 7;
int REAR_RIGHT_DIRECTION_1_PIN = 3;
int REAR_LEFT_DIRECTION_1_PIN = 8;

int FRONT_RIGHT_DIRECTION_2_PIN = 5;
int FRONT_LEFT_DIRECTION_2_PIN = 6;
int REAR_RIGHT_DIRECTION_2_PIN = 2;
int REAR_LEFT_DIRECTION_2_PIN = 9;

void controlMotorDirection(int in1, int in2, int direction);

void setup() {
  nh.initNode();
  nh.advertise(chatter);

  Serial.begin(9600);
  pinMode(FRONT_RIGHT_DIRECTION_1_PIN, OUTPUT);
  pinMode(FRONT_LEFT_DIRECTION_1_PIN, OUTPUT);
  pinMode(REAR_RIGHT_DIRECTION_1_PIN, OUTPUT);
  pinMode(REAR_LEFT_DIRECTION_1_PIN, OUTPUT);

  pinMode(FRONT_RIGHT_DIRECTION_2_PIN, OUTPUT);
  pinMode(FRONT_LEFT_DIRECTION_2_PIN, OUTPUT);
  pinMode(REAR_RIGHT_DIRECTION_2_PIN, OUTPUT);
  pinMode(REAR_LEFT_DIRECTION_2_PIN, OUTPUT);

  controlMotorDirection(FRONT_RIGHT_DIRECTION_1_PIN, FRONT_RIGHT_DIRECTION_2_PIN, 0);
  controlMotorDirection(FRONT_LEFT_DIRECTION_1_PIN, FRONT_LEFT_DIRECTION_2_PIN, 0);
  controlMotorDirection(REAR_RIGHT_DIRECTION_1_PIN, REAR_RIGHT_DIRECTION_2_PIN, 0);
  controlMotorDirection(REAR_LEFT_DIRECTION_1_PIN, REAR_LEFT_DIRECTION_2_PIN, 0);
}

void loop() {
  // Turn on FRONT_RIGHT all motors
  controlMotorDirection(FRONT_RIGHT_DIRECTION_1_PIN, FRONT_RIGHT_DIRECTION_2_PIN, 1);
  controlMotorDirection(FRONT_LEFT_DIRECTION_1_PIN, FRONT_LEFT_DIRECTION_2_PIN, 1);
  controlMotorDirection(REAR_RIGHT_DIRECTION_1_PIN, REAR_RIGHT_DIRECTION_2_PIN, 1);
  controlMotorDirection(REAR_LEFT_DIRECTION_1_PIN, REAR_LEFT_DIRECTION_2_PIN, 1);
  Serial.println("FRONT_RIGHT motor running");
  delay(2000);  // Run for 2 seconds

  // Turn off all motors
  controlMotorDirection(FRONT_RIGHT_DIRECTION_1_PIN, FRONT_RIGHT_DIRECTION_2_PIN, 0);
  controlMotorDirection(FRONT_LEFT_DIRECTION_1_PIN, FRONT_LEFT_DIRECTION_2_PIN, 0);
  controlMotorDirection(REAR_RIGHT_DIRECTION_1_PIN, REAR_RIGHT_DIRECTION_2_PIN, 0);
  controlMotorDirection(REAR_LEFT_DIRECTION_1_PIN, REAR_LEFT_DIRECTION_2_PIN, 0);
  delay(500);  // wait for 500ms

  str_msg.data = hello;
  chatter.publish(&str_msg);
  nh.spinOnce();
}

void controlMotorDirection(int in1, int in2, int direction) {
  // 0 to  stop motro, 1 for dir1 and -1 for dir2
  if (direction == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  } else if (direction == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else if (direction == -1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    return;
  }
}
