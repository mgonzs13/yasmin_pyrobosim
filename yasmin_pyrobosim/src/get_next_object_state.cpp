
#include <memory>
#include <string>

#include "pyrobosim_msgs/msg/object_state.hpp"
#include "yasmin/state.hpp"

#include <pluginlib/class_list_macros.hpp>

class GetNextObjectState : public yasmin::State {

public:
  GetNextObjectState() : yasmin::State({"next", "end"}){};

  std::string
  execute(std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) override {
    auto objects =
        blackboard->get<std::vector<pyrobosim_msgs::msg::ObjectState>>(
            "detected_objects");

    if (objects.empty()) {
      return "end";
    } else {
      blackboard->set<std::string>("next_object", objects[0].name);
      blackboard->set<std::string>("object_location", objects[0].parent);
      objects.erase(objects.begin());
      blackboard->set<std::vector<pyrobosim_msgs::msg::ObjectState>>(
          "detected_objects", objects);
      return "next";
    }
  };
};

PLUGINLIB_EXPORT_CLASS(GetNextObjectState, yasmin::State)