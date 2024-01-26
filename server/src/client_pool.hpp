#pragma once
#include <WinSock2.h>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

class ClientPool
{
public:
   ClientPool() = default;
   void Handle();
   void Add(SOCKET socketClient);
   void Stop();
   ~ClientPool() = default;
private:
   SOCKET tryPick();
private:
   std::queue<SOCKET> m_clients;
   mutable std::mutex m_mutex;
   bool m_stop{ false };
};

