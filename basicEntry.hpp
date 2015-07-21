#ifndef __dlog_basicEntry_hpp__
#define __dlog_basicEntry_hpp__

#include <vector>
#include <iostream>


namespace dlog 
{

class basicEntry 
{

protected:
   
   std::string text;
      
public:
   
   basicEntry();

   void setText(const std::string & txt);
         
   virtual void outputEntry(std::ostream & os);
   
};

basicEntry::basicEntry()
{
   return;
}


void basicEntry::setText(const std::string & txt)
{
   text = txt;
}
   
void basicEntry::outputEntry(std::ostream & os)
{
   os << text << "\n";
}



} //namespace dlog 

#endif // __dlog_basicEntry_hpp__
