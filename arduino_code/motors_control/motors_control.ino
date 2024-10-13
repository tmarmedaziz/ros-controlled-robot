#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

std_msgs::Float32 float_msg;
ros::Publisher dhtSensor("sensors/temperature", &float_msg);

// ----- Subscriber
// sub callback
void subCallback(const std_msgs::Float32& msg) {
  // for test now
  Serial.print("Received: ");
  Serial.println(msg.data);

  digitalWrite(LED_BUILTIN, HIGH);

  if (msg.data == 1.0){
    digitalWrite(LED_BUILTIN, HIGH);
  } 
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

ros::Subscriber<std_msgs::Float32> motorsControlSub("robotcontrol/motors", &subCallback);


char hello[24] = "Hello, ROS from arduino!";

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
  nh.advertise(dhtSensor);
  nh.subscribe(motorsControlSub);

  Serial.begin(9600);
  pinMode(FRONT_RIGHT_DIRECTION_1_PIN, OUTPUT);
  pinMode(FRONT_LEFT_DIRECTION_1_PIN, OUTPUT);
  pinMode(REAR_RIGHT_DIRECTION_1_PIN, OUTPUT);
  pinMode(REAR_LEFT_DIRECTION_1_PIN, OUTPUT);

  pinMode(FRONT_RIGHT_DIRECTION_2_PIN, OUTPUT);
  pinMode(FRONT_LEFT_DIRECTION_2_PIN, OUTPUT);
  pinMode(REAR_RIGHT_DIRECTION_2_PIN, OUTPUT);
  pinMode(REAR_LEFT_DIRECTION_2_PIN, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

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

  float_msg.data = 24.0;
  dhtSensor.publish(&float_msg);

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
