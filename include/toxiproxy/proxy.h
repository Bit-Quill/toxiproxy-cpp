#ifndef __PROXY_H__
#define __PROXY_H__

#include "toxic_list.h"

namespace TOXIPROXY {
class PROXY {

 public:
  PROXY(TOXIPROXY_HTTP_CLIENT* client, const std::string &path, nlohmann::json json_object);

  std::string get_name();
  std::string get_listen();
  std::string get_upstream();
  bool is_enabled() const;
  TOXIC_LIST* get_toxics() const;
  void set_listen(std::string listen);
  void set_upstream(std::string upstream);
  void enable();
  void disable();
  void delete_path() const;
  void reset();

 private:
  TOXIPROXY_HTTP_CLIENT* client;
  std::string path;
  std::string name;
  std::string listen;
  std::string upstream;
  bool enabled;
  TOXIC_LIST* toxic_list;

  void set_from_json(nlohmann::json json_object);
};
}

#endif
