"""
Arm Hardware Interface Launch File

This Launch file initializes the interface between the arm hardware and ROS2.

Author: Hunter Ellis
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    port_arg = DeclareLaunchArgument(
        'port',
        default_value='/dev/ttyACM0',
        description='Serial port for arm interface'
    )

    interface_node = Node(
        package="arm_interface",
        executable='SerialInterface',
        name='serial_interface',
        parameters=[{'port': LaunchConfiguration('port')}]
    )

    return LaunchDescription([
        port_arg,
        interface_node
    ])
