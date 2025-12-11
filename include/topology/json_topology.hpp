

#pragma once
#include "topology.hpp"
#include <nlohmann/json.hpp>

class JSONTopology : public Topology
{
  public:
    JSONTopology(const std::string& file);

    std::vector<Router>                                    create_routers(size_t packet_queue_size) const override;
    std::vector<std::pair<RouterNum, std::vector<Packet>>> get_access_routers_and_packets() const override;
    size_t                                                 num_routers() const override;

  private:
    nlohmann::json _config;
    size_t         _num_routers = 0;
};
