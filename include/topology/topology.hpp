

#pragma once
#include "router.hpp"
#include <vector>

class Topology
{
  public:
    virtual ~Topology()                                                                                           = default;
    virtual std::vector<Router>                                    create_routers(size_t packet_queue_size) const = 0;
    virtual std::vector<std::pair<RouterNum, std::vector<Packet>>> get_access_routers_and_packets() const         = 0;
    virtual size_t                                                 num_routers() const                            = 0;
};
