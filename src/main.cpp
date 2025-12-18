

#include "event_loop.hpp"
#include "logger.hpp"
#include "params.hpp"
#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
    const std::string params_file = "../params.json";

    Params params = parse_params(params_file);

    if (!params.log_file_path.empty())
        Logger::get_instance().open_log_file(params.log_file_path);

    Logger::get_instance().set_mode(Logger::Mode::DEBUG);

    std::unique_ptr<Topology> topology = get_topology_type(params);

    std::vector<Router> routers = topology->create_routers(params.packet_queue_size);

    for (auto& router : routers)
        router.set_global_topology(&routers);

    std::vector<Host> hosts = topology->create_hosts();

    for (auto& host : hosts)
        routers[host.gateway_router].set_connected_host(&host);

    std::unique_ptr<Control> control = get_control_type(params);

    control->generate_forwarding_tables(routers, hosts);

    run_packet_switching_loop(routers, hosts, params.packets_per_round, params.forwards_per_round);

    std::cout << "*========== Simulation Complete ==========*" << std::endl;

    return 0;
}
