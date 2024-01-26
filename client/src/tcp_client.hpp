#pragma once
#include <string>
#include <chrono>
class TCPClient
{
public:
   TCPClient(const std::string& name_, int port_, std::chrono::seconds period_);
   void Send();
   ~TCPClient() = default;
private:
   std::string m_name;
   int m_port;
   std::chrono::seconds m_period;
};

