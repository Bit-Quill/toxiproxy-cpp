#include <toxiproxy/toxiproxy_http_client.h>

#include <utility>

namespace TOXIPROXY {
std::map<std::string, TOXIC_DIRECTION>TOXIPROXY_HTTP_CLIENT::str_to_toxic_direction_map =
    {{"UPSTREAM", TOXIC_DIRECTION::UPSTREAM}, {"DOWNSTREAM", TOXIC_DIRECTION::DOWNSTREAM}};
std::map<TOXIC_DIRECTION, std::string>TOXIPROXY_HTTP_CLIENT::toxic_direction_to_str_map =
    {{TOXIC_DIRECTION::UPSTREAM, "upstream"}, {TOXIC_DIRECTION::DOWNSTREAM, "downstream"}};

TOXIPROXY_HTTP_CLIENT::TOXIPROXY_HTTP_CLIENT(std::string protocol, std::string host, int port)
    : protocol{protocol}, host({host}), port{port} {
  // TODO: handle https protocol
}

nlohmann::json TOXIPROXY_HTTP_CLIENT::post(const std::string &path, std::string name, bool value) const {
  std::string str_value = value ? "true" : "false";
  const nlohmann::json param = {
      {name, str_value}
  };
  return post(path, param);
}

nlohmann::json TOXIPROXY_HTTP_CLIENT::post(const std::string &path, std::string name, std::string value) const {
  const nlohmann::json param = {
      {name, value}
  };
  return post(path, param);
}

nlohmann::json TOXIPROXY_HTTP_CLIENT::post(const std::string &path, std::string name, double value) const {
  const nlohmann::json param = {
      {name, value}
  };
  return post(path, param);
}

nlohmann::json TOXIPROXY_HTTP_CLIENT::post(const std::string &path, nlohmann::json value) const {
  if (auto res = httplib::Client(host, port).Post(path.c_str(), value.dump(), "application/json")) {
    nlohmann::json json_object = nlohmann::json::parse(res->body);
    return json_object;
  }

  return "";
}

nlohmann::json TOXIPROXY_HTTP_CLIENT::post(const std::string &path) const {
  if (path.empty()) {
    return -1;
  }

  if (auto res = httplib::Client(host, port).Post(path.c_str())) {
    nlohmann::json json_object = nlohmann::json::parse(res->body);
    return json_object;
  }

  return "";
}

nlohmann::json TOXIPROXY_HTTP_CLIENT::get(const std::string &path) const {
  if (path.empty()) {
    return -1;
  }

  if (auto res = httplib::Client(host, port).Get(path.c_str())) {
    return nlohmann::json::parse(res->body);
  }

  return "";
}

int TOXIPROXY_HTTP_CLIENT::delete_path(const std::string &path) const {
  if (path.empty()) {
    return -1;
  }

  if (auto res = httplib::Client(host, port).Delete(path.c_str())) {
    return res->status;
  }

  return -1;
}
}
