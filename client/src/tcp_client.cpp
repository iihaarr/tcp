#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include "tcp_client.hpp"

TCPClient::TCPClient(const std::string& name_, int port_, std::chrono::seconds period_)
   : m_name(name_), m_port(port_), m_period(period_)
{
}

void TCPClient::Send()
{
   WSAData wsaData;
   SOCKADDR_IN addr;

   WSAStartup(MAKEWORD(2, 0), &wsaData);
   const auto serverSocket = socket(AF_INET, SOCK_STREAM, 0);

   InetPton(AF_INET, _T("127.0.0.1"), &addr.sin_addr.s_addr);

   addr.sin_family = AF_INET;
   addr.sin_port = htons(m_port);
   for (;;)
   {
      const auto serverSocket = socket(AF_INET, SOCK_STREAM, 0);
      std::cout << "trying connect to server... " << m_name << '\n';
      if (connect(serverSocket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr)) != 0)
      {
         std::cout << "failed to connect\n";
         std::this_thread::sleep_for(m_period);
         continue;
      }
      auto nowChrono = std::chrono::system_clock::now();
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(nowChrono.time_since_epoch()) % 1000;
      auto timer = std::chrono::system_clock::to_time_t(nowChrono);
      std::tm* now = std::localtime(&timer);
      std::stringstream msgStream;
      msgStream << '[' << std::put_time(now, "%Y-%m-%d %H:%M:%S") << '.' << ms.count() << "] " << m_name << '\n';      
      auto msg = msgStream.str();
      int sended = send(serverSocket, msg.c_str(), msg.length(), 0);
      std::printf("sended bytes = %d\n", sended);
      if (sended == 0)
      {
         std::cout << "can't send data\n";
         std::this_thread::sleep_for(m_period);
         continue;
      }

      std::this_thread::sleep_for(m_period);
   }
}
