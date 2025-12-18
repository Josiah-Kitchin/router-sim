
#pragma once

#include "control.hpp"

class OSPFControl : public Control
{
  public:
    void generate_forwarding_tables(std::vector<Router>& routers, std::vector<Host> hosts) override;
};
