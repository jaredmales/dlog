

#include <cstdio>
#include <iostream>
#include <fstream>


#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>




#include "dlog.hpp"
#include "basicLogger.hpp"





int main(int argc, char *argv[])
{
   double djm, djmf;
   std::string fts;
   
   timespec tsp;
   
   dlog::getTimestamp(tsp);
      
   dlog::basicLogger log(tsp);
   
   //log.log(argc, argv, tsp);
   
   log.main(argc, argv);
}
   

   


