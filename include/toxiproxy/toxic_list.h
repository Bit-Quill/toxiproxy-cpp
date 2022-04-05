#ifndef __TOXICLIST_H__
#define __TOXICLIST_H__

#include <type_traits>
#include <utility>

#include "toxic_type.h"

namespace TOXIPROXY {
class TOXIC_LIST {
 public:
  TOXIC_LIST(TOXIPROXY_HTTP_CLIENT* client, std::string path) : client{client}, path(std::move(path)) {}
  TOXIC* get(const std::string &name);

  template<typename T, typename std::enable_if<std::is_base_of<TOXIC, T>::value>::type* = nullptr>
  std::vector<T> get_all();

  template<typename T, typename std::enable_if<std::is_base_of<TOXIC, T>::value>::type* = nullptr>
  T get(std::string name, T type);

  BANDWIDTH* bandwidth(const std::string &name, TOXIC_DIRECTION direction, long rate) const;
  LATENCY* latency(const std::string &name, TOXIC_DIRECTION direction, long latency) const;
  SLICER* slicer(const std::string &name, TOXIC_DIRECTION direction, long average_size, long delay) const;
  SLOW_CLOSE* slow_close(const std::string &name, TOXIC_DIRECTION direction, long delay) const;
  TIMEOUT* timeout(const std::string &name, TOXIC_DIRECTION direction, long timeout) const;
  LIMIT_DATA* limit_data(const std::string &name, TOXIC_DIRECTION direction, long bytes) const;
  RESET_PEER* reset_peer(const std::string &name, TOXIC_DIRECTION direction, long timeout) const;

 private:
  TOXIPROXY_HTTP_CLIENT* client;
  std::string path;
  std::string get_toxic_path(const std::string &name) const;
};
}

#endif
