
#include <memory>
#include <string>

#include "yasmin/state.hpp"

#include <pluginlib/class_list_macros.hpp>

class GetNextLocationState : public yasmin::State {

public:
  GetNextLocationState() : yasmin::State({"next", "end"}) {};

  std::string
  execute(std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) override {
    auto locations =
        blackboard->get<std::vector<std::string>>("ordered_locations");

    if (locations.empty()) {
      return "end";
    } else {
      blackboard->set<std::string>("next_location", locations[0]);
      locations.erase(locations.begin());
      blackboard->set<std::vector<std::string>>("ordered_locations", locations);
      return "next";
    }
  };
};

PLUGINLIB_EXPORT_CLASS(GetNextLocationState, yasmin::State)