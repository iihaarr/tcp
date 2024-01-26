#include <iostream>
#include "client_pool.hpp"
#include "logger.hpp"

void ClientPool::Handle()
{
   using namespace std::chrono;
   static constexpr int kBufSize = 1024;
   static constexpr auto kSleepTime = milliseconds(5);

   char buf[kBufSize];
   memset(buf, 0, kBufSize);
   while (!m_stop)
   {
      auto socket = tryPick();
      if (socket == INVALID_SOCKET)
      {
         std::this_thread::sleep_for(kSleepTime);
         continue;
      }
      const auto receivedBytesCount = recv(socket, buf, kBufSize, 0);
      std::cout << "received bytes = " << receivedBytesCount << '\n';
      if (receivedBytesCount > 0)
      {
         Logger::GetLogger().Write(buf, receivedBytesCount);
         memset(buf, 0, receivedBytesCount);
      }
      else
      {
         std::cout << "last error = " << WSAGetLastError() << '\n';
      }
   }
}

void ClientPool::Add(SOCKET socketClient)
{
   std::lock_guard<std::mutex> lock{ m_mutex };
   m_clients.push(socketClient);
}
void ClientPool::Stop()
{
   m_stop = true;
}
SOCKET ClientPool::tryPick()
{
   std::lock_guard<std::mutex> lock{ m_mutex };
   if (m_clients.empty())
      return INVALID_SOCKET;

   auto socket = m_clients.front();
   m_clients.pop();
   return socket;
}