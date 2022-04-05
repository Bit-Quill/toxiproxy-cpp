#include <toxiproxy/slow_close.h>

namespace TOXIPROXY {
void SLOW_CLOSE::set_attributes(nlohmann::json attributes) {
  this->delay = attributes["delay"].get<long>();
}

nlohmann::json SLOW_CLOSE::get_attributes() {
  nlohmann::json attribute = {{"delay", delay}};
  return attribute;
}

TOXIC_TYPES SLOW_CLOSE::get_type() {
  return TOXIC_TYPES::RESET_PEER;
}

long SLOW_CLOSE::get_delay() const {
  return delay;
}

SLOW_CLOSE* SLOW_CLOSE::set_delay(long delay) {
  post_attribute("delay", delay);
  return this;
}
}
