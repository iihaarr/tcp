#include <iostream>
#include "src/tcp_server.hpp"
int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cout << "argc < 2\n";
      return -1;
   }
   TCPServer server(std::atoi(argv[1]));
   std::thread t{ &TCPServer::Listen, &server };
#if 0
   std::this_thread::sleep_for(std::chrono::seconds(3));
   
   server.Stop();
#endif
   t.join();
   return 0;
}

