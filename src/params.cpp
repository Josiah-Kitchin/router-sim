

#include "params.hpp"
#include "topology/json_topology.hpp"
#include <fstream> 


Params parse_params(const std::string& params_json_file_path)
{
    std::ifstream params_file;
    params_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    params_file.open(params_json_file_path);

    auto json_params = nlohmann::json::parse(params_file);

    Params params; 

    params.packet_queue_size = json_params["packet_queue_size"];
    if (json_params["topology_type"] == "json")
    {
        
        params.json_topology_file_path = json_params["json_file_path"];
        params.topology_type = Params::TopologyType::JSON;
    }
    else
    {
        throw std::logic_error("Unknown Topology Type");
    }

    params.log_file_path = json_params.contains("log_file_path") ? json_params["log_file_path"] : "netsim_logs.txt";
    return params; 
}

std::unique_ptr<Topology> get_topology_type(const Params& params)
{
    switch (params.topology_type)
    {
    case (Params::TopologyType::JSON):
        return std::make_unique<JSONTopology>(params.json_topology_file_path);
        break;
    default:
        throw std::logic_error("Topology Type Unimplemented");
    }
}
