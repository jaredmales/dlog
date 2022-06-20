/** \file dlog.cpp
  * \author Jared R. Males
  * \brief The dlog main function.
  *
  */


#include "dlog.hpp"
#include "basicLogger.hpp"

#include "randomNumberLinux.hpp"

int main(int argc, char *argv[])
{
   timespec tsp;
   
   dlog::getTimestamp(tsp);
      
   dlog::basicLogger<dlog::randomNumberLinux> log(tsp);
      
   
   
   log.main(argc, argv);
}
   

   


