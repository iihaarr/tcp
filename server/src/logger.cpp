#include "logger.hpp"

void Logger::Write(const char* msg_, std::size_t msgLen_)
{
   std::unique_lock<std::mutex> lock{ m_mutex };
   std::ofstream file("log.txt", std::ios::app);
   if (file.is_open())
      file.write(msg_, msgLen_);
}

Logger & Logger::GetLogger()
{
   static Logger l;
   return l;
}
