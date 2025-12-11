

#pragma once
#include "router.hpp"
#include <vector>

/// @breif Topologies are in charge of creating the routers in memory from some source 
///        (i.e. database, test json, random, etc)
class Topology
{
  public:
    virtual ~Topology()                                                        = default;
    virtual std::vector<Router> create_routers(size_t packet_queue_size) const = 0;
    virtual std::vector<Host>   create_hosts() const                           = 0;
    virtual size_t              num_routers() const                            = 0;
};
