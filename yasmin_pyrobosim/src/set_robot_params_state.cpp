#include <memory>
#include <string>

#include "yasmin/blackboard.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/basic_outcomes.hpp"

class SetRobotParamsState : public yasmin::State {

public:
  SetRobotParamsState() : yasmin::State({"succeeded"}) {
    this->set_description(
        "Set robot params as blackboard output keys from declared parameters.");
    this->declare_parameter("robot_name", "Name of the robot to navigate",
                            std::string("robot"));
    this->declare_parameter("dumpster_location",
                            "Name of the dumpster location",
                            std::string("dumpster"));
    this->declare_parameter("target_object",
                            "Name of the target object to pick",
                            std::string("waste"));
  };

  std::string execute(yasmin::Blackboard::SharedPtr blackboard) override {

    blackboard->set<std::string>(
        "robot_name", this->get_parameter<std::string>("robot_name"));
    blackboard->set<std::string>(
        "dumpster_location",
        this->get_parameter<std::string>("dumpster_location"));
    blackboard->set<std::string>(
        "target_object", this->get_parameter<std::string>("target_object"));

    return yasmin_ros::basic_outcomes::SUCCEED;
  }
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(SetRobotParamsState, yasmin::State)
