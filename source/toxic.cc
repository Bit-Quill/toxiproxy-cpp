#include <utility>

#include <toxiproxy/toxic_type.h>

namespace TOXIPROXY {
TOXIC::TOXIC(TOXIPROXY_HTTP_CLIENT* client,
             const std::string &toxic_list_path,
             const std::string &name,
             TOXIC_DIRECTION stream)
    : client{client}, name{name}, stream{stream}, toxicity{1} {
  this->path = toxic_list_path + "/" + name;
}

TOXIC::TOXIC(TOXIPROXY_HTTP_CLIENT* client, std::string path, nlohmann::json json_object)
    : client{client}, path{path} {}

void TOXIC::remove() const {
  client->delete_path(path);
}

void TOXIC::create_toxic(const std::string &toxic_list_path) {
  std::string stream_value;
  const auto it = TOXIPROXY_HTTP_CLIENT::toxic_direction_to_str_map.find(stream);
  if (it != TOXIPROXY_HTTP_CLIENT::toxic_direction_to_str_map.end()) {
    stream_value = it->second;
  }

  std::string type_value;
  const auto it2 = TOXIC_TYPE::toxic_types_to_str_map.find(get_type());
  if (it2 != TOXIC_TYPE::toxic_types_to_str_map.end()) {
    type_value = it2->second;
  }

  const nlohmann::json toxic_json = {
      {"name", name},
      {"toxicity", toxicity},
      {"stream", stream_value},
      {"type", type_value},
      {"attributes", get_attributes()}
  };

  set_from_json(client->post(toxic_list_path, toxic_json));
}

void TOXIC::post_attribute(std::string name, long value) {
  const nlohmann::json toxic_json = {{name, value}};

  set_from_json(client->post(path, toxic_json));
}

void TOXIC::set_from_json(nlohmann::json json_object) {
  name = json_object["name"].get<std::string>();
  toxicity = json_object["toxicity"].get<double>();
  set_attributes(json_object["attributes"]);

  std::string stream_value = json_object["stream"].get<std::string>();
  for (auto &c: stream_value)
    c = toupper(c);

  const auto it = TOXIPROXY_HTTP_CLIENT::str_to_toxic_direction_map.find(stream_value);
  if (it != TOXIPROXY_HTTP_CLIENT::str_to_toxic_direction_map.end()) {
    stream = it->second;
  }
}

void TOXIC::set_toxicity(double toxicity) {
  set_from_json(client->post(path, "toxicity", toxicity));
}

std::string TOXIC::get_name() const { return name; }
TOXIC_DIRECTION TOXIC::get_stream() const { return stream; }
double TOXIC::get_toxicity() const { return toxicity; }
}
