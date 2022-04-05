#ifndef __LATENCY_H__
#define __LATENCY_H__

#include <utility>

#include "toxic.h"

/**
   A type of Toxic that adds a delay to all data going through the proxy.
*/

namespace TOXIPROXY {
class LATENCY : public TOXIC {
 public:
  LATENCY(TOXIPROXY_HTTP_CLIENT* client,
          const std::string &toxic_list_path,
          const std::string &name,
          TOXIC_DIRECTION stream,
          long latency)
      : TOXIC{client, toxic_list_path, name, stream}, latency(latency) {
    create_toxic(toxic_list_path);
  }

  LATENCY(TOXIPROXY_HTTP_CLIENT* client, std::string path, nlohmann::json json_object)
      : TOXIC{client, path, json_object} {
    set_from_json(json_object);
  }

  void set_attributes(nlohmann::json attributes) override;
  nlohmann::json get_attributes() override;
  TOXIC_TYPES get_type() override;
  long get_latency() const;
  long get_jitter() const;
  LATENCY* set_latency(long latency);
  LATENCY* set_jitter(long jitter);

 private:
  long latency;
  long jitter;
};
}

#endif
