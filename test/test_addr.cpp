

#include <gtest/gtest.h> 
#include "addr.hpp"


TEST(addr, ip_pton)
{
    std::string ip = "192.168.55.1";
    uint32_t nip = ip_pton(ip);
    ASSERT_EQ(nip, 3232249601);
}

TEST(addr, ip_ntop)
{
    uint32_t ip = 3232249601;
    ASSERT_EQ("192.168.55.1", ip_ntop(ip));
}

TEST(addr, mac_pton)
{
    std::string mac = "ff-bA-a7-2c-82-c8";
    ASSERT_EQ(281177133712072, mac_pton(mac));
}

TEST(addr, mac_ntop)
{
    uint64_t mac = 281177133712072;
    ASSERT_EQ("ff-ba-a7-2c-82-c8", mac_ntop(mac));
}


