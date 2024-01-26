#include <iostream>
#include "src/tcp_client.hpp"

int main(int argc, char** argv)
{
   if (argc < 4)
   {
      std::cout << "argc < 4\n";
      return -1;
   }
   const auto name = std::string(argv[1]);
   TCPClient client{ name, std::atoi(argv[2]), std::chrono::seconds(std::atoi(argv[3])) };
   client.Send();
   return 0;
}