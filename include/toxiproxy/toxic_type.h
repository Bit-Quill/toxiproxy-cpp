#ifndef __TOXICTYPE_H__
#define __TOXICTYPE_H__

#include "toxic.h"
#include "bandwidth.h"
#include "latency.h"
#include "limit_data.h"
#include "reset_peer.h"
#include "slicer.h"
#include "timeout.h"
#include "slow_close.h"

/*
    Create Toxics based on the given type.
*/

namespace TOXIPROXY {
class TOXIC_TYPE {
 public:
  static std::map<std::string, TOXIC_TYPES> str_to_toxic_types_map;
  static std::map<TOXIC_TYPES, std::string> toxic_types_to_str_map;
  static TOXIC* create_toxic(TOXIPROXY_HTTP_CLIENT* client, const std::string &path, nlohmann::json json_object);
  static TOXIC_TYPES get_toxic_type(std::string type);

 private:
  template<typename T>
  static TOXIC* do_create_toxic(TOXIPROXY_HTTP_CLIENT* client, std::string path, nlohmann::json json_object);
};
}

#endif
