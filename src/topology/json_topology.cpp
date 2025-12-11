

#include "topology/json_topology.hpp"
#include "addr.hpp"
#include <fstream> 
#include <stdexcept>

using nlohmann::json;


JSONTopology::JSONTopology(const std::string& file)
{
    std::ifstream topology_file;
    topology_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    topology_file.open(file);

    _config = json::parse(topology_file);
    _num_routers = _config["topology"].size();
}

std::vector<Router> JSONTopology::create_routers(size_t packet_queue_size) const
{

    const std::vector<json>& topology = _config["topology"];

    std::vector<Router> routers;
    routers.reserve(topology.size());

    for (RouterNum i = 0; i < topology.size(); i++)
    {
        const json& router_json = topology[i];
        routers.emplace_back(router_json["ip_addr"], router_json["mac_addr"], i, packet_queue_size);
        for (const auto& neighbor : router_json["neighbors"])
        {
            RouterNum neighbor_num = neighbor[0];
            int       weight       = neighbor[1];

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
                routers[i].get_forwarding_table().add_entry(ip, entry["prefix_bit"], entry["router_interface"]);
            }
            if (forwarding_table_json.contains("default_gateway"))
            {
                routers[i].get_forwarding_table().set_default_gateway(forwarding_table_json["default_gateway"]);
            }
        }
    }
    return routers;
}

size_t JSONTopology::num_routers() const { return _num_routers; }

std::vector<std::pair<RouterNum, std::vector<Packet>>> JSONTopology::get_access_routers_and_packets() const
{
    std::vector<json>                                      access_routers = _config["access_routers"];
    std::vector<std::pair<RouterNum, std::vector<Packet>>> access_data;
    for (const auto& access_router : access_routers)
    {
        RouterNum           router_num = access_router["router_num"];
        std::vector<Packet> packets;
        for (const json& packet : access_router["packets"])
        {
            packets.push_back({.dst_ip_addr  = ip_pton(packet["dst_ip_addr"]),
                               .src_ip_addr  = ip_pton(packet["src_ip_addr"]),
                               .src_mac_addr = mac_pton(packet["src_mac_addr"]),
                               .ttl          = packet["ttl"]});
        }
        access_data.push_back({router_num, std::move(packets)});
    }
    return access_data;
}
