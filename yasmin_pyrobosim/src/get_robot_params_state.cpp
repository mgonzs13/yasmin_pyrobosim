#include <memory>
#include <string>

#include "pyrobosim_msgs/action/execute_task_action.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/get_parameters_state.hpp"

class GetRobotParamsState : public yasmin_ros::GetParametersState {

public:
  GetRobotParamsState()
      : yasmin_ros::GetParametersState(
            yasmin_ros::GetParametersState::Parameters{
                {"robot_name", std::string("robot")},
                {"dumpster_location", std::string("dumpster")},
                {"target_object", std::string("waste")},
            }) {
    this->set_description(
        "Get the robot parameters from the blackboard and set them as output "
        "keys.");
    this->add_input_key("robot_name", "Name of the robot to navigate", "robot");
    this->add_input_key("dumpster_location", "Name of the dumpster location",
                        "dumpster");
    this->add_input_key("target_object", "Name of the target object to pick",
                        "waste");
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(GetRobotParamsState, yasmin::State)