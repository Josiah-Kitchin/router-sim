

#pragma once

#include "fixed_queue.hpp"
#include "packet.hpp"
#include <cstddef>
#include <optional>
#include <vector>

using RouterNum = size_t;

struct ForwardingTableEntry
{
    uint32_t  ip_prefix;
    uint8_t   prefix_bit;
    RouterNum interface;
};

class ForwardingTable
{
  public:
    void                     add_entry(const std::string& ip_addr, uint8_t subnet_mask, RouterNum router);
    void                     add_entry(uint32_t ip_addr, uint8_t subnet_mask, RouterNum router);
    void                     set_default_gateway(RouterNum router);

    std::optional<RouterNum> get_interface(const std::string& ip);
    std::optional<RouterNum> get_interface(uint32_t ip);

  private:
    std::vector<ForwardingTableEntry> _table;
    std::optional<RouterNum>          _default_gateway;
};

/// @brief Simulate a single router in the simulation .
///        Stores a limited number of packets, represented as a node in a graph with access to the full
///        topology.
class Router
{
  public:
    Router(const std::string& ip_addr, const std::string& mac_addr, RouterNum router_num, size_t packet_queue_size);

    void add_neighbor(RouterNum neighbor, int weight);

    void set_global_topology(std::vector<Router>* top) { _global_topology = top; }

    void receive(Packet* packet);

    void forward(size_t packets);

    ForwardingTable& get_forwarding_table() { return _forwarding_table; }

    void replace_forwarding_table(const ForwardingTable& forwarding_table) { _forwarding_table = forwarding_table; }

    void replace_forwarding_table(ForwardingTable&& forwarding_table) { _forwarding_table = std::move(forwarding_table); }

    size_t num_packets_in_queue() const { return _packet_queue.size(); }

  private:
    uint32_t _ip_addr;
    uint64_t _mac_addr;

    std::vector<Router>* _global_topology = nullptr;

    std::vector<std::pair<RouterNum, int>> _neighbors;
    RouterNum                              _num = 0;

    FixedQueue<Packet*> _packet_queue;
    ForwardingTable     _forwarding_table;
};
