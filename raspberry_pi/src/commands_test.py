#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32
import sys

def publish_value(value):
    rospy.init_node('command_line_publisher', anonymous=True)
    
    pub = rospy.Publisher('/robotcontrol/motors', Float32, queue_size=10)
    
    rospy.sleep(1)

    msg = Float32()
    msg.data = value

    pub.publish(msg)
    rospy.loginfo(f"Published to /output_topic: {msg.data}")

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python command_line_publisher.py <value>")
        sys.exit(1)

    try:
        value = float(sys.argv[1])  
        publish_value(value)
    except ValueError:
        print("Please provide a valid float value.")
        sys.exit(1)
