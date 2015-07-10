#ifndef __dlog_todoEntry_hpp__
#define __dlog_todoEntry_hpp__

#include "basicEntry.hpp"

namespace dlog 
{

template<typename randomNumberT>
class todoEntry : public basicEntry<randomNumberT>
{

public:
   
   todoEntry();

};

template<typename randomNumberT>
todoEntry<randomNumberT>::todoEntry()
{
   this->type = "todo";
   return;
}



} //namespace dlog 

#endif // __dlog_todoEntry_hpp__
