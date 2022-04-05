#ifndef __SLICER_H__
#define __SLICER_H__

#include <utility>

#include "toxic.h"

/**
   A type of Toxic that slices TCP data up into small bits and adding the given delay between each sliced "packet".
*/

namespace TOXIPROXY {
class SLICER : public TOXIC {
 public:
  SLICER(TOXIPROXY_HTTP_CLIENT* client,
         const std::string &toxic_list_path,
         const std::string &name,
         TOXIC_DIRECTION stream,
         long delay)
      : TOXIC{client, toxic_list_path, name, stream}, delay(delay) {
    create_toxic(toxic_list_path);
  }

  SLICER(TOXIPROXY_HTTP_CLIENT* client, std::string path, nlohmann::json json_object)
      : TOXIC{client, path, json_object} {
    set_from_json(json_object);
  }

  void set_attributes(nlohmann::json attributes) override;
  nlohmann::json get_attributes() override;
  TOXIC_TYPES get_type() override;
  long get_delay() const;
  SLICER* set_delay(long delay);

 private:
  long delay;
};
}

#endif
