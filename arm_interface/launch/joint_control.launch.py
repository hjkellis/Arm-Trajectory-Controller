"""
RViz-JSP Hardware Interface Launch File

Combines RViz, Joint State Publisher, and the hardware interface.
This allows the user to move the indiviudal joints of the arm.

Author: Hunter Ellis
"""

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    desc_pkg_path = get_package_share_directory('arm_description')
    arm_interface = get_package_share_directory('arm_interface')

    arm_port_arg = DeclareLaunchArgument(
        'port',
        default_value='/dev/ttyACM0',
        description='Serial port for arm interface'
    )

    rviz_arg = DeclareLaunchArgument(
        'rviz',
        default_value='true',
        description='Enable rviz visualization'
    )

    jsp_rviz = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(desc_pkg_path,
                         'launch',
                         'rviz_jsp.launch.py'
                         )
        ),
        launch_arguments={'rviz': LaunchConfiguration('rviz')}.items()
    )

    hw_interface = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(arm_interface,
                         'launch'
                         'interface.launch.py'
                         )
        ),
        launch_arguments={'port': LaunchConfiguration('port')}.items()
    )

    return LaunchDescription([
        arm_port_arg,
        rviz_arg,
        jsp_rviz,
        hw_interface
    ])
