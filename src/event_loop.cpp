

#include "event_loop.hpp"

bool traffic_exists(const std::vector<Router> routers)
{
    for (const auto& router : routers)
    {
        if (router.num_packets_in_queue() != 0)
            return true;
    }
    return false; 
}

/// @brief Run the main simulation event loop. Simulation data shall not leave this scope 
/// @param routers list of routers in sim
/// @param access_data list of access routers and the packets that will be sent through them. (Where packets originate from)
void run_packet_switching_loop(std::vector<Router>& routers, std::vector<std::pair<RouterNum, std::vector<Packet>>>& access_data)
{
    /* =============================== Data Plane ================================== */ 

    size_t packet_send_rounds = 0; 
    for (auto& [router_num, packets] : access_data)
    {
        packet_send_rounds = std::max(packets.size(), packet_send_rounds);
    }
    size_t access_packet_num = 0; 

    while (access_packet_num < packet_send_rounds || traffic_exists(routers))
    {
        for (auto& [router_num, packets] : access_data)
        {
            if (access_packet_num < packets.size())
            {
                // Dispatch inital packets
                routers[router_num].receive(&packets[access_packet_num++]);
            }
        }

        for (auto& router : routers)
        {
            router.forward(1);
        }
    }
    /* ============================================================================= */ 
}
