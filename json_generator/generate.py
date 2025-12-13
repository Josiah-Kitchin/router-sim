
from netsim_serialize import Router, Packet, ForwardingTableEntry, Host, generate_json


"""
Used for generating JSON topologies that can be fed into the routing simulation for testing purposes

"""

def main(): 
    routers = []
    routers.append(Router(0, [(1, 1)], [ForwardingTableEntry("192.168.55.0", 24, 1)]))
    routers.append(Router(1, [(1, 1)], [ForwardingTableEntry("192.168.55.0", 24, 2)]))
    routers.append(Router(2, [(1, 1)], []))

    hosts = []
    hosts.append(Host(0, "10.0.0.1", [Packet("192.168.55.1", 5)]))
    hosts.append(Host(2, "192.168.55.1", []))



    generate_json("topology.json", routers, hosts)
        

if __name__ == "__main__": 
    main()

