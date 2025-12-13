

#include "logger.hpp"
#include <iostream> 

Logger logger(&std::cout);

Logger& Logger::get_instance() { return logger; }

void Logger::open_log_file(const std::string& file_path)
{
    logger._log_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    logger._log_file.open(file_path);
    logger._stream = &logger._log_file;
}

void Logger::log_packet_received(Packet* packet, RouterNum router) 
{ 
    *_stream << "Packet received from Router: " << router << '\n'; 
}

void Logger::log_packet_delivered(Packet* packet, RouterNum router, const std::string& host_ip)
{
    *_stream << "Packet successfully delivered to host IP address " << host_ip << " from router " << router << '\n';
}

void Logger::log_packet_dropped(Packet* packet, RouterNum router, std::string_view reason)
{
    *_stream << "Packet dropped from Router " << router << " for reason: " << reason << '\n';
}



