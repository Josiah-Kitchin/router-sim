

#pragma once

#include "packet.hpp"
#include "router.hpp"
#include <fstream>
#include <string>

class Logger
{
  public:
    Logger(std::ostream* stream) : _stream(stream) {};
    static Logger& get_instance();
    static void    open_log_file(const std::string& file_path);
    void           log_packet_received(Packet* packet, RouterNum router);
    void           log_packet_dropped(Packet* packet, RouterNum router, std::string_view reason);
    void           log_packet_delivered(Packet* packet, RouterNum router, const std::string& host_ip);

  private:
    std::ostream* _stream; 

    std::ofstream _log_file;
};
