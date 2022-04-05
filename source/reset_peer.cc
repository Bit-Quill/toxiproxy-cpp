#include <toxiproxy/reset_peer.h>

namespace TOXIPROXY {
void RESET_PEER::set_attributes(nlohmann::json attributes) {
  timeout = attributes["timeout"].get<long>();
}

nlohmann::json RESET_PEER::get_attributes() {
  nlohmann::json attribute = {{"timeout", timeout}};
  return attribute;
}

TOXIC_TYPES RESET_PEER::get_type() {
  return TOXIC_TYPES::RESET_PEER;
}

long RESET_PEER::get_timeout() const {
  return timeout;
}

RESET_PEER* RESET_PEER::set_timeout(const long new_timeout) {
  post_attribute("timeout", new_timeout);
  return this;
}
}
