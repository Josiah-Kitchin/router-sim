

#include "logger.hpp"

Logger logger;

Logger& Logger::get_instance() { return logger; }

void Logger::open_log_file(const std::string& file_path)
{
    logger._log_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    logger._log_file.open(file_path);
}

void Logger::log_packet_received(Packet* packet, RouterNum router) { _log_file << "Packet received from Router: " << router << '\n'; }

void Logger::log_packet_dropped(Packet* packet, RouterNum router, std::string_view reason)
{
    _log_file << "Packet dropped from Router " << router << " for reason: " << reason << '\n';
}
