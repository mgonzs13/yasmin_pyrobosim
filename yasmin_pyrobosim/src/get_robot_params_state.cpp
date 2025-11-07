
#include <memory>
#include <string>

#include "pyrobosim_msgs/action/execute_task_action.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/get_parameters_state.hpp"

#include <pluginlib/class_list_macros.hpp>

class GetRobotParamsState : public yasmin_ros::GetParametersState {

public:
  GetRobotParamsState()
      : yasmin_ros::GetParametersState(std::map<std::string, std::any>{
            {"robot_name", std::string("robot")},
        }){};
};

PLUGINLIB_EXPORT_CLASS(GetRobotParamsState, yasmin::State)