

#pragma once

#include <stdint.h>

struct Packet
{
    uint32_t dst_ip_addr = 0;
    uint32_t src_ip_addr = 0;

    uint16_t ttl = 0; 


    // used to keep packets sent by 1 router per round 
    bool forwarded_this_round = false; 
};

