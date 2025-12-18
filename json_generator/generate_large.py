
from netsim_serialize import Router, Packet, ForwardingTableEntry, Host, generate_json


"""
Used for generating JSON topologies that can be fed into the routing simulation for testing purposes

"""

def main(): 

    routers = []

    # start router 
    routers.append(Router(0, [(1, 1)], [ForwardingTableEntry("192.168.55.0", 24, 1)]))

    for i in range(1, 99): 
        routers.append(Router(i, [(i + 1, 1), (i - 1, 1)], [ForwardingTableEntry("192.168.55.0", 24, i + 1)]))
    
    # circular test 
    routers.append(Router(99, [(98, 1), (100, 1)], [ForwardingTableEntry("192.168.55.0", 24, 0)]))

    # end router 
    routers.append(Router(100, [(99, 1)], []))

    hosts = []
    hosts.append(Host(0, "10.0.0.1", [Packet("192.168.55.1", 1000)]))
    hosts.append(Host(100, "192.168.55.1", []))

    generate_json("topology.json", routers, hosts)
        

if __name__ == "__main__": 
    main()

