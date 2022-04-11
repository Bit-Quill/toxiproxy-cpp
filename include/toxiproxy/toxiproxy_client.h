#ifndef __TOXIPROXY_CLIENT_H__
#define __TOXIPROXY_CLIENT_H__

#include "proxy.h"
#include "toxiproxy_http_client.h"

/*
    Create a PROXY object or retrieves existing proxies.
*/

namespace TOXIPROXY {
class TOXIPROXY_CLIENT {
 public:
  TOXIPROXY_CLIENT();
  TOXIPROXY_CLIENT(std::string host);
  TOXIPROXY_CLIENT(std::string host, int port);
  TOXIPROXY_CLIENT(std::string protocol, std::string host, int port);
  ~TOXIPROXY_CLIENT() = default;

  std::vector<PROXY*> get_proxies() const;
  PROXY* create_proxy(std::string name, std::string listen, std::string upstream);
  PROXY* get_proxy(const std::string &name);
  void reset() const;

 private:
  PROXY* new_proxy_instance(const std::string &name, nlohmann::json json_object);
  TOXIPROXY_HTTP_CLIENT* client;
  const std::string PROXIES_API = "/proxies/";
  const std::string RESET_API = "/reset";

  std::set<PROXY*> proxies;
};
}

#endif
