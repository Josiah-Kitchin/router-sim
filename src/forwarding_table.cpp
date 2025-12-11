

#include "addr.hpp"
#include "router.hpp"

void ForwardingTable::add_entry(const std::string& ip_addr, uint8_t subnet_mask, RouterNum router)
{
    add_entry(ip_pton(ip_addr), subnet_mask, router);
}

void ForwardingTable::add_entry(uint32_t ip_addr, uint8_t subnet_mask, RouterNum router) { _table.push_back({ip_addr, subnet_mask, router}); }

void ForwardingTable::set_default_gateway(RouterNum router) { _default_gateway = router; }

std::optional<RouterNum> ForwardingTable::get_interface(const std::string& dst_ip_addr) { return get_interface(ip_pton(dst_ip_addr)); }

std::optional<RouterNum> ForwardingTable::get_interface(uint32_t dst_ip_addr)
{
    uint8_t                  largest_bit_matched = 0;
    std::optional<RouterNum> router;
    for (const auto& entry : _table)
    {
        uint8_t  shift_amount   = 32 - entry.prefix_bit;
        uint32_t prefix_shifted = entry.ip_prefix >> shift_amount;
        uint32_t dst_shifted    = dst_ip_addr >> shift_amount;

        if (prefix_shifted == dst_shifted)
        {
            if (largest_bit_matched < entry.prefix_bit)
            {
                largest_bit_matched = entry.prefix_bit; 
                router = entry.interface; 
            }
        }
    }
    if (!router.has_value() && _default_gateway.has_value())
    {
        return _default_gateway;
    }
    return router;
}
