
#ifndef __dlog_basicLogger_hpp__
#define __dlog_basicLogger_hpp__

//include of dlog.hpp must be before application.hpp
#include "dlog.hpp"
#include "mx/application.hpp"

#include "timeStamp.hpp"

#include "basicEntry.hpp"
#include "todoEntry.hpp"

#include <set>

   
namespace dlog
{
   
template<typename randomNumberT>   
class basicLogger : public mx::application
{
protected:
   
   randomNumberT randomNumber;
   std::string _userName;
   std::string _path;
   
   int _type;
   std::string _typeStr;
   
   timeStamp _timeStamp;
   std::string _fileName;
   
   std::string _text;
   
   ///Set to true if entry is a to-do list entry
   bool _isToDo;

   ///Collect the tags set by the configuration
   /** Is a std::set to avoid duplication of tags.
     */
   std::set<std::string> _tags;
   
public:
   
   basicLogger(const timespec & tsp);

   void setUserName(const std::string & userName);
   std::string getUserName();
   
   void setTimeStamp(const timespec & tsp);
   void setTimeStamp(const timeStamp & tsp);

   std::string getFileName();
   std::string getPathName();
   std::string getFullName();
   
   //basicEntry<randomNumberLinux> be;
   
   
   virtual void setupConfig();
   virtual void loadConfig();

   virtual int execute();
   
  // template<class logT>
  // int log(logT & entry);

   template<class logT>
   int writeLog(logT & entry);
   
   int commitLog();
   
};

template<typename randomNumberT>
basicLogger<randomNumberT>::basicLogger(const timespec & tsp)
{
   _timeStamp.setTime(tsp);
   _type = DLOG_TYPE_BASIC;
   _typeStr = DLOG_TYPE_BASICSTR;
   
   _isToDo = false;
}


template<typename randomNumberT>
std::string basicLogger<randomNumberT>::getUserName()
{
   return _userName;
}
   
template<typename randomNumberT>
void basicLogger<randomNumberT>::setUserName(const std::string & userName)
{
   _userName = userName;
}

template<typename randomNumberT>
void basicLogger<randomNumberT>::setTimeStamp(const timespec & tsp)
{
   _timeStamp.setTime(tsp);
}

template<typename randomNumberT>
void basicLogger<randomNumberT>::setTimeStamp(const timeStamp & tsp)
{
   _timeStamp = tsp;
}

template<typename randomNumberT>
std::string basicLogger<randomNumberT>::getFileName()
{
   return _fileName;
}

template<typename randomNumberT>
std::string basicLogger<randomNumberT>::getPathName()
{
   return (_path + "/" + _userName + "/");
}

template<typename randomNumberT>
std::string basicLogger<randomNumberT>::getFullName()
{
   return getPathName() + getFileName();
}

template<typename randomNumberT>
void basicLogger<randomNumberT>::setupConfig()
{
   config.add(mx::configTarget("editor","e", "editor",mx::argType::Required, "", "editor"));
   config.add(mx::configTarget("path","p", "path",mx::argType::Required, "", "path"));

   config.add(mx::configTarget("username","u", "user-name",mx::argType::Required, "", "user-name"));
   config.add(mx::configTarget("type","", "type",mx::argType::Required, "", "type"));
   config.add(mx::configTarget("type-basic","b", "basic",mx::argType::True, "", ""));
   
   config.add(mx::configTarget("todo","t", "todo",mx::argType::True, "", ""));
   
   config.add(mx::configTarget("tags", "", "tag", mx::argType::Required, "", "tag"));
  
}
   
template<typename randomNumberT>
void basicLogger<randomNumberT>::loadConfig()
{
   std::string tmpstr;
   
   tmpstr = config.get<std::string>("username");
   if(tmpstr == "")
   {
      std::cerr << "user name not set" << "\n";
      exit(0);
   }
   _userName = tmpstr;//"jaredmales@gmail.com"
   _fileName =  _timeStamp.getFileName(_userName, randomNumber.nextRandom());
 
   _path = config.get<std::string>("path");
   
    
   if(config.nonOptions.size() == 0)
   {
      tmpstr = "";
   }
   else
   {
      tmpstr = config.nonOptions[0];
      for(int i=1;i<config.nonOptions.size(); ++i)
      {
         tmpstr += " " + config.nonOptions[i];
      }
   }
   _text = tmpstr;

  
   
   if(config.get<std::string>("type") == "basic" || config.isSet("type-basic") )
   {
      _type = DLOG_TYPE_BASIC;
      _typeStr = DLOG_TYPE_BASICSTR;
   }
   
  
   //Set for todo
   if(config.isSet("todo") )
   {
      _isToDo = true;
   }
   
   //Load the tags
   for(int i=0; i< config.count("tags"); ++i)
   {
      _tags.insert(config.get<std::string>("tags", i));
   }
      
}

template<typename randomNumberT>
int basicLogger<randomNumberT>::execute()
{   
   std::string fullName;
   
   switch(_type)
   {
      case DLOG_TYPE_BASIC:
      {  
         basicEntry entry;
         writeLog(entry);
      }
      
   }
   
   if(_text == "")
   {
      std::string command = "vim -c 'startinsert' +2 " + getFullName();
      int r = system(command.c_str());
   }
   
   commitLog();
   
}


template<typename randomNumberT>
template<class logT>
int basicLogger<randomNumberT>::writeLog(logT & entry)
{
   
   entry.setText(_text);
   
   std::ofstream fout;
      
   fout.open(getFullName());
   
   //fout << "<dlog v=\"" <<  DLOG_VERSION <<"\" tai=\"" << _timeStamp.getTimeStampString() << "\" t=\"";
   fout << "<dlog v=\"" <<  DLOG_VERSION <<"\" t=\"";
   fout << _typeStr << "\">\n";
   
   entry.outputEntry(fout);
   
   
   if(_isToDo)
   {
      fout << "<todo />\n";
   }
   
   for(std::set<std::string>:: iterator tagit = _tags.begin(); tagit != _tags.end(); ++tagit)
   {
      fout << "<tag name=\"" << *tagit << "\" />\n";
   }
   fout << "</dlog>";
   
   
   fout.close();
   
}
   
template<typename randomNumberT>
int basicLogger<randomNumberT>::commitLog()
{
   std::string baseCommand, command;
   
   std::string pathName = getPathName();
   std::string fullName = getFullName();
   
   baseCommand = "git --git-dir=";
   baseCommand += pathName + ".git  --work-tree=" + pathName + " ";
   command =  baseCommand + "add ";
   command += fullName;
   command += " >> /dev/null";
   //std::cout << command << "\n";
   int rv = system(command.c_str());
   
   command = baseCommand + "commit --allow-empty-message -m '' ";
   command += fullName;
   command += " >> /dev/null";
   //std::cout << command << "\n";
  
   rv = system(command.c_str());
   
}

} //namespace dlog

#endif //__dlog_basicLogger_hpp__

