
#include <memory>
#include <string>

#include "pyrobosim_msgs/action/execute_task_action.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/action_state.hpp"

#include <pluginlib/class_list_macros.hpp>

using ExecuteTaskAction = pyrobosim_msgs::action::ExecuteTaskAction;
using namespace std::placeholders;

class NavigateState : public yasmin_ros::ActionState<ExecuteTaskAction> {

public:
  NavigateState()
      : yasmin_ros::ActionState<ExecuteTaskAction>(
            "/execute_action",
            std::bind(&NavigateState::create_goal_handler, this, _1)){};

  ExecuteTaskAction::Goal create_goal_handler(
      std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) {

    auto goal = ExecuteTaskAction::Goal();
    goal.action.type = "navigate";
    goal.action.robot = blackboard->get<std::string>("robot_name");
    goal.action.target_location =
        blackboard->get<std::string>("target_location");
    return goal;
  };
};

PLUGINLIB_EXPORT_CLASS(NavigateState, yasmin::State)