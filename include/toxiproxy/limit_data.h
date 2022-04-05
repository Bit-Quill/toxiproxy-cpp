#ifndef __LIMITDATA_H__
#define __LIMITDATA_H__

#include <utility>

#include "toxic.h"

/**
   A type of Toxic that closes the proxy connection when transmitted data exceeds a set limit.
*/

namespace TOXIPROXY {
class LIMIT_DATA : public TOXIC {
 public:
  LIMIT_DATA(TOXIPROXY_HTTP_CLIENT* client,
             const std::string &toxic_list_path,
             const std::string &name,
             TOXIC_DIRECTION stream,
             long bytes)
      : TOXIC{client, toxic_list_path, name, stream}, bytes(bytes) {
    create_toxic(toxic_list_path);
  }

  LIMIT_DATA(TOXIPROXY_HTTP_CLIENT* client, std::string path, nlohmann::json json_object)
      : TOXIC{client, path, json_object} {
    set_from_json(json_object);
  }

  void set_attributes(nlohmann::json attributes) override;
  nlohmann::json get_attributes() override;
  TOXIC_TYPES get_type() override;
  long get_bytes() const;
  LIMIT_DATA* set_bytes(long bytes);

 private:
  long bytes;
};

}

#endif
