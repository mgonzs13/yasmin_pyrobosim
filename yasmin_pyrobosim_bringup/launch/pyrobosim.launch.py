# Copyright (C) 2025 Miguel Ángel González Santamarta
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from ament_index_python import get_package_share_directory


def generate_launch_description():

    world_file_arg = DeclareLaunchArgument(
        "world_file",
        default_value="roscon_2024_world.yaml",
        description="World YAML file to load",
    )

    world_file = LaunchConfiguration("world_file")

    pyrobosim_cmd = Node(
        package="pyrobosim_ros",
        executable="demo.py",
        output="both",
        parameters=[
            {
                "world_file": PathJoinSubstitution(
                    [
                        get_package_share_directory("yasmin_pyrobosim_bringup"),
                        "worlds",
                        world_file,
                    ]
                )
            }
        ],
    )

    ld = LaunchDescription()
    ld.add_action(world_file_arg)
    ld.add_action(pyrobosim_cmd)
    return ld
