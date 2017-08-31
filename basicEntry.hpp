/** \file basicEntry.hpp
  * \author Jared R. Males
  * \brief A basic log entry
  *
  */

#ifndef dlog_basicEntry_hpp
#define dlog_basicEntry_hpp

#include <vector>
#include <iostream>


namespace dlog 
{

///A basic dlog log entry.
class basicEntry 
{

protected:
   
   ///The text of the entry
   std::string text;
      
public:

   ///c'tor
   basicEntry();

   ///Set the text of the entry.
   void setText(const std::string & txt /**< [in] The new text.*/);
         
   ///Output the entry to an ostream.
   virtual void outputEntry(std::ostream & os  /**< [in] the ostream to write to,*/);
   
};

inline
basicEntry::basicEntry()
{
   return;
}

inline
void basicEntry::setText(const std::string & txt)
{
   text = txt;
}

inline
void basicEntry::outputEntry(std::ostream & os)
{
   os << text << "\n";
}



} //namespace dlog 

#endif // dlog_basicEntry_hpp
