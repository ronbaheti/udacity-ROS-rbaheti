#!/bin/sh
xterm -e " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
xterm -e " roslaunch my_robot world.launch world_file:=/home/workspace/catkin_ws/src/map/world.world" &
sleep 5
xterm -e " roslaunch my_robot mapping.launch " &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5
xterm -e " roslaunch my_robot teleop.launch " &
