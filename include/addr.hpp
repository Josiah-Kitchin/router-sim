
#pragma once

#include <cstdint>
#include <string>

uint32_t    ip_pton(const std::string& ip);
uint64_t    mac_pton(const std::string& mac);
std::string ip_ntop(uint32_t ip);
std::string mac_ntop(uint64_t mac);

