#include <toxiproxy/toxic_type.h>
#include <toxiproxy/toxic_list.h>

#include <utility>

namespace TOXIPROXY {
TOXIC* TOXIC_LIST::get(const std::string &name) {
  const std::string toxic_path = get_toxic_path(std::move(name));
  const nlohmann::json json_object = client->get(toxic_path);

  if (json_object.contains("error")) {
    return nullptr;
  }

  return TOXIC_TYPE::create_toxic(client, toxic_path, json_object);
}

template<typename T, typename std::enable_if<std::is_base_of<TOXIC, T>::value>::type*>
std::vector<T> TOXIC_LIST::get_all() {
  std::vector < TOXIC * > toxics;

  for (auto json_object: client->get(path)) {
    auto toxic_name = json_object["name"].get<std::string>();
    TOXIC* toxic = TOXIC_TYPE::create_toxic(client, get_toxic_path(toxic_name), json_object);
    toxics.push_back(toxic);
  }

  return toxics;
}

template<typename T, typename std::enable_if<std::is_base_of<TOXIC, T>::value>::type*>
T TOXIC_LIST::get(std::string name, T type) {
  TOXIC* toxic = get(name);
  return static_cast<T>(toxic);
}

BANDWIDTH* TOXIC_LIST::bandwidth(const std::string &name, TOXIC_DIRECTION direction, long rate) const {
  return new BANDWIDTH(client, path, name, direction, rate);
}

LATENCY* TOXIC_LIST::latency(const std::string &name, TOXIC_DIRECTION direction, long latency) const {
  return new LATENCY(client, path, name, direction, latency);
}

SLICER* TOXIC_LIST::slicer(const std::string &name, TOXIC_DIRECTION direction, long average_size, long delay) const {
  return new SLICER(client, path, name, direction, delay);
}

SLOW_CLOSE* TOXIC_LIST::slow_close(const std::string &name, TOXIC_DIRECTION direction, long delay) const {
  return new SLOW_CLOSE(client, path, name, direction, delay);
}

TIMEOUT* TOXIC_LIST::timeout(const std::string &name, TOXIC_DIRECTION direction, long timeout) const {
  return new TIMEOUT(client, path, name, direction, timeout);
}

LIMIT_DATA* TOXIC_LIST::limit_data(const std::string &name, TOXIC_DIRECTION direction, long bytes) const {
  return new LIMIT_DATA(client, path, name, direction, bytes);
}

RESET_PEER* TOXIC_LIST::reset_peer(const std::string &name, TOXIC_DIRECTION direction, long timeout) const {
  return new RESET_PEER(client, path, name, direction, timeout);
}

std::string TOXIC_LIST::get_toxic_path(const std::string &name) const {
  return path + "/" + name;
}
}
