

#pragma once
#include "topology.hpp"
#include <nlohmann/json.hpp>

/// @breif Topology read from a JSON file for small simulation tests
class JSONTopology : public Topology
{
  public:
    JSONTopology(const std::string& file);

    std::vector<Router> create_routers(size_t packet_queue_size) const override;
    std::vector<Host>   create_hosts() const override;
    size_t              num_routers() const override;

  private:
    nlohmann::json _config;
    size_t         _num_routers = 0;
};
