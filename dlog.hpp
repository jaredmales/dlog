
#ifndef __dlog_hpp__
#define __dlog_hpp__




#define DLOG_VERSION  ("0")

#define DLOG_TYPE_BASIC 0
#define DLOG_TYPE_TODO  1

//#define MX_APP_DEFAULT_configPathGlobal
//#define MX_APP_DEFAULT_configPathGlobal_env
#define MX_APP_DEFAULT_configPathUser  "dlog/dlog.conf"
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

#endif //__dlog_hpp__
