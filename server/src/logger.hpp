#pragma once
#include <string>
#include <fstream>
#include <future>
class Logger
{
public:
   void Write(const char* msg_, std::size_t msgLen_);
   ~Logger() = default;
   static Logger& GetLogger();
private:
   Logger() = default;
private:
   std::mutex m_mutex;
};

