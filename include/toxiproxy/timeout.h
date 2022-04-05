#ifndef __TIMEOUT_H__
#define __TIMEOUT_H__

#include <utility>

#include "toxic.h"

/*
    A type of Toxics that stops all data transfers and closes the connection after the given timeout.
*/

namespace TOXIPROXY {
class TIMEOUT : public TOXIC {
 public:
  TIMEOUT(TOXIPROXY_HTTP_CLIENT* client,
          const std::string &toxic_list_path,
          const std::string &name,
          TOXIC_DIRECTION stream,
          long timeout)
      : TOXIC{client, toxic_list_path, name, stream}, timeout(timeout) {
    create_toxic(toxic_list_path);
  }

  TIMEOUT(TOXIPROXY_HTTP_CLIENT* client, std::string path, nlohmann::json json_object)
      : TOXIC{client, path, json_object} {
    set_from_json(json_object);
  }

  void set_attributes(nlohmann::json attributes) override;
  nlohmann::json get_attributes() override;
  TOXIC_TYPES get_type() override;
  long get_timeout() const;
  TIMEOUT* set_timeout(long timeout);

 private:
  long timeout;
};
}

#endif
