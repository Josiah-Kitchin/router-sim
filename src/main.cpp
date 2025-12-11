

#include "event_loop.hpp"
#include "logger.hpp"
#include "params.hpp"
#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
    const std::string params_file = argc < 2 ? "params.json" : argv[1];

    Params params = parse_params(params_file);

    Logger::get_instance().open_log_file(params.log_file_path);

    std::unique_ptr<Topology> topology = get_topology_type(params);

    std::vector<Router> routers = topology->create_routers(params.packet_queue_size);

    for (auto& router : routers)
        router.set_global_topology(&routers);

    auto access_routers_and_packets = topology->get_access_routers_and_packets();

    run_packet_switching_loop(routers, access_routers_and_packets);

    std::cout << "Router Simulation Complete" << std::endl; 

    return 0;
}
