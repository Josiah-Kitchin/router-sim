

#pragma once

#include <nlohmann/json.hpp>
#include "topology/topology.hpp"
#include <memory> 

struct Params
{
    size_t packet_queue_size;
    enum class TopologyType
    {
        JSON, 
    };
    TopologyType topology_type; 


    // JSON Specific 
    std::string json_topology_file_path;


    // Lgging
    std::string log_file_path;
};


Params parse_params(const std::string& param_json_file);

std::unique_ptr<Topology> get_topology_type(const Params& params);

