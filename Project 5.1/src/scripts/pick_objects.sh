xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
xterm -e "  roslaunch my_robot world.launch world_file:=/home/workspace/catkin_ws/src/map/world.world" &
sleep 5
xterm -e " roslaunch my_robot amcl.launch map_file:=/home/workspace/catkin_ws/src/map/map.yaml" &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5
xterm -e " roslaunch pick_objects pick_objects2.launch "
