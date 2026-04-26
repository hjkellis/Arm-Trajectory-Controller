# ROS2 Planning and Control Packages
Trajectory planning and control packages for my modified version of the [tw2ka robotic arm](https://www.youtube.com/watch?v=wI4Jh-T0Tlo).

## Quickstart
Add the packages to your ROS2 workspace. Source and build the packages.
```bash
git clone https://github.com/hunterwellis/Arm-Trajectory-Controller.git /path/to/ws/src
source /opt/ros/jazzy/setup.bash
colcon build
source ./install/setup.bash
```

Determine the serial port the arm is conected to.

To control the individual joints use the joint state publisher launch file.
```bash
ros2 launch arm_interface joint_control.launch.py port:=${SERIAL_PORT} rviz:=true
```

Control the arm in SE(3) using the `se3_control.launch.py` launch file.
```bash
ros2 launch arm_interface se3_control.launch.py port:=${SERIAL_PORT}
```

## Instructions
To control the end effector directly launch `se3_control.launch.py` and use the `/se3_ee` message.
> `se3_ee` is a ROS2 `geometry_msgs/msg/Pose` message

## Requirements
- Ubuntu 24.04+
- ROS2 Jazzy
- Jazzy control packages
- MoveIt 2
