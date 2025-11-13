#!/usr/bin/env python3

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

import rclpy
import threading
from pyrobosim.core import World, WorldYamlLoader
from pyrobosim.gui import start_gui
from pyrobosim_ros.ros_interface import WorldROSWrapper


def create_world_from_yaml(world_file: str) -> World:
    return WorldYamlLoader().from_file(world_file)


def create_ros_node() -> WorldROSWrapper:
    """Initializes ROS node"""
    rclpy.init()
    node = WorldROSWrapper(state_pub_rate=0.1, dynamics_rate=0.01)
    node.declare_parameter("world_file", value="")

    # Set the world
    world_file = node.get_parameter("world_file").get_parameter_value().string_value
    node.get_logger().info(f"Using world file {world_file}.")
    world = create_world_from_yaml(world_file)
    node.set_world(world)
    return node


if __name__ == "__main__":
    node = create_ros_node()

    # Start ROS node in separate thread
    ros_thread = threading.Thread(target=lambda: node.start(wait_for_gui=True))
    ros_thread.start()

    # Start GUI in main thread
    start_gui(node.world)
