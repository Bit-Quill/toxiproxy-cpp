#ifndef __TOXIPROXYHTTPCLIENT_H__
#define __TOXIPROXYHTTPCLIENT_H__

#include <nlohmann/json.hpp>
#include <httplib.h>

namespace TOXIPROXY {

/*
  Enums representing the stream direction.
  Upstream = client -> server.
  Downstream = server -> client.
*/

enum class TOXIC_DIRECTION {
  UPSTREAM = 0,
  DOWNSTREAM = 1
};

/*
    HTTP Client to communicate to the toxiproxy daemon.
*/

class TOXIPROXY_HTTP_CLIENT {
 public:
  static std::map<std::string, TOXIC_DIRECTION> str_to_toxic_direction_map;
  static std::map<TOXIC_DIRECTION, std::string> toxic_direction_to_str_map;

  TOXIPROXY_HTTP_CLIENT(std::string protocol, std::string host, int port);
  ~TOXIPROXY_HTTP_CLIENT() = default;

  nlohmann::json post(const std::string &path, std::string name, bool value) const;
  nlohmann::json post(const std::string &path, std::string name, std::string value) const;
  nlohmann::json post(const std::string &path, std::string name, double value) const;
  nlohmann::json post(const std::string &path, nlohmann::json value) const;
  nlohmann::json post(const std::string &path) const;
  nlohmann::json get(const std::string &path) const;
  int delete_path(const std::string &path) const;

 private:
  const std::string protocol;
  const std::string host;
  const int port;

  const std::string PROXIES_API = "/proxies/";
  const std::string RESET_API = "/reset";
};
}

#endif
