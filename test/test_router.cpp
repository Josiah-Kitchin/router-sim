

#include <gtest/gtest.h> 

#include "router.hpp"

TEST(forwarding_table, get_interface)
{
    ForwardingTable ft; 
    ft.add_entry("192.168.54.0", 24, 0);
    ft.add_entry("192.168.55.0", 24, 1);

    std::optional<RouterNum> result = ft.get_interface("192.168.55.2");

    ASSERT_TRUE(result.has_value() && result.value() == 1);
}

TEST(forwarding_table, get_interface2)
{
    ForwardingTable ft; 
    ft.add_entry("192.168.54.0", 24, 0);
    ft.add_entry("192.167.55.0", 24, 1);
    ft.add_entry("192.169.56.0", 24, 2);
    ft.add_entry("192.190.57.0", 24, 3);
     
    std::optional<RouterNum> result = ft.get_interface("192.169.56.2");
    ASSERT_TRUE(result.has_value() && result.value() == 2);
}

TEST(forwarding_table, get_interface3)
{
    ForwardingTable ft; 
    ft.add_entry("192.168.0.0", 16, 0);
    ft.add_entry("192.167.0.0", 16, 1);
    ft.add_entry("192.199.0.0", 16, 2);
    ft.add_entry("192.198.0.0", 16, 3);
     
    std::optional<RouterNum> result = ft.get_interface("192.198.56.2");
    ASSERT_TRUE(result.has_value() && result.value() == 3);
}

TEST(forwarding_table, get_interface_default)
{
    ForwardingTable ft; 
    ft.add_entry("192.168.0.0", 16, 0);
    ft.add_entry("192.167.0.0", 16, 1);
    ft.add_entry("192.199.0.0", 16, 2);
    ft.add_entry("192.198.0.0", 16, 3);
    ft.set_default_gateway(4);
     
    std::optional<RouterNum> result = ft.get_interface("192.298.56.2");
    ASSERT_TRUE(result.has_value() && result.value() == 4);
}

TEST(forwarding_table, get_interface_none)
{
    ForwardingTable ft; 
    ft.add_entry("192.168.0.0", 16, 0);
    ft.add_entry("192.167.0.0", 16, 1);
    ft.add_entry("192.199.0.0", 16, 2);
    ft.add_entry("192.198.0.0", 16, 3);
     
    std::optional<RouterNum> result = ft.get_interface("192.298.56.2");
    ASSERT_TRUE(!result.has_value());
}
