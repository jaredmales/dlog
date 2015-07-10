
#ifndef __dlog_timeStamp_hpp__
#define __dlog_timeStamp_hpp__

#include <time.h>
#include <sys/time.h>

#include <sstream>

#include "mx/timeUtils.hpp"

#define DLOG_TSLEN 30


namespace dlog 
{

class timeStamp 
{
protected:
   int year;
   int month;
   int day;
   int hour;
   int minute;
   int second;
   long nanosecond;

   double mjdn;
   double mjdf;
   
public:
   
   timeStamp();
   
   timeStamp(const timespec & tsp);

   void setTime(const timespec & tsp);

   std::string getTimeStampString();
   std::string getTimeStampString(const timespec & tsp);

   std::string getFileName(const std::string & usern, const int randN);
};

inline
timeStamp::timeStamp()
{
   year = 0;
   month = 0;
   day = 0;
   hour = 0;
   minute = 0;
   second = 0;
   nanosecond = 0;
   mjdn = 0.0;
   mjdf = 0.0;
}

inline
timeStamp::timeStamp(const timespec & tsp)
{
   setTime(tsp);
}

inline
void timeStamp::setTime(const timespec & tsp)
{
   tm tm0;

   mx::timespecUTC2TAIMJD(mjdn, mjdf, tsp, &tm0);

   year = tm0.tm_year + 1900;
   month = tm0.tm_mon + 1;
   day = tm0.tm_mday;
   hour = tm0.tm_hour;
   minute = tm0.tm_min;
   second = tm0.tm_sec;
   nanosecond = tsp.tv_nsec;
}


inline
std::string timeStamp::getTimeStampString()
{
   char cfts[DLOG_TSLEN]; //char formatted timestamp
   
   snprintf(cfts, DLOG_TSLEN, "%.f.%016lu", mjdn, (unsigned long) (mjdf*1e16 + 0.5));
     
   std::string fts = cfts;
  
   
   return fts;
}

inline
std::string timeStamp::getTimeStampString(const timespec & tsp)
{
   setTime(tsp);
   return getTimeStampString();
}


inline
std::string timeStamp::getFileName(const std::string & usern, const int randN)
{
    //std::ostringstream fname;
    std::string rvstr;
    int nc = (4+1)+(2+1)+(2+1)+(2+1)+(2+1)+(2+1+9+1)+(usern.length()+1) + (9+1) + 5+1;
    char *fname = (char *) malloc(nc*sizeof(char));
    
    snprintf(fname, nc, "%04d_%02d_%02d_%02d_%02d_%02d.%09ld_%s_%09d.dlog", year,month,day,
                                 hour, minute, second, nanosecond,usern.c_str(),randN);
    
    //fname <<  year << "_" << month << "_" << day << "_" << hour << "_" << minute << "_" << second << ".";
    //fname << nanosecond <<  "_" << usern << "_" << randN << ".dslog";
    rvstr = fname;
    free(fname);
    
    return rvstr;
    
}


} //namespace dlog 

#endif //__dlog_timeStamp_hpp__






