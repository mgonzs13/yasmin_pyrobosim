# yasmin_pyrobosim

# Installation

```shell
cd ~/ros2_ws/src
git clone https://github.com/mgonzs13/yasmin_pyrobosim.git
cd ~/ros2_ws
pip3 install -r src/yasmin_pyrobosim/requirements.txt
rosdep install --from-paths src --ignore-src -r -y
colcon build
```

## Usage

First of all, launch the pyrobosim world to use all the demos:

```shell
ros2 launch yasmin_pyrobosim_bringup pyrobosim.launch.py
```

Then, you can run any YASMIN demo:

```shell
ros2 launch yasmin_pyrobosim_bringup run_demo.launch.py state_machine_file:="navigate_random.xml"
```

You can run the YASMIN viewer to visualize the state machines while running by entering in http://localhost:5000:

```shell
ros2 run yasmin_viewer yasmin_viewer_node
```
