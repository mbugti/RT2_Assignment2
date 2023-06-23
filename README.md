# RT2_Assignment2
## Jupyter notebook package:
This package has **Jupyter Notebooks** which helps to control the robot in the gazebo environment and serves as an user iterface node.In the action package,the user interface is simply a command line interface and through which user can 'start' or 'stop' the robot but this node will have Graphical interface with Jupyter notebook for starting and stopping the robot,contrlling the robot in required direction and also different plots can be analysed with the help of this node.
## Jupyter Notebook desription:
The Jupyter Notebook consists of number of plots,buttons for controlling the robot and display of different analysis data of the robot's state.the buttons and plots that can be provided by this node is mentioned below.
### Start,Stop,foreward,backward,left,right buttons:
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/154955314-6963db8c-23d2-49e4-811a-2452e962a76c.jpg" >
This button is used to manually start and stop the robot and also the robot can be controlled in a every direction using the foreward,backward,left,right buttons.these buttons acts as a client service sending request to state machine through /user_interface node.
### Robot's moving position in real time:
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/154955780-9474e2e9-7205-48a8-a9d6-31f4c7c4ab6a.jpg" >
It is a live plot that shows the real-time state of the robot and this plot is an x,y plot and used to visualize the position of robot and also the path through which the robot is moving in gazebo environment.A diamond shaped black line will show the movement of robot.
### Velocity visualization plot:
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/154956187-c5c24725-6045-499d-8544-8cb020882c2d.jpg" >
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/154957806-3044a32b-0ba2-490a-8863-b9f7fdbf1c4c.jpg" >
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/154956251-a9522580-93a5-4e4a-8cb1-444f4b790fdc.jpg" >
This plot helps to visualize the **cmd_vel** against the **odom(actual velocity)**.it shows for both in linear and angular poistions.
### Bar plot:
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/154956539-3706afeb-484f-4db5-8399-a2c252391a55.jpg" >
Bar plot is used for showing the number of target reached and the number of target that as cancelled by the user.


### Histogram plot:
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/154956810-0b0ae5db-65ec-4cbd-af07-1082146131b8.jpg" >
The histogram plot shows the time taken to reach the target by the robot wn it is reached the goal.
## Running the package:
- In the first tab:
run the command below to launch the simulation and all the required nodes.
```roslaunch rt2_assignment1 sim.launch```
- In the second tab:
run the command to open jupyter notebook.
```jupyter notebook --allow-root```
and open the notebook named as **jupyter_4904540.ipynb** .

## Simulation:
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/Screenshot_2023-06-22_18-02-40.png ">
<img src="https://github.com/mbugti/RT2_Assignment2/blob/main/imgs/Screenshot_2023-06-22_18-04-09.png ">
