

#include "router.hpp"
#include "addr.hpp"
#include "logger.hpp"

Router::Router(const std::string& ip_addr, const std::string& mac_addr, RouterNum router_num, size_t packet_queue_size)
    : _ip_addr(ip_pton(ip_addr)), _mac_addr(mac_pton(mac_addr)), _num(router_num), _packet_queue(packet_queue_size)
{
}

void Router::add_neighbor(RouterNum neighbor, int weight) { _neighbors.emplace_back(neighbor, weight); }

void Router::receive(Packet* packet)
{
    if (_packet_queue.size() >= _packet_queue.max_size())
        return;

    if (--packet->ttl == 0)
    {
        Logger::get_instance().log_packet_dropped(packet, _num, "TTL Expired");
        return;
    }

    Logger::get_instance().log_packet_received(packet, _num);
    _packet_queue.enqueue(packet);
}

void Router::forward(size_t packets)
{
    size_t num_to_forward = std::min(packets, _packet_queue.size());

    for (size_t i = 0; i < num_to_forward; i++)
    {
        // Disallows packets to move more than one router per round 
        if (_packet_queue.peek()->forwarded_this_round)
        {
            _packet_queue.peek()->forwarded_this_round = false; 
            return;
        }

        Packet* packet = _packet_queue.dequeue();

        if (_connected_host != nullptr && packet->dst_ip_addr == _connected_host->ip_addr)
        {
            Logger::get_instance().log_packet_delivered(packet, _num, ip_ntop(_connected_host->ip_addr));
            continue;
        }

        std::optional<RouterNum> next_hop = _forwarding_table.get_interface(packet->dst_ip_addr);
        if (!next_hop.has_value())
        {
            Logger::get_instance().log_packet_dropped(packet, _num, "Could not route packet to it's destination");
            return;
        }

        packet->forwarded_this_round = true;

        auto [neighbor_num, weight] = _neighbors[*next_hop];
        (*_global_topology)[neighbor_num].receive(packet);
    }
}
