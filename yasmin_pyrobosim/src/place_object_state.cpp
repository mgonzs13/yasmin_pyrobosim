
#include <memory>
#include <string>

#include "pyrobosim_msgs/action/execute_task_action.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/action_state.hpp"

using ExecuteTaskAction = pyrobosim_msgs::action::ExecuteTaskAction;
using namespace std::placeholders;

class PlaceObjectState : public yasmin_ros::ActionState<ExecuteTaskAction> {

public:
  PlaceObjectState()
      : yasmin_ros::ActionState<ExecuteTaskAction>(
            "/execute_action",
            std::bind(&PlaceObjectState::create_goal_handler, this, _1)) {};

  ExecuteTaskAction::Goal create_goal_handler(
      std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) {

    auto goal = ExecuteTaskAction::Goal();
    goal.action.type = "place";
    goal.action.robot = blackboard->get<std::string>("robot_name");
    return goal;
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(PlaceObjectState, yasmin::State)