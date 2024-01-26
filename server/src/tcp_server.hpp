#pragma once
#include <windows.h>
#include "logger.hpp"
class TCPServer
{
public:
   TCPServer(int port_);
   void Listen();
   void Stop();
   ~TCPServer();
private:
   int m_serverSocket;
   bool m_running{true};
};

