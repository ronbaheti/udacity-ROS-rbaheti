#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "add_markers/add_markers_srv.h"
#include <string>



class add_markers_sp
{
private:

  ros::NodeHandle n;
  ros::Publisher marker_pub ;
  ros::ServiceServer marker_ser;

  bool callbackFunc(add_markers::add_markers_srv::Request& req, add_markers::add_markers_srv::Response& res)
  {
    
     visualization_msgs::Marker marker;
     // Set the frame ID and timestamp.  See the TF tutorials for information on these.
     marker.header.frame_id = "map";
     marker.header.stamp = ros::Time::now();
     // Set the namespace and id for this marker.  This serves to create a unique ID
     // Any marker sent with the same namespace and id will overwrite the old one
     marker.ns = "add_markers";
     marker.id = 0;
     // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
     uint32_t shape = visualization_msgs::Marker::CUBE;
     marker.type = shape;
     // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
     marker.action = req.display? visualization_msgs::Marker::ADD : visualization_msgs::Marker::DELETE;
     // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified n the header
     marker.pose.position.x = req.x;
     marker.pose.position.y = req.y;
     marker.pose.position.z = 0;
     marker.pose.orientation.x = 0.0;
     marker.pose.orientation.y = 0.0;
     marker.pose.orientation.z = 0.0;
     marker.pose.orientation.w = 1.0;
     // Set the scale of the marker -- 1x1x1 here means 1m on a side
     marker.scale.x = 0.5;
     marker.scale.y = 0.5;
     marker.scale.z = 0.5;
     // Set the color -- be sure to set alpha to something non-zero!
     marker.color.r = 0.0f;
     marker.color.g = 1.0f;
     marker.color.b = 0.0f;
     marker.color.a = 1.0;
     marker.lifetime = ros::Duration();
     // Publish the marker

     marker_pub.publish(marker);

     return true;
  }

public:
  add_markers_sp()
  {

     marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
     marker_ser = n.advertiseService("/add_markers/add_markers", &add_markers_sp::callbackFunc, this);
  }
};

int main( int argc, char** argv )
{

  ros::init(argc, argv, "add_markers");
  // ros::Subscriber odom_sub = n.subscribe("/odom",10, callbackfunc);
  add_markers_sp add_markers;
  ros::spin();


  return 0;
}

