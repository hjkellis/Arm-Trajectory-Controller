cmake_minimum_required(VERSION 3.8)
project(arm_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(robot_state_publisher REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)

find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

include_directories(
  include
  src
)

# Serial Library
add_library(serial_port
  src/serial_port.cpp
)
ament_target_dependencies(serial_port
  rclcpp
)
target_include_directories(serial_port
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Interface Library
add_library(arm_interface_lib
  src/joint_interface.cpp
  src/se3_interface.cpp
)
ament_target_dependencies(arm_interface_lib
  rclcpp
  sensor_msgs
  geometry_msgs
)
target_include_directories(arm_interface_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(arm_interface_lib serial_port)

# Serial Port Node
add_executable(SerialNode
  src/serial_node.cpp
)

ament_target_dependencies(SerialNode
  rclcpp
  sensor_msgs
)
target_link_libraries(SerialNode serial_port)

# interface
add_executable(JointInterface
  src/joint_interface_node.cpp
)
ament_target_dependencies(JointInterface
  rclcpp
  sensor_msgs
)
target_link_libraries(JointInterface arm_interface_lib)

# SE3 interface
add_executable(SE3Interface
  src/se3_interface_node.cpp
)
ament_target_dependencies(SE3Interface
  rclcpp
  sensor_msgs
  geometry_msgs
)
target_link_libraries(SE3Interface arm_interface_lib)


# Install
install(
  TARGETS
    serial_port
    arm_interface_lib
    SerialNode
    JointInterface
    SE3Interface
  EXPORT export_${PROJECT_NAME}
  RUNTIME DESTINATION lib/${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(
  DIRECTORY
  launch
  DESTINATION
  share/${PROJECT_NAME}/launch
)

# Export and package
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  rclcpp
  sensor_msgs
  geometry_msgs
)

ament_package()
