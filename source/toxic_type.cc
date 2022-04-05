#include <toxiproxy/toxic_type.h>

namespace TOXIPROXY {
std::map<std::string, TOXIC_TYPES> TOXIC_TYPE::str_to_toxic_types_map = {
    {"BANDWIDTH", TOXIC_TYPES::BANDWIDTH},
    {"LIMIT_DATA", TOXIC_TYPES::LIMIT_DATA},
    {"LATENCY", TOXIC_TYPES::LATENCY},
    {"SLICER", TOXIC_TYPES::SLICER},
    {"SLOW_CLOSE", TOXIC_TYPES::SLOW_CLOSE},
    {"RESET_PEER", TOXIC_TYPES::RESET_PEER},
    {"TIMEOUT", TOXIC_TYPES::TIMEOUT}};

std::map<TOXIC_TYPES, std::string> TOXIC_TYPE::toxic_types_to_str_map = {
    {TOXIC_TYPES::BANDWIDTH, "bandwidth"},
    {TOXIC_TYPES::LATENCY, "latency"},
    {TOXIC_TYPES::SLICER, "slicer"},
    {TOXIC_TYPES::TIMEOUT, "timeout"},
    {TOXIC_TYPES::SLOW_CLOSE, "slow_close"},
    {TOXIC_TYPES::RESET_PEER, "reset_peer"},
    {TOXIC_TYPES::LIMIT_DATA, "limit_data"},
};

TOXIC* TOXIC_TYPE::create_toxic(TOXIPROXY_HTTP_CLIENT* client, const std::string &path, nlohmann::json json_object) {
  const std::string type = json_object["type"].get<std::string>();

  const TOXIC_TYPES toxic_type = get_toxic_type(type);

  switch (toxic_type) {
    case TOXIC_TYPES::BANDWIDTH: return new BANDWIDTH(client, path, json_object);
    case TOXIC_TYPES::LIMIT_DATA: return new LIMIT_DATA(client, path, json_object);
    case TOXIC_TYPES::LATENCY: return new LATENCY(client, path, json_object);
    case TOXIC_TYPES::SLICER: return new SLICER(client, path, json_object);
    case TOXIC_TYPES::SLOW_CLOSE: return new SLOW_CLOSE(client, path, json_object);
    case TOXIC_TYPES::RESET_PEER: return new RESET_PEER(client, path, json_object);
    case TOXIC_TYPES::TIMEOUT: return new TIMEOUT(client, path, json_object);
    default: return nullptr;
  }
}

TOXIC_TYPES TOXIC_TYPE::get_toxic_type(std::string type) {
  for (auto &c: type)
    c = toupper(c);

  const auto it = str_to_toxic_types_map.find(type);
  if (it != str_to_toxic_types_map.end()) {
    return it->second;
  }

  return TOXIC_TYPES::INVALID;
}
}
