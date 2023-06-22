/**
 * \file state_machine.cpp
 * \brief This files defines a finite state machine for controlling the robot in the Gazebo environment
 * \author Aatheethyaa Dhanasekaran
 * \version 1.0
 * \date 05/02/2022
 * 
 * \details
 * 
 * Services : <BR>
 * 		/user_interface
 * 
 * Clients : 
 * 		/position_server 
 * 
 * Action Client : 
 * 		/go_to_point 
 * 
 *  Description :
 *  
 *  This node implements the state machine for the input to be provided by the user 
 *  to control the holonomic robot. It includes:
 *  - An Action client "go_to_point" that interacts with the action
 *    "Planning" to:
 * 		- set a new goal randomly when the user presses 1 to start 
 * 		- check if the goal has been reached by the robot
 * 		- check if the goal has been cancelled,when the user presses 0 to stop the robot
 * 		- Define the new state
 *  - A Service server that advertise the command line user interface
* 	- A Service client that requires a new target postion from the 
* 		/position_server
 */


#include "ros/ros.h"
#include "rt2_assignment1/Command.h"
#include "rt2_assignment1/RandomPosition.h"
#include "rt2_assignment1/PlanningAction.h"
#include "actionlib/client/simple_action_client.h"
#include "actionlib/client/terminal_state.h"

bool start = false;

/**
 * bool user_interface(req, res)
 * 
 * \brief Function implemented to get the user's command 
 * 
 * \param req: request done by the client (start or stop the robot)
 * 
 * \param res: respondse generated from the server
 * 
 * \return true if the server finishes to set the "start" variable on the basis of the command received 
 * 
 * description:
 *    This callback checks if the command from the /user_interface node is "start", 
 *    in this case sets to true the correspective variable, otherwise sets it to false
 **/
bool user_interface(rt2_assignment1::Command::Request &req, rt2_assignment1::Command::Response &res){
    if (req.command == "start"){
    	start = true;
    }
    else {
    	start = false;
    }
    return true;
}

/** 
 * int main(argc, argv)
 * 
 * \brief Main function of the node
 * 
 * \param argc: the number of argument passed as parameters
 * 
 * \param argv: the vector of string containing each argument
 * 
 * \return 0 when the program ends
 * 
 * description:
 *    The main function, makes all the initializations as follows:
 * 
 *    client_rp: to get a random goal at custom service RandomPosition
 *    goal_position: the random goal generated as a PositionGoal and send it to /go_to_point node
 *    service: read the command sent by the user from the Command service custom message
 * 
 *    After initializations it generates a request for the random position in interval [-5, 5], then executes an infinite loop 
 *    in which it gets the random position and sends it as a goal position to the /go_to_point node and waits untill
 *    the target is reached. In case in wich the command from /user_interface is "stop" (so start==false) the goal is cancelled
 *    and the robot is stopped, otherwise the loop is executed again.
 *    
 **/

int main(int argc, char **argv)
{
   ros::init(argc, argv, "state_machine");
   ros::NodeHandle n;
   ros::ServiceServer service= n.advertiseService("/user_interface", user_interface);
   ros::ServiceClient client_rp = n.serviceClient<rt2_assignment1::RandomPosition>("/position_server");
   actionlib::SimpleActionClient <rt2_assignment1::PlanningAction> ac("/go_to_point", true);
   
   rt2_assignment1::PlanningGoal goal;
   rt2_assignment1::RandomPosition rp;
   rp.request.x_max = 5.0;
   rp.request.x_min = -5.0;
   rp.request.y_max = 5.0;
   rp.request.y_min = -5.0;

   while(ros::ok()){
   	ros::spinOnce();
   	if (start){
   		client_rp.call(rp);
        
        goal.x=rp.response.x; 
        goal.y=rp.response.y;  
        goal.theta=rp.response.theta;

        std::cout << "\nGoal: x-coordinate= " << goal.x << "\nGoal: y-coordinate= " <<goal.y << " \nGoal: theta= " <<goal.theta << std::endl;
        ac.sendGoal(goal);
        
        while (true)
        {
           ros::spinOnce();
           if(start==false)
           {    //Cancel the goal
                ac.cancelGoal();
                    std::cout << "\n goal is interrupted and cancelled" << std::endl;
                    break;
                }
                else
                {
                    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
                    {
                        std::cout << "\nGoal Reached!" << std::endl;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
