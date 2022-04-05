#include <toxiproxy/bandwidth.h>

namespace TOXIPROXY {
void BANDWIDTH::set_attributes(nlohmann::json attributes) {
  rate = attributes["rate"].get<long>();
}

nlohmann::json BANDWIDTH::get_attributes() {
  nlohmann::json attribute = {{"rate", rate}};
  return attribute;
}

TOXIC_TYPES BANDWIDTH::get_type() {
  return TOXIC_TYPES::BANDWIDTH;
}

long BANDWIDTH::get_rate() const {
  return rate;
}

BANDWIDTH* BANDWIDTH::set_rate(const long new_rate) {
  post_attribute("rate", new_rate);
  return this;
}
}
