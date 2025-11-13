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
from launch.actions import OpaqueFunction, DeclareLaunchArgument
from launch import LaunchDescription, LaunchContext
from launch.substitutions import LaunchConfiguration
from ament_index_python import get_package_share_directory


def generate_launch_description():

    # Creata a run_yasmin opaque function
    def run_yasmin(context: LaunchContext, state_machine_file):
        state_machine_file = str(context.perform_substitution(state_machine_file))
        state_machine_file = os.path.join(
            get_package_share_directory("yasmin_pyrobosim"),
            "state_machines",
            state_machine_file,
        )

        return [
            Node(
                package="yasmin_factory",
                executable="yasmin_factory_node",
                namespace="robot",
                output="both",
                parameters=[{"state_machine_file": state_machine_file}],
            )
        ]

    state_machine_file = LaunchConfiguration("state_machine_file")
    state_machine_file_cmd = DeclareLaunchArgument(
        "state_machine_file",
        default_value="navigate_random.xml",
        description="State machine file to use",
    )

    ld = LaunchDescription()
    ld.add_action(state_machine_file_cmd)
    ld.add_action(
        OpaqueFunction(function=run_yasmin, args=[state_machine_file]),
    )
    return ld
