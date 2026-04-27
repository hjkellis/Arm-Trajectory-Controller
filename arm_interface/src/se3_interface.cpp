#include "arm_interface/se3_interface.hpp"

SE3Interface::SE3Interface() : JointInterface() {
  se3_subscriber_ = create_subscription<geometry_msgs::msg::Pose>(
      "se3_ee", 10,
      [this] (const geometry_msgs::msg::Pose::SharedPtr msg) {
        RCLCPP_INFO(get_logger(), "SE3 Pose: x=%.3f, y=%.3f, z=%.3f",
                    msg->position.x, msg->position.y, msg->position.z);
      }
  );
}
