#include <toxiproxy/slicer.h>

namespace TOXIPROXY {
void SLICER::set_attributes(nlohmann::json attributes) {
  delay = attributes["delay"].get<long>();
}

nlohmann::json SLICER::get_attributes() {
  nlohmann::json attribute = {{"delay", delay}};
  return attribute;
}

TOXIC_TYPES SLICER::get_type() {
  return TOXIC_TYPES::SLICER;
}

long SLICER::get_delay() const {
  return delay;
}

SLICER* SLICER::set_delay(long delay) {
  post_attribute("delay", delay);
  return this;
}
}
