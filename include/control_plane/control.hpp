

#pragma once
#include "router.hpp"

/// @brief Generates forwarding tables via some control plane protocol 
class Control
{
  public:
    virtual ~Control() = default;
    virtual void generate_forwarding_tables(std::vector<Router>& routers, std::vector<Host> hosts) = 0;
};
