#include "arm_interface/joint_interface.hpp"

#include "arm_interface/serial_port.hpp"

JointInterface::JointInterface() : Node("arm_interface") {
  declare_parameter("port", "/dev/ttyACM0");
  declare_parameter("baudrate", 115200);

  std::string port = get_parameter("port").as_string();
  int baudrate = get_parameter("baudrate").as_int();

  serial_ = std::make_unique<SerialPort>(port, baudrate);

  serial_publisher_ = create_publisher<std_msgs::msg::String>("serial_tx", 10);

  serial_subscriber_ = create_subscription<std_msgs::msg::String>(
      "serial_rx", 10,
      [this] (const std_msgs::msg::String::SharedPtr msg) {
        serial_->write_data(msg->data);
      }
  );

  joint_state_subscriber_ = create_subscription<sensor_msgs::msg::JointState>(
      "joint_states", 10,
      [this] (const sensor_msgs::msg::JointState msg) {
        std_msgs::msg::String str = serial_format(msg);
        serial_publisher_->publish(str);
      }
  );
}

void JointInterface::serial_rx() {
  auto data = serial_->read_data();
  if (!data.empty()) {
    std_msgs::msg::String msg;
    msg.data = data;
    serial_publisher_->publish(msg);
  }
}

std_msgs::msg::String JointInterface::serial_format(sensor_msgs::msg::JointState msg) const {
  std_msgs::msg::String str_msg;
  return str_msg;
}
