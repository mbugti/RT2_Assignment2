"""
.. module:: user_interface
   :platform: Unix
   :synopsis: Python module for the user Interface
.. moduleauthor:: Aatheethyaa Dhanasekaran 

This node implements an user interface and the user will be able to start/stop using the user interface in terminal

Service:
   /user_interface
   
"""

import rospy
import time
from rt2_assignment1.srv import Command
def main():
    """
    This function initializes the ROS node and waits for the user to
    insert *start* or *stop* to control the robot, by relying on the
    `rospy <http://wiki.ros.org/rospy/>`_ module.
    
    The user message is passed to the service``user_interface``,
    advertised by :mod:`go_to_point`.

    """
    rospy.init_node('user_interface')
    ui_client = rospy.ServiceProxy('/user_interface', Command)
    time.sleep(10)
    rate = rospy.Rate(20)
    x = int(input("\nPress 1 to start the robot "))
    while not rospy.is_shutdown():
        if (x == 1):
            ui_client("start")
            x = int(input("\nPress 0 to stop the robot "))
        else:
            print("Please wait, the robot is going to stop when the position will be reached")
            ui_client("stop")
            x = int(input("\nPress 1 to start the robot "))
            
if __name__ == '__main__':
    main()
