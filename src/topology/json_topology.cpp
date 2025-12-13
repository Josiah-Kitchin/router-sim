

#include "topology/json_topology.hpp"
#include "addr.hpp"
#include <fstream>
#include <stdexcept>
#include <algorithm>

using nlohmann::json;

JSONTopology::JSONTopology(const std::string& file)
{
    std::ifstream topology_file;
    topology_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    topology_file.open(file);

    _config      = json::parse(topology_file);
    _num_routers = _config["routers"].size();
}

std::vector<Router> JSONTopology::create_routers(size_t packet_queue_size) const
{
    const std::vector<json>& topology = _config["routers"];

    std::vector<Router> routers;
    routers.reserve(topology.size());

    for (RouterNum i = 0; i < topology.size(); i++)
    {
        const json& router_json = topology[i];
        routers.emplace_back(router_json["id"], packet_queue_size);
        for (const auto& neighbor : router_json["neighbors"])
        {
            RouterNum neighbor_num = neighbor["id"];
            int       weight       = neighbor["weight"];

            if (neighbor_num >= _num_routers)
            {
                throw std::logic_error("Router " + std::to_string(i) + " has neighbor " + std::to_string(neighbor_num) +
                                       " beyond max router num: " + std::to_string(_num_routers));
            }
            routers[i].add_neighbor(neighbor_num, weight);
        }
        if (router_json.contains("forwarding_table"))
        {
            const json& forwarding_table_json = router_json["forwarding_table"];
            for (const json& entry : forwarding_table_json["entries"])
            {
                std::string ip = entry["prefix"];
                routers[i].get_forwarding_table().add_entry(ip, entry["prefix_bit"], entry["router_interface_id"]);
            }
            if (forwarding_table_json.contains("default_gateway_id"))
            {
                routers[i].get_forwarding_table().set_default_gateway(forwarding_table_json["default_gateway_id"]);
            }
        }
    }

    // put routers in order of their ID so they can be indexed by ID 
    std::sort(routers.begin(), routers.end(), [](const auto& r1, const auto& r2) {
        return r1.get_router_num() < r2.get_router_num(); 
    });

    return routers;
}

size_t JSONTopology::num_routers() const { return _num_routers; }

std::vector<Host> JSONTopology::create_hosts() const
{
    std::vector<Host> hosts;

    for (const json& host_json : _config["hosts"])
    {
        Host host;
        host.gateway_router = host_json["gateway_router_id"];
        host.ip_addr        = ip_pton(host_json["ip_addr"]);

        if (host_json.contains("packets_to_send"))
        {
            for (const json& packet : host_json["packets_to_send"])
            {
                host.packets_to_send.push_back({.dst_ip_addr  = ip_pton(packet["dst_ip_addr"]),
                                                .src_ip_addr  = ip_pton(host_json["ip_addr"]),
                                                .ttl          = packet["ttl"]});
            }
        }
        hosts.push_back(host);
    }
    return hosts; 
}
