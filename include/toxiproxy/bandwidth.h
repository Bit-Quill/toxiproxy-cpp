#ifndef __BANDWIDTH_H__
#define __BANDWIDTH_H__

#include <utility>

#include "toxic.h"

/**
   A type of Toxic that limits a proxy connection to a maximum number of kilobytes per second.
*/

namespace TOXIPROXY {
class BANDWIDTH : public TOXIC {
 public:
  BANDWIDTH(TOXIPROXY_HTTP_CLIENT* client,
            const std::string &toxic_list_path,
            const std::string &name,
            TOXIC_DIRECTION stream,
            long rate)
      : TOXIC{client, toxic_list_path, name, stream}, rate{rate} {
    create_toxic(toxic_list_path);
  }

  BANDWIDTH(TOXIPROXY_HTTP_CLIENT* client, std::string path, nlohmann::json json_object)
      : TOXIC{client, path, json_object} {
    set_from_json(json_object);
  }

  void set_attributes(nlohmann::json attributes) override;
  nlohmann::json get_attributes() override;
  TOXIC_TYPES get_type() override;
  long get_rate() const;
  BANDWIDTH* set_rate(long rate);

 private:
  long rate = 0;
};
}

#endif
