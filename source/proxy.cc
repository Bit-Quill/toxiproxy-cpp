#include <toxiproxy/proxy.h>

#include <iostream>
#include <utility>

namespace TOXIPROXY {
PROXY::PROXY(TOXIPROXY_HTTP_CLIENT* client, const std::string &path, nlohmann::json json_object)
    : client{client}, path{path} {
  set_from_json(std::move(json_object));
}

std::string PROXY::get_name() {
  return name;
}

std::string PROXY::get_listen() {
  return listen;
}

std::string PROXY::get_upstream() {
  return upstream;
}

bool PROXY::is_enabled() const {
  return enabled;
}

TOXIC_LIST* PROXY::get_toxics() const {
  return toxic_list;
}

void PROXY::set_listen(std::string new_listen) {
  set_from_json(client->post(path, "listen", std::move(new_listen)));
}

void PROXY::set_upstream(std::string new_upstream) {
  set_from_json(client->post(path, "upstream", std::move(new_upstream)));
}

void PROXY::enable() {
  set_from_json(client->post(path, "enabled", true));
}

void PROXY::disable() {
  set_from_json(client->post(path, "enabled", false));
}

void PROXY::delete_path() const {
  client->delete_path(path);
}

void PROXY::reset() {
  set_from_json(client->get(path));
}

void PROXY::set_from_json(nlohmann::json json_object) {
  name = json_object["name"].get<std::string>();
  listen = json_object["listen"].get<std::string>();
  upstream = json_object["upstream"].get<std::string>();
  enabled = json_object["enabled"].get<bool>();

  toxic_list = new TOXIC_LIST(client, path + "/toxics");
}
}
