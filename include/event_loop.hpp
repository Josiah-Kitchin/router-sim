

#pragma once
#include "router.hpp"

void run_packet_switching_loop(std::vector<Router>& router, std::vector<std::pair<RouterNum, std::vector<Packet>>>&);
