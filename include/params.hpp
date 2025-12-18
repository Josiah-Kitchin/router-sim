

#pragma once

#include "topology/topology.hpp"
#include "control_plane/control.hpp"
#include <memory>
#include <nlohmann/json.hpp>

struct Params
{
    // Config
    size_t packet_queue_size;
    size_t packets_per_round;
    size_t forwards_per_round;

    enum class TopologyType
    {
        JSON,
    };
    TopologyType topology_type;

    enum class ControlType
    {
        OSPF
    };
    ControlType control_type; 

    // JSON Specific
    std::string json_topology_file_path;

    // Lgging
    std::string log_file_path;
};

Params parse_params(const std::string& param_json_file);

std::unique_ptr<Topology> get_topology_type(const Params& params);
std::unique_ptr<Control> get_control_type(const Params& params);
