

#include "addr.hpp"
#include <sstream> 


uint32_t ip_pton(const std::string& ip)
{
    uint32_t    ip_addr = 0;
    std::string numbers;
    int         num_dots_seen = 0;
    for (char ch : ip)
    {
        if (ch == '.')
        {
            uint32_t byte = std::stoi(numbers);
            ip_addr |= (byte << (24 - (num_dots_seen * 8)));
            numbers.clear();
            num_dots_seen++;
            continue;
        }
        numbers.push_back(ch);
    }
    uint8_t byte = std::stoi(numbers);
    ip_addr |= (byte << (24 - (num_dots_seen * 8)));

    return ip_addr;
}

uint64_t mac_pton(const std::string& mac) 
{  
    uint64_t    mac_addr = 0;
    std::string numbers;
    int         num_dash_seen = 0;
    for (char ch : mac)
    {
        if (ch == '-')
        {
            uint64_t byte = std::stoi(numbers, 0, 16);
            mac_addr |= (byte << (40 - (num_dash_seen * 8)));
            numbers.clear();
            num_dash_seen++;
            continue;
        }
        numbers.push_back(ch);
    }
    uint8_t byte = std::stoi(numbers, 0, 16);
    mac_addr |= (byte << (40 - (num_dash_seen * 8)));

    return mac_addr; 

}


std::string ip_ntop(uint32_t ip)
{
    uint32_t byte_one   = ip & 0xFF;
    uint32_t byte_two   = (ip >> 8) & 0xFF;
    uint32_t byte_three = (ip >> 16) & 0xFF;
    uint32_t byte_four  = (ip >> 24) & 0xFF;

    return std::to_string(byte_four) + '.' + std::to_string(byte_three) + '.' + std::to_string(byte_two) + '.' + std::to_string(byte_one);
}

std::string mac_ntop(uint64_t mac) 
{ 
    std::string mac_address; 
    for (int i = 40; i >= 0; i -= 8)
    {
        uint32_t byte = (mac >> i) & 0xFF; 
        std::stringstream stream;
        stream << std::hex << byte;
        mac_address += stream.str() + '-';
    }
    mac_address.pop_back();
    return mac_address;
}
