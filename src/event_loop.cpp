

#include "event_loop.hpp"

bool traffic_exists(const std::vector<Router> routers)
{
    for (const auto& router : routers)
    {
        if (router.num_packets_in_queue() != 0)
        {
            return true;
        }
    }
    return false;
}

/// @brief Run the main simulation event loop. Simulation data shall not leave this scope
/// @param routers list of routers in sim
/// @param access_data list of access routers and the packets that will be sent through them. (Where packets originate from)
void run_packet_switching_loop(std::vector<Router>& routers, std::vector<Host>& hosts, size_t packets_per_round, size_t forwards_per_round)
{
    size_t total_packet_send_rounds = 0;
    for (auto& host : hosts)
        total_packet_send_rounds = std::max(host.packets_to_send.size(), total_packet_send_rounds);

    size_t packet_send_round = 0;

    while (packet_send_round < total_packet_send_rounds || traffic_exists(routers))
    {
        for (auto& host : hosts)
        {
            for (size_t i = 0; i < packets_per_round; i++)
            {
                if (packet_send_round < host.packets_to_send.size())
                {
                    // Dispatch inital packets
                    routers[host.gateway_router].receive(&host.packets_to_send[packet_send_round + i]);
                }
            }
        }

        for (auto& router : routers)
        {
            router.forward(forwards_per_round);
        }

        packet_send_round += packets_per_round;
    }
}
