#pragma once

#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "serial_port.hpp"

class JointInterface : public rclcpp::Node {
  public:
    JointInterface();

  protected:
    std::unique_ptr<SerialPort> serial_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr serial_publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr serial_subscriber_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;

    std_msgs::msg::String serial_format(sensor_msgs::msg::JointState msg) const;

  private:
    void serial_rx();
};
