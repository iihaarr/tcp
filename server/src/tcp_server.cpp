#include <winsock2.h>
#include <errors.h>
#include <future>
#include <functional>
#include <iostream>
#include <array>
#include "tcp_server.hpp" 
#include "client_pool.hpp"

TCPServer::TCPServer(int port_){
   WSADATA wsaData;
   SOCKADDR_IN serverAddr;
   WSAStartup(MAKEWORD(2, 2), &wsaData);

   m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
   serverAddr.sin_addr.s_addr = INADDR_ANY;
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(port_);
   bind(m_serverSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr));
   auto error = listen(m_serverSocket, 0);
   if (error != 0)
      throw std::exception("Can't set socket to listen");
}

void TCPServer::Listen()
{
   std::cout << "listen clients...\n";
   ClientPool ch;
   std::array<std::thread, 2> threads = {
      std::thread{&ClientPool::Handle, std::ref(ch)},
      std::thread{&ClientPool::Handle, std::ref(ch)},
   };

   SOCKADDR_IN clientAddr;
   int clientAddrSize = sizeof(clientAddr);
   while (m_running)
   {
      SOCKET clientSocket;
      if ((clientSocket = accept(m_serverSocket, reinterpret_cast<SOCKADDR*>(&clientAddr), &clientAddrSize)) != INVALID_SOCKET)
      {
         ch.Add(clientSocket);
      }
   }
   ch.Stop();
   std::cout << "server is shutting down...\n";
   for (auto& thread : threads)
   {
      thread.join();
   }

}
void TCPServer::Stop()
{
   m_running = false;
}
TCPServer::~TCPServer()
{
   closesocket(m_serverSocket);
}
