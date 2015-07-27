#include <iostream>
#include <fstream>
#include <iomanip>

#include <mx/fileUtils.hpp>

#include "timeStamp.hpp"

int main()
{
   std::ifstream fin;
   std::string line;
   std::vector<std::string> dlogs = mx::getFileNames("/home/jaredmales/dlog/jaredmales@gmail.com/", "", ".dlog");

   dlog::timeStamp ts;
   std::string uname;
   long randn;
   
   std::cout << "Content-type: text/xml\n\n";
   std::cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
   std::cout << "<?xml-stylesheet type=\"text/xsl\" href=\"dlogstandard.xsl\"?>\n";
   std::cout << "<dlogsheet>\n";

   for(int i=dlogs.size()-1; i>=0;--i)
   {
      std::string fstr = boost::filesystem::path(dlogs[i]).filename().string();
      
      ts.parseFileName(uname, randn, fstr);
      
      fin.open(dlogs[i].c_str());
      getline(fin, line);
      std::cout << line << "\n";
      std::cout << "<yr>" << ts.year << "</yr>\n";
      std::cout << "<mo>" << std::setw(2) << std::setfill('0') << ts.month << "</mo>\n";
      std::cout << "<dy>" << std::setw(2) << std::setfill('0') <<ts.day << "</dy>\n";
      std::cout << "<hr>" << std::setw(2) << std::setfill('0') <<ts.hour << "</hr>\n";
      std::cout << "<mn>" << std::setw(2) << std::setfill('0') <<ts.minute << "</mn>\n";
      std::cout << "<ss>" << std::setw(2) << std::setfill('0') <<ts.second << "</ss>\n";
      std::cout << "<ns>" << std::setw(9) << std::setfill('0') <<ts.nanosecond << "</ns>\n";
      std::cout << "<username>" << uname << "</username>\n";
      while(!fin.eof()) 
      {
         getline(fin, line);
      
         
         if(line.find("</dlog>") != std::string::npos) break;
         std::cout << "<line>\n<![CDATA[" << "\n";
         std::cout << line;
         std::cout << "]]></line>\n";
      }
      
      
      std::cout << line << "\n";
      fin.close();
   }


   std::cout << "</dlogsheet>\n";

   return 0;
}



