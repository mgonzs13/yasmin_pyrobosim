
#include <memory>
#include <string>

#include "pyrobosim_msgs/action/detect_objects.hpp"
#include "pyrobosim_msgs/msg/object_state.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/action_state.hpp"
#include "yasmin_ros/basic_outcomes.hpp"

using DetectObjectsAction = pyrobosim_msgs::action::DetectObjects;
using namespace std::placeholders;

class DetectObjectsState : public yasmin_ros::ActionState<DetectObjectsAction> {

public:
  DetectObjectsState()
      : yasmin_ros::ActionState<DetectObjectsAction>(
            "detect_objects",
            std::bind(&DetectObjectsState::create_goal_handler, this, _1),
            std::bind(&DetectObjectsState::on_result, this, _1, _2)) {};

  DetectObjectsAction::Goal create_goal_handler(
      std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) {

    auto goal = DetectObjectsAction::Goal();

    if (blackboard->contains("target_object")) {
      goal.target_object = blackboard->get<std::string>("target_object");
    }

    return goal;
  };

  std::string
  on_result(std::shared_ptr<yasmin::blackboard::Blackboard> blackboard,
            const DetectObjectsAction::Result::SharedPtr result) {

    blackboard->set<std::vector<pyrobosim_msgs::msg::ObjectState>>(
        "detected_objects", result->detected_objects);

    return yasmin_ros::basic_outcomes::SUCCEED;
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(DetectObjectsState, yasmin::State)