
#include <memory>
#include <string>

#include "yasmin/state.hpp"

class GetNextLocationState : public yasmin::State {

public:
  GetNextLocationState() : yasmin::State({"next", "end"}) {
    this->set_description(
        "Get the next location to navigate to from the ordered locations and "
        "set "
        "it as an output key. If there are no more locations, return 'end'.");
    this->set_outcome_description(
        "next",
        "A next location to navigate to was found and set as an output key.");
    this->set_outcome_description(
        "end", "No more locations to navigate to were found.");
    this->add_input_key("locations",
                        "List of ordered location names to navigate to");
    this->add_output_key("next_location",
                         "Name of the next location to navigate to");
  };

  std::string execute(yasmin::Blackboard::SharedPtr blackboard) override {
    auto locations = blackboard->get<std::vector<std::string>>("locations");

    if (locations.empty()) {
      return "end";
    } else {
      blackboard->set<std::string>("next_location", locations[0]);
      locations.erase(locations.begin());
      blackboard->set<std::vector<std::string>>("locations", locations);
      return "next";
    }
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(GetNextLocationState, yasmin::State)