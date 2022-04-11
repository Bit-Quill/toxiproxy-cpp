#include <toxiproxy/toxiproxy_client.h>

#include <utility>

namespace TOXIPROXY {
TOXIPROXY_CLIENT::TOXIPROXY_CLIENT() : TOXIPROXY_CLIENT{"localhost", 8474} {}

TOXIPROXY_CLIENT::TOXIPROXY_CLIENT(std::string host) : TOXIPROXY_CLIENT{host, 8474} {}

TOXIPROXY_CLIENT::TOXIPROXY_CLIENT(std::string host, int port) : TOXIPROXY_CLIENT{"http", std::move(host), port} {}

TOXIPROXY_CLIENT::TOXIPROXY_CLIENT(std::string protocol, std::string host, int port) {
  client = new TOXIPROXY_HTTP_CLIENT(std::move(protocol), std::move(host), port);
}

std::vector<PROXY*> TOXIPROXY_CLIENT::get_proxies() const {
  std::vector < PROXY * > proxies;
  nlohmann::json json_object = client->get(PROXIES_API);
  if (!json_object) {
    return proxies;
  }

  for (auto elem: json_object.items())
    proxies.push_back(new PROXY(client, PROXIES_API + elem.key(), elem.value()));

  return proxies;
}

PROXY* TOXIPROXY_CLIENT::create_proxy(std::string name, std::string listen, std::string upstream) {
  const nlohmann::json json_object = {
      {"name", name},
      {"listen", listen},
      {"upstream", upstream}
  };

  return new_proxy_instance(name, client->post(PROXIES_API, json_object));
}

PROXY* TOXIPROXY_CLIENT::get_proxy(const std::string &name) {
  return new_proxy_instance(name, client->get(PROXIES_API + name));
}

void TOXIPROXY_CLIENT::reset() const {
  client->post(RESET_API);
  for (const auto elem: proxies) {
    elem->reset();
  }
}

PROXY* TOXIPROXY_CLIENT::new_proxy_instance(const std::string &name, nlohmann::json json_object) {
  const auto proxy = new PROXY(client, PROXIES_API + name, std::move(json_object));
  proxies.insert(proxy);
  return proxy;
}
}
