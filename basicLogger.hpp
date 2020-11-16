/** \file basicLogger.hpp
  * \author Jared R. Males
  * \brief The basic logger application.
  *
  */

#ifndef dlog_basicLogger_hpp
#define dlog_basicLogger_hpp

#include <iostream>
#include <fstream>

//include of dlog.hpp must be before application.hpp
#include "dlog.hpp"
#include <mx/app/application.hpp>

#include "timeStamp.hpp"

#include "basicEntry.hpp"
#include "todoEntry.hpp"

#include <set>


namespace dlog
{

///The basic logger application
/**
  * \tparam is a random number generation class, which is OS dependent.
  */
template<typename randomNumberT>
class basicLogger : public mx::app::application
{
protected:

   randomNumberT randomNumber;
   std::string _userName;
   std::string _path;

   int _type;
   std::string _typeStr;

   timeStamp _timeStamp;
   std::string _fileName;

   bool _revise {false};

   std::string _text;

   ///Set to true if entry is a to-do list entry
   bool _isToDo;

   ///Collect the tags set by the configuration
   /** Is a std::set to avoid duplication of tags.
     */
   std::set<std::string> _tags;

public:

   ///Constructor
   basicLogger(const timespec & tsp /**< [in] */);

   void setUserName(const std::string & userName /**< [in] */);
   std::string getUserName();

   void setTimeStamp(const timespec & tsp /**< [in] */);
   void setTimeStamp(const timeStamp & tsp /**< [in] */);

   std::string getFileName();
   std::string getPathName();
   std::string getFullName();

   //basicEntry<randomNumberLinux> be;


   virtual void setupConfig();
   virtual void loadConfig();

   virtual int execute();

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
   //config.add("editor","e", "editor",mx::app::argType::Required, "", "editor", false, "string", "Not implemented yet.  Currently always vim");
   config.add("path","p", "path",mx::app::argType::Required, "", "path", true, "string", "The path of the dlog directory.");

   config.add("username","u", "user-name",mx::app::argType::Required, "", "user-name", true, "string", "The user name");
   config.add("type","", "type",mx::app::argType::Required, "", "type");
   config.add("type-basic","b", "basic",mx::app::argType::True, "", "");
   config.add("type-latex","l", "latex",mx::app::argType::True, "", "");
   config.add("type-html","w", "html",mx::app::argType::True, "", "");

   config.add("todo","t", "todo",mx::app::argType::True, "", "");

   config.add("tags", "", "tag", mx::app::argType::Required, "", "tag");

   config.add("revise","r", "revise", mx::app::argType::Required, "", "revise", false, "string", "Revise a file, you must give the complete file name, but not the path.");
}

template<typename randomNumberT>
void basicLogger<randomNumberT>::loadConfig()
{
   std::string tmpstr;

   config(tmpstr, "username");
   
   if(tmpstr == "")
   {
      std::cerr << "user name not set" << "\n";
      exit(0);
   }
   _userName = tmpstr;//"jaredmales@gmail.com"

   config(_fileName, "revise");
   if(_fileName != "")
   {
      _revise = true;
   }
   else
   {
      _revise = false;
      _fileName =  _timeStamp.getFileName(_userName, randomNumber.nextRandom());
   }

   config(_path, "path");

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
   
   config(tmpstr, "type");

   if(tmpstr == "basic" || config.isSet("type-basic") )
   {
      _type = DLOG_TYPE_BASIC;
      _typeStr = DLOG_TYPE_BASICSTR;
   }
   if(tmpstr == "latex" || config.isSet("type-latex") )
   {
      _type = DLOG_TYPE_LATEX;
      _typeStr = DLOG_TYPE_LATEXSTR;
   }

   if(tmpstr == "html" || config.isSet("type-html") )
   {
      _type = DLOG_TYPE_HTML;
      _typeStr = DLOG_TYPE_HTMLSTR;
   }

   //Set for todo
   if(config.isSet("todo") )
   {
      _isToDo = true;
   }

   //Load the tags
   for(int i=0; i< config.count("tags"); ++i)
   {
      std::string nt;
      config.get<std::string>(nt, "tags", i);
      _tags.insert(nt);
   }

}

template<typename randomNumberT>
int basicLogger<randomNumberT>::execute()
{
   std::string fullName;

   if(!_revise)
   {
      switch(_type)
      {
         case DLOG_TYPE_BASIC:
         {
            basicEntry entry;
            writeLog(entry);
            break;
         }
         case DLOG_TYPE_LATEX:
         {
            basicEntry entry;
            writeLog(entry);
            break;
         }
         case DLOG_TYPE_HTML:
         {
            basicEntry entry;
            writeLog(entry);
            break;
         }
      }
   }

   if(_text == "" || _revise)
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

   int rv = system(command.c_str());

   if(rv != 0)
   {
      std::cerr << "dlog: git error. (" << __FILE__ << " " << __LINE__ << ")\n";
      std::cerr << "command was: " << command << "\n";
   }

   command = baseCommand + "commit --allow-empty-message -m '' ";
   command += fullName;
   command += " >> /dev/null";

   rv = system(command.c_str());

   if(rv == 0)
   {
      std::cout << "Committed: " << _fileName << "\n";
   }
   else
   {
      std::cerr << "dlog: git error. (" << __FILE__ << " " << __LINE__ << ")\n";
      std::cerr << "command was: " << command << "\n";
      std::cerr << "returned: " << rv << "\n";
   }

   return rv;

}

} //namespace dlog

#endif //dlog_basicLogger_hpp
