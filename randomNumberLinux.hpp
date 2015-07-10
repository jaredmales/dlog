
#ifndef __dlog_randomNumberLinux_hpp__
#define __dlog_randomNumberLinux_hpp__

namespace dlog
{

///Random number generator for Linux, which uses /dev/urandom for seed
class randomNumberLinux
{
   bool initialized;
   
   drand48_data _state;
   
public:
   randomNumberLinux()
   {
      initialized = false;
   }
   
   void initialize()
   {
      long int seedval;
      
      int fd;
      
      fd = open("/dev/urandom", O_RDONLY);
      
      int rv =read(fd, &seedval, sizeof(long int));
      
      close(fd);
      
    
      if(rv < 0)
      {
         std::cerr << "read from /dev/urandom returned error\n";
         
         return;
      }
      
      srand48_r(seedval, &_state);
      
   }
   
   int nextRandom()
   {
      if(!initialized) initialize();
      
      long int result;
      
      lrand48_r(&_state, &result);
      
      return floor((result/2147483648.) * (1e9-1.));
   }

};

} //namespace dlog

#endif //__dlog_randomNumberLinux_hpp__

