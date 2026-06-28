#include <memory>
#include <string>
#include <vector>

#include "pyrobosim_msgs/msg/object_state.hpp"

#include "yasmin/state.hpp"
#include "yasmin_ros/basic_outcomes.hpp"

class AccumulateObjectsState : public yasmin::State {

public:
  AccumulateObjectsState() : yasmin::State({"succeeded"}) {
    this->set_description(
        "Accumulate detected objects into an accumulated list on the "
        "blackboard.");
    this->add_input_key("detected_objects",
                        "List of newly detected objects to accumulate");
    this->add_output_key("accumulated_objects",
                         "Accumulated list of all detected objects");
  };

  std::string execute(yasmin::Blackboard::SharedPtr blackboard) override {
    auto detected =
        blackboard->get<std::vector<pyrobosim_msgs::msg::ObjectState>>(
            "detected_objects");

    std::vector<pyrobosim_msgs::msg::ObjectState> accumulated;
    if (blackboard->contains("accumulated_objects")) {
      accumulated =
          blackboard->get<std::vector<pyrobosim_msgs::msg::ObjectState>>(
              "accumulated_objects");
    }

    accumulated.insert(accumulated.end(), detected.begin(), detected.end());

    blackboard->set<std::vector<pyrobosim_msgs::msg::ObjectState>>(
        "accumulated_objects", accumulated);

    return yasmin_ros::basic_outcomes::SUCCEED;
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(AccumulateObjectsState, yasmin::State)
