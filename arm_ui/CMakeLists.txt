cmake_minimum_required(VERSION 3.8)
project(arm_ui)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncurses)

find_package(moveit_ros_planning_interface QUIET)

add_executable(control_manager src/control_manager.cpp)
ament_target_dependencies(control_manager
  rclcpp
  sensor_msgs
  geometry_msgs
  std_msgs
  trajectory_msgs
)

if(moveit_ros_planning_interface_FOUND)
  ament_target_dependencies(control_manager moveit_ros_planning_interface)
  target_compile_definitions(control_manager PRIVATE HAS_MOVEIT=1)
  message(STATUS "MoveIt2 found — motion planning enabled")
else()
  message(STATUS "MoveIt2 not found — motion planning disabled")
endif()

target_include_directories(control_manager PRIVATE ${NCURSES_INCLUDE_DIRS})
target_link_libraries(control_manager ${NCURSES_LIBRARIES})

target_include_directories(control_manager PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(control_manager PUBLIC c_std_99 cxx_std_17)

install(
  TARGETS
    control_manager
  DESTINATION
    lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
