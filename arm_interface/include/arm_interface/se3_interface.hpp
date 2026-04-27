#pragma once

#include "joint_interface.hpp"
#include "geometry_msgs/msg/pose.hpp"

class SE3Interface : public JointInterface {
  public:
    SE3Interface();

  private:
    rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr se3_subscriber_;
};
