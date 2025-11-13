
#include <memory>
#include <string>

#include "pyrobosim_msgs/action/detect_objects.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/action_state.hpp"

#include <pluginlib/class_list_macros.hpp>

using DetectObjectsAction = pyrobosim_msgs::action::DetectObjects;
using namespace std::placeholders;

class DetectObjectsState : public yasmin_ros::ActionState<DetectObjectsAction> {

public:
  DetectObjectsState()
      : yasmin_ros::ActionState<DetectObjectsAction>(
            "detect_objects",
            std::bind(&DetectObjectsState::create_goal_handler, this, _1)){};

  DetectObjectsAction::Goal create_goal_handler(
      std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) {

    auto goal = DetectObjectsAction::Goal();

    if (blackboard->contains("target_object")) {
      goal.target_object = blackboard->get<std::string>("target_object");
    }

    return goal;
  };
};

PLUGINLIB_EXPORT_CLASS(DetectObjectsState, yasmin::State)