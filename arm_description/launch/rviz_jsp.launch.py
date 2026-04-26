"""
RViz with Joint State Publisher GUI Launch File

This launch file launches the JSP GUI to control RViz.

Author: Hunter Ellis
Date: 3-29-25
"""

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():

    desc_pkg_path = get_package_share_directory('arm_description')

    rviz_arg = DeclareLaunchArgument(
        'rviz',
        default_value='true',
        description='Enable rviz visualization'
    )

    jsp = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(desc_pkg_path,
                         'launch',
                         'jsp.launch.py'
                         )
        ),
        launch_arguments={'jsp_gui': 'true'}.items()
    )

    state_publisher = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(desc_pkg_path,
                         'launch',
                         'arm.launch.py'
                         )
        ),
        launch_arguments={'spawn': 'false'}.items()
    )

    rviz = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(desc_pkg_path,
                         'launch',
                         'rviz.launch.py'
                         )
        ),
        condition=IfCondition(LaunchConfiguration('rviz', default='true'))
    )

    return LaunchDescription([
        rviz_arg,
        jsp,
        state_publisher,
        rviz
    ])
