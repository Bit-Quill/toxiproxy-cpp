#include <toxiproxy/timeout.h>

namespace TOXIPROXY {
void TIMEOUT::set_attributes(nlohmann::json attributes) {
  timeout = attributes["timeout"].get<long>();
}

nlohmann::json TIMEOUT::get_attributes() {
  nlohmann::json attribute = {{"timeout", timeout}};
  return attribute;
}

TOXIC_TYPES TIMEOUT::get_type() {
  return TOXIC_TYPES::TIMEOUT;
}

long TIMEOUT::get_timeout() const {
  return timeout;
}

TIMEOUT* TIMEOUT::set_timeout(long timeout) {
  post_attribute("timeout", timeout);
  return this;
}
}
