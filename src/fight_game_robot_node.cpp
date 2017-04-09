#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <ros_arduino_msgs/ServoWrite.h>

#include <skeleton_markers/Skeleton.h>
#include <stdio.h>

//void skeletonCallBack (const skeleton_markers::Skeleton::ConstPtr& skeleton_msg)
//{
//  ROS_INFO("skeleton msgs recevied");

//  //getting servo angles
//  //TODO: make lowest angle 0 and max 80
//  //right servo
//    ros_arduino_msgs::ServoWrite right_servo_srv;
//    right_servo_srv.request.id = 0;
//    right_servo_srv.request.value = 0.5;
//  //left servo
//    ros_arduino_msgs::ServoWrite left_servo_srv;
//    left_servo_srv.request.id = 1;
//    left_servo_srv.request.value = 0.5;

//  //calling servo angle service
//    int dummy;
//    ros::service::call("arduino/servo_write", left_servo_srv);
//    ros::service::call("arduino/servo_write", right_servo_srv);
//}

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "arms_controller");
  ros::NodeHandle node;

  //TODO: where is loop rate ?????????

  //NOTE: kinect read depth as the z axis not x
  tf::TransformListener tf_listener;
  tf::StampedTransform right_hand_transform;
  tf::StampedTransform left_hand_transform;
  while (node.ok()){

    try{

      tf_listener.lookupTransform("/torso", "/right_shoulder", ros::Time(0), right_hand_transform);
      //tf::Quaternion rotation_quat;
      double right_yaw, right_pitch, right_roll;
      right_hand_transform.getBasis().getRPY(right_roll,right_pitch,right_yaw);
      //TODO: add 1.57 to all or WHAT
      double right_angle = - right_yaw + 1.57;
//      std::cout << "right angle: " << right_angle << std::endl;
      //ROS_INFO("%f", pitch); //error - doesnt displat right value

      tf_listener.lookupTransform("/torso", "/left_shoulder", ros::Time(0), left_hand_transform);
      //tf::Quaternion rotation_quat;
      double left_yaw, left_pitch, left_roll;
      left_hand_transform.getBasis().getRPY(left_roll,left_pitch,left_yaw);
      //TODO: add 1.57 to all or WHAT
      double left_angle = - left_yaw + 1.57;
      std::cout << "left angle: " << left_angle << std::endl;
      //ROS_INFO("%f", pitch); //error - doesnt displat right value

        //commanding arm - servo angles
        //TODO: make lowest angle 0 and max 80
        //right servo
          ros_arduino_msgs::ServoWrite right_servo_srv;
          right_servo_srv.request.id = 1;
          right_servo_srv.request.value = right_angle; //testing it with 45 deg
        //left servo
          ros_arduino_msgs::ServoWrite left_servo_srv;
          left_servo_srv.request.id = 0;
          left_servo_srv.request.value = left_angle; //testing it with 45 deg

        //calling servo angle service
          ros::service::call("base_arm_controller/servo_write", left_servo_srv);
          ros::service::call("base_arm_controller/servo_write", right_servo_srv);

    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
  }

ros::spin();

  return 0;
}
