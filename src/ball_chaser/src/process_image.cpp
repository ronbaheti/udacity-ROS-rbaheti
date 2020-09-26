#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "sensor_msgs/JointState.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot

    ROS_INFO_STREAM("Following the ball");

    // Request velocities
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the safe_move service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");


}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    float linearx = 0;
    float angularz=0;
    int i = 0, j=0;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    bool white_ball = false;

    for (j=0; j<img.height; i++) {  
	for (i=0; i<img.step; i++) { 
	    if (img.data[i*j] == white_pixel) {
	        white_ball = true;
	        break; 
	    }
	} 
    }
    
    // Finding position in image

    i = 3*i/img.step;
    
    // Providing velocities

    if (white_ball==true && i<=1) {
	linearx = 0;
	angularz = -5;
    }
    else if (white_ball==true && i>1 && i<2) {
	linearx = 5;
	angularz = 0;
    }
    else if (white_ball==true && i<=3 && i>=2) {
	linearx = 0;
	angularz = 5;
    }
    else if (white_ball==false){
	linearx=0;
	angularz=0;
    }

    drive_robot(linearx, angularz);    

}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
