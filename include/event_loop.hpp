

#pragma once
#include "router.hpp"

void run_packet_switching_loop(std::vector<Router>& router, std::vector<Host>& hosts, size_t packets_per_round, size_t forwards_per_round);
