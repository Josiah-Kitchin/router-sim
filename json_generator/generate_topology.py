

import json 
from dataclasses import dataclass

"""
Used for generating JSON topologies that can be fed into the routing simulation for testing purposes

"""

@dataclass
class Packet: 
    dst_ip_addr: str
    ttl: int


@dataclass
class Host: 
    gatway_router_id: int
    ip_addr: str 
    packets_to_send: list[Packet]
    

@dataclass 
class ForwardingTableEntry: 
    prefix: str 
    prefix_bit: int
    router_interface_id: int
    

@dataclass 
class Router: 
        id: int
        neighbors: list[tuple[int, int]]
        forwarding_table: list[ForwardingTableEntry]
        default_gateway_id: int


def prepare_host_serilization(hosts: list[Host]) -> list: 
    host_dicts = []
    for host in hosts: 
        json_dict = {"gateway_router_id": host.gatway_router_id, "ip_addr": host.ip_addr, "packets_to_send": []}
        for packet in host.packets_to_send: 
            json_dict["packets_to_send"].append({
                "dst_ip_addr": packet.dst_ip_addr, 
                "ttl": packet.ttl
            })
        host_dicts.append(json_dict)
    return host_dicts

def prepare_router_serilization(routers: list[Router]) -> list:
    router_dicts = [] 
    for router in routers: 
        json_dict = { "id": router.id, "neighbors": [], "forwarding_table": {} }
        for id, weight in router.neighbors: 
            json_dict["neighbors"].append({"id": id, "weight": weight})
        for entry in router.forwarding_table: 
             json_dict["forwarding_table"]["entries"] = {
                "prefix": entry.prefix, 
                "prefix_bit": entry.prefix_bit, 
                "router_interface_id": entry.router_interface_id
             }
        if router.default_gateway_id > 0: 
            json_dict["forwarding_table"]["default_gateway_id"] = router.default_gateway_id
        router_dicts.append(json_dict)
    return router_dicts



def main(): 
    routers = []
    routers.append(Router(0, [(1, 1)], [ForwardingTableEntry("192.168.55.0", 24, 1)], -1))
    routers.append(Router(1, [(1, 1)], [ForwardingTableEntry("192.168.55.0", 24, 2)], -1))
    routers.append(Router(2, [(1, 1)], [], -1))

    hosts = []
    hosts.append(Host(0, "10.0.0.1", [Packet("192.168.55.1", 5)]))
    hosts.append(Host(2, "192.168.55.1", []))

    with open ("pytop.json", "w") as file: 
        json.dump({"routers": prepare_router_serilization(routers), "hosts": prepare_host_serilization(hosts)}, 
                  file, indent=4, )
        

if __name__ == "__main__": 
    main()

