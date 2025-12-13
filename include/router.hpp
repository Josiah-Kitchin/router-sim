

#pragma once

#include "fixed_queue.hpp"
#include "packet.hpp"
#include <cstddef>
#include <optional>
#include <vector>

using RouterNum = size_t;

struct Host
{
    RouterNum gateway_router;
    std::vector<Packet> packets_to_send;

    uint32_t ip_addr; 
};


/// @brief Used to route packets based on the packets dst ip and a table of ip prefixes to other routers
class ForwardingTable
{
  public:
    struct Entry
    {
        uint32_t  ip_prefix;
        uint8_t   prefix_bit; // bit number indicating length of prefix
        RouterNum interface;
    };
    void add_entry(const std::string& ip_addr, uint8_t subnet_mask, RouterNum router);
    void add_entry(uint32_t ip_addr, uint8_t subnet_mask, RouterNum router);
    void set_default_gateway(RouterNum router);

    std::optional<RouterNum> get_interface(const std::string& ip);
    std::optional<RouterNum> get_interface(uint32_t ip);

  private:
    std::vector<Entry> _table;
    std::optional<RouterNum> _default_gateway;
};

/// @brief Simulate a single router in the simulation .
///        Stores a limited number of packets, represented as a node in a graph with access to the full
///        topology.
class Router
{
  public:
    /// @brief Create a router to be used in the simulation 
    /// @param router_num ID and index in the vector of routers 
    /// @param packet_queue_size max size of the packet queue. Will drop packets if exceeded 
    Router(RouterNum router_num, size_t packet_queue_size);

    /// @brief Add a neighbor with a given weight, used for control plane
    /// @param neighbor router id / router idx of the neighbor 
    /// @param weight arbitrary number 
    void add_neighbor(RouterNum neighbor, int weight);

    /// @brief Give the router a referecne to the list of vectors so it can forward packets
    /// @param top topology that stores all routers (including this)
    void set_global_topology(std::vector<Router>* top) { _global_topology = top; }

    /// @brief Store a packet pointer in the packet queue. Will be dropped if packet queue limit exceeded
    /// @param packet pointer to a packet, should stay alive throughout routers lifetime 
    void receive(Packet* packet);

    /// @brief Forward packets from the packet queue to the next router based on the routing table
    /// @param num_packets number of packets to send 
    void forward(size_t num_packets);

    /// @brief Give a router access to a host so it can route packets to them 
    /// @param connected_host Should not go out of scope within routers lifetime 
    void set_connected_host(Host* connected_host) { _connected_host = connected_host; };

    ForwardingTable& get_forwarding_table() { return _forwarding_table; }

    void replace_forwarding_table(const ForwardingTable& forwarding_table) { _forwarding_table = forwarding_table; }

    void replace_forwarding_table(ForwardingTable&& forwarding_table) { _forwarding_table = std::move(forwarding_table); }

    size_t num_packets_in_queue() const { return _packet_queue.size(); }

    RouterNum get_router_num() const { return _num; }; 


  private:
    std::vector<Router>* _global_topology = nullptr;

    std::vector<std::pair<RouterNum, int>> _neighbors;
    RouterNum                              _num = 0;

    FixedQueue<Packet*> _packet_queue;
    ForwardingTable     _forwarding_table;

    Host* _connected_host = nullptr; 
};
