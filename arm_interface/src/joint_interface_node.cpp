#include "arm_interface/joint_interface.hpp"

int main (int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JointInterface>());
  rclcpp::shutdown();

  return 0;
}
