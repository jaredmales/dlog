/** \file dlog.hpp
  * \author Jared R. Males
  * \brief dlog application defines and utilities.
  *
  */

#ifndef dlog_hpp
#define dlog_hpp


#include <mx/sys/timeUtils.hpp>

#define DLOG_VERSION  ("0.2")

#define DLOG_TYPE_BASIC 0
#define DLOG_TYPE_BASICSTR "basic"

#define DLOG_TYPE_LATEX  1
#define DLOG_TYPE_LATEXSTR "latex"


#define DLOG_TYPE_HTML  2
#define DLOG_TYPE_HTMLSTR "html"

//#define MX_APP_DEFAULT_configPathGlobal
//#define MX_APP_DEFAULT_configPathGlobal_env
//#define MX_APP_DEFAULT_configPathUser  
//#define MX_APP_DEFAULT_configPathUser_env
//#define MX_APP_DEFAULT_configPathLocal
//#define MX_APP_DEFAULT_configPathLocal_env


#define DLOG_CFG_SECT_PERSONAL     "personal"
#define DLOG_CFG_PERSONAL_USERNAME "username"
#define DLOG_CFG_PERSONAL_REPO     "repo"

#define DLOG_CFG_SECT_EDITOR       "editor"
#define DLOG_CFG_EDITOR_COMMAND    "command"

namespace dlog 
{
 
inline
int getTimestamp(timespec & tsp)
{
   return clock_gettime(CLOCK_REALTIME, &tsp);
}

}

#endif //dlog_hpp

