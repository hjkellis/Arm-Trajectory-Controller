#include "arm_interface/se3_interface.hpp"

int main (int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SE3Interface>());
  rclcpp::shutdown();

  return 0;
}
