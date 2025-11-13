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

import os
from launch_ros.actions import Node
from launch import LaunchDescription
from ament_index_python import get_package_share_directory


def generate_launch_description():

    pyrobosim_cmd = Node(
        package="pyrobosim_ros",
        executable="demo.py",
        output="both",
        parameters=[
            {
                "world_file": os.path.join(
                    get_package_share_directory("yasmin_pyrobosim_bringup"),
                    "worlds",
                    "roscon_2024_workshop_world.yaml",
                )
            }
        ],
    )

    ld = LaunchDescription()
    ld.add_action(pyrobosim_cmd)
    return ld
