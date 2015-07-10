#ifndef __dlog_basicEntry_hpp__
#define __dlog_basicEntry_hpp__

#include <vector>
#include <iostream>

#include "timeStamp.hpp"

namespace dlog 
{

template<typename randomNumberT>
class basicEntry 
{

protected:
   std::string _userName;
   
   timeStamp _timeStamp;

   std::vector<std::string> tags;

   std::string type;
   
   std::string text;
   
   randomNumberT randomNumber;
   
   
public:
   
   basicEntry();

   void setUserName(const std::string & userName);

   std::string getUserName()
   {
      return _userName;
   }
   
   void setTimeStamp(const timespec & tsp);
   void setTimeStamp(const timeStamp & tsp);

   void setText(const std::string & txt);
   
   std::string getFileName()
   {
      return _timeStamp.getFileName(_userName, randomNumber.nextRandom());
   }
   
   void  output(std::ostream & os);
   
   virtual void outputEntry(std::ostream & os);
   
};

template<typename randomNumberT>
basicEntry<randomNumberT>::basicEntry()
{
   type = "basic";
   return;
}

template<typename randomNumberT>
void basicEntry<randomNumberT>::setUserName(const std::string & userName)
{
   _userName = userName;
}

template<typename randomNumberT>
void basicEntry<randomNumberT>::setTimeStamp(const timespec & tsp)
{
   _timeStamp.setTime(tsp);
}

template<typename randomNumberT>
void basicEntry<randomNumberT>::setTimeStamp(const timeStamp & tsp)
{
   _timeStamp = tsp;
}

template<typename randomNumberT>
void basicEntry<randomNumberT>::setText(const std::string & txt)
{
   text = txt;
}
   
template<typename randomNumberT>   
void basicEntry<randomNumberT>::output(std::ostream & os)
{
   os << "<dlog v=\"" <<  DLOG_VERSION <<"\" tai=\"" << _timeStamp.getTimeStampString() << "\" t=\"";
   os << type << "\">\n";
   outputEntry(os);
   os << "</dlog>";
}

template<typename randomNumberT>
void basicEntry<randomNumberT>::outputEntry(std::ostream & os)
{
   os << "   " << text << "\n";
}

template<typename randomNumberT>
std::ostream& operator << (std::ostream& os, basicEntry<randomNumberT> & be)
{
   be.output(os);
   return os;
}


} //namespace dlog 

#endif // __dlog_basicEntry_hpp__
