#ifndef __TOXIC_H__
#define __TOXIC_H__

#include <ctype.h>
#include "toxiproxy_http_client.h"

/*
    Enums of all available types of Toxics.
*/

namespace TOXIPROXY {
enum class TOXIC_TYPES {
  BANDWIDTH,
  LIMIT_DATA,
  LATENCY,
  SLICER,
  SLOW_CLOSE,
  RESET_PEER,
  TIMEOUT,
  INVALID
};

/*
    Base class for all types of Toxics. Toxics maniuplate the pipe between the client and the upstream,
    and are added to or removed from proxies via the TOXIPROXY_HTTP_CLIENT.
*/

class TOXIC {
 public:
  TOXIC(TOXIPROXY_HTTP_CLIENT* client,
        const std::string &toxic_list_path,
        const std::string &name,
        TOXIC_DIRECTION stream);
  TOXIC(TOXIPROXY_HTTP_CLIENT* client, std::string path, nlohmann::json json_object);
  virtual ~TOXIC() = default;
  void remove() const;

  virtual void set_attributes(nlohmann::json attributes) = 0;
  virtual nlohmann::json get_attributes() = 0;
  virtual TOXIC_TYPES get_type() = 0;

  void create_toxic(const std::string &toxic_list_path);
  void post_attribute(std::string name, long value);
  void set_from_json(nlohmann::json json_object);
  void set_toxicity(double toxicity);
  std::string get_name() const;
  TOXIC_DIRECTION get_stream() const;
  double get_toxicity() const;

 private:
  TOXIPROXY_HTTP_CLIENT* client;
  std::string path;
  std::string name;
  TOXIC_DIRECTION stream;
  double toxicity;
};
}

#endif
