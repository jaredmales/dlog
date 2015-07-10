
#ifndef __dlog_basicLogger_hpp__
#define __dlog_basicLogger_hpp__

//include of dlog.hpp must be before application.hpp
#include "dlog.hpp"
#include "mx/application.hpp"

#include "basicEntry.hpp"
#include "todoEntry.hpp"


#include "randomNumberLinux.hpp"
   
namespace dlog
{
   
class basicLogger : public mx::application
{
protected:
   
   std::string _userName;
   std::string _path;
   
   int _type;
   
   timeStamp _timeStamp;
   
   std::string _text;
   
public:
   
   basicLogger(const timespec & tsp);
   
   //basicEntry<randomNumberLinux> be;
   
   
   virtual void setupConfig();
   virtual void loadConfig();

   virtual int execute();
   
   template<class logT>
   int log(logT & entry);

   
};

inline
basicLogger::basicLogger(const timespec & tsp)
{
   _timeStamp.setTime(tsp);
   _type = DLOG_TYPE_BASIC;
}

inline
void basicLogger::setupConfig()
{
   config.add(mx::configTarget("editor","e", "editor",mx::argType::Required, "", "editor"));
   config.add(mx::configTarget("path","p", "path",mx::argType::Required, "", "path"));

   config.add(mx::configTarget("username","u", "user-name",mx::argType::Required, "", "user-name"));
   config.add(mx::configTarget("type","", "type",mx::argType::Required, "", "type"));
   config.add(mx::configTarget("type-basic","b", "basic",mx::argType::True, "", ""));
   config.add(mx::configTarget("type-todo","t", "todo",mx::argType::True, "", ""));
  
}
   
inline   
void basicLogger::loadConfig()
{
   std::string tmpstr;
   
   tmpstr = config.get<std::string>("username");
   if(tmpstr == "")
   {
      std::cerr << "user name not set" << "\n";
      exit(0);
   }
   _userName = tmpstr;//"jaredmales@gmail.com"
   
 
   _path = config.get<std::string>("path");
   
    
   if(config.nonOptions.size() == 0)
   {
      std::cerr << "no log entry given" << "\n";
      exit(0);
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
      _type = DLOG_TYPE_BASIC;
   
   if(config.get<std::string>("type") == "todo" || config.isSet("type-todo") )
      _type = DLOG_TYPE_TODO;
   
}

inline
int basicLogger::execute()
{   
   switch(_type)
   {
      case DLOG_TYPE_BASIC:
      {  
         basicEntry<randomNumberLinux> entry;
         return log(entry);
      }
      
      case DLOG_TYPE_TODO:
      {
         todoEntry<randomNumberLinux> entry;
         return log(entry);
      }
   }
}


template<class logT>
inline
int basicLogger::log(logT & entry)
{
      
   entry.setUserName(_userName);
   entry.setText(_text);
   entry.setTimeStamp(_timeStamp);
   
   std::ofstream fout;
   
   std::string baseName = entry.getFileName();
   std::string pathName = _path + "/" + _userName + "/";
   std::string fullName = pathName + baseName;
   
   fout.open(fullName);
   
   fout << entry << "\n";
   
   fout.close();
   
   std::string baseCommand, command;
   
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

