#include <toxiproxy/limit_data.h>

namespace TOXIPROXY {
void LIMIT_DATA::set_attributes(nlohmann::json attributes) {
  this->bytes = attributes["bytes"].get<long>();
}

nlohmann::json LIMIT_DATA::get_attributes() {
  nlohmann::json attribute = {{"bytes", bytes}};
  return attribute;
}

TOXIC_TYPES LIMIT_DATA::get_type() {
  return TOXIC_TYPES::LIMIT_DATA;
}

long LIMIT_DATA::get_bytes() const {
  return bytes;
}

LIMIT_DATA* LIMIT_DATA::set_bytes(const long new_bytes) {
  post_attribute("bytes", new_bytes);
  return this;
}
}
