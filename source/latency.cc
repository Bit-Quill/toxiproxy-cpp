#include <toxiproxy/latency.h>

namespace TOXIPROXY {
void LATENCY::set_attributes(nlohmann::json attributes) {
  this->latency = attributes["latency"].get<long>();
  this->jitter = attributes["jitter"].get<long>();
}

nlohmann::json LATENCY::get_attributes() {
  nlohmann::json attribute = {
      {"latency", latency},
      {"jitter", jitter}};
  return attribute;
}

TOXIC_TYPES LATENCY::get_type() {
  return TOXIC_TYPES::LATENCY;
}

long LATENCY::get_latency() const {
  return latency;
}

long LATENCY::get_jitter() const {
  return jitter;
}

LATENCY* LATENCY::set_latency(const long new_latency) {
  post_attribute("latency", new_latency);
  return this;
}

LATENCY* LATENCY::set_jitter(const long new_jitter) {
  post_attribute("jitter", new_jitter);
  return this;
}
}
