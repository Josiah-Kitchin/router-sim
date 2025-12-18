

import json 
from dataclasses import dataclass


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
    default_gateway_id: int | None = None


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
        json_dict = { "id": router.id, "neighbors": [], "forwarding_table": { "entries": [] } }
        for id, weight in router.neighbors: 
            json_dict["neighbors"].append({"id": id, "weight": weight})
        for entry in router.forwarding_table: 
             json_dict["forwarding_table"]["entries"].append({
                "prefix": entry.prefix, 
                "prefix_bit": entry.prefix_bit, 
                "router_interface_id": entry.router_interface_id
             })
        if router.default_gateway_id is not None: 
            json_dict["forwarding_table"]["default_gateway_id"] = router.default_gateway_id
        router_dicts.append(json_dict)
    return router_dicts


def generate_json(file_name: str, routers: list[Router], hosts: list[Host]): 
    with open(file_name, "w") as file: 
        json.dump({"routers": prepare_router_serilization(routers), "hosts": prepare_host_serilization(hosts)}, 
                  file, indent=4, )


