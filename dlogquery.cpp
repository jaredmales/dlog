#include <iostream>
#include <fstream>
#include <iomanip>

#include <mx/fileUtils.hpp>

#include "dlog.hpp"
#include "timeStamp.hpp"


struct entryParse
{
   int type;
   
   dlog::timeStamp ts;
   std::string uname;
   long randn;
   
   std::vector<std::string> lines;
   std::vector<std::string> tags;
   
   void parse(const std::string & fpath)
   {
      std::ifstream fin;
      std::string line;
      
      std::string fstr = boost::filesystem::path(fpath).filename().string();
      
      ts.parseFileName(uname, randn, fstr);
      
      fin.open(fpath.c_str());
      
      
      getline(fin, line);
      if(line.find("t=\"basic\"") != std::string::npos) type = DLOG_TYPE_BASIC;
      if(line.find("t=\"latex\"") != std::string::npos) type = DLOG_TYPE_LATEX;
      if(line.find("t=\"html\"") != std::string::npos) type = DLOG_TYPE_HTML;
       
      lines.clear();
      tags.clear();
      
      while(!fin.eof()) 
      {
         getline(fin, line);
      
         if(line.find("</dlog>") != std::string::npos) break;
         
         if(line.find("<tag") != std::string::npos)
         {
            int st = line.find('"', 0);
            ++st;
            int ed = line.find('"', st);
            
            tags.push_back(line.substr(st, ed-st));
            continue;
         }
         
         lines.push_back(line);
      }
         
      fin.close();   
   }
   
};
         

void outputDocBegin()
{
   std::cout << "Content-type: text/xml\n\n";
   
   std::cout <<  "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"  \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n";

   std::cout << "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n";

   std::cout << "<head>";
   std::cout << "  <title>dlog of </title> \n";
   std::cout << "  <script type=\"text/javascript\" src=\"http://math.etsu.edu/LaTeXMathML/LaTeXMathML.js\"></script>\n";
   std::cout << "  <link rel=\"stylesheet\" type=\"text/css\" ";
   std::cout << "  href=\"http://math.etsu.edu/LaTeXMathML/LaTeXMathML.standardarticle.css\" />\n";
   std::cout << "</head>\n";
   
   std::cout << "<body>\n";
}

void outputDocEnd()
{
   std::cout << "</body>\n";
   std::cout << "</html>\n";
      
}

void outputEscapeLine(std::string line)
{
   for(int i=0;i<line.size();++i)
   {
      if(line[i] == '<')
      {
         std::cout << "&lt;";
         continue;
      }
      
      if(line[i] == '>')
      {
         std::cout << "&gt;";
         continue;
      }
      std::cout << line[i];
   }
}


int main()
{
   std::vector<std::string> dlogs = mx::getFileNames("/home/jaredmales/dlog/jaredmales@gmail.com/", "", ".dlog");

   std::string uname;
 
   outputDocBegin();
   
   entryParse ep;
   
   for(int i=dlogs.size()-1; i>=0;--i)
   {
      ep.parse(dlogs[i]);

      std::cout << "<hr /> \n";
      std::cout << "<table width=\"100%\" cellpadding=\"2\" border=\"0\">\n";
      std::cout << "   <colgroup span=\"3\" valign=\"top\">\n";
      std::cout << "      <col width=\"18%\" />\n";
      std::cout << "      <col width=\"44%\" />\n";
      std::cout << "      <col width=\"18%\" />\n";
      std::cout << "   </colgroup>\n";
      std::cout << "   <tbody>\n";
      std::cout << "      <tr align=\"left\">\n";
      std::cout << "         <td>\n";
      std::cout << "            " << ep.ts.year << "-";
      std::cout << std::setw(2) << std::setfill('0') << ep.ts.month << "-";
      std::cout << std::setw(2) << std::setfill('0') << ep.ts.day << "T";
      std::cout << std::setw(2) << std::setfill('0') << ep.ts.hour << ":";
      std::cout << std::setw(2) << std::setfill('0') << ep.ts.minute << ":";
      std::cout << std::setw(2) << std::setfill('0') << ep.ts.second << ".";
      std::cout << std::setw(9) << std::setfill('0') << ep.ts.nanosecond << "\n";
      std::cout << "         </td>\n";
      std::cout << "         <td />\n";
      std::cout << "         <td>\n";
      std::cout << "            " << ep.uname << "\n";
      std::cout << "         </td>\n";
      std::cout << "      </tr>\n";
      std::cout << "   </tbody>\n";
      std::cout << "</table>\n";
      
      std::cout << "<table width=\"100%\" cellpadding=\"2\" border=\"0\">\n";
      std::cout << "   <colgroup span=\"3\" valign=\"top\">\n";
      std::cout << "      <col width=\"18%\" />\n";
      std::cout << "      <col width=\"5%\" />\n";
      std::cout << "      <col width=\"77%\" />\n";
      std::cout << "   </colgroup>\n";
      std::cout << "   <tbody>\n";
      std::cout << "      <tr align=\"left\">\n";
      std::cout << "         <td />\n";
      std::cout << "         <td />\n"; //Here make todo.
      std::cout << "         <td>\n";

      if(ep.type == DLOG_TYPE_BASIC)
      {
         for(int j=0;j<ep.lines.size();++j)
         {
            outputEscapeLine(ep.lines[j]);
            std::cout << "<br />\n";
         }
      }
      else
      {
         for(int j=0;j<ep.lines.size();++j)
         {
            std::cout << ep.lines[j] << "\n";
         }
      }
      std::cout << "         </td>\n";
      std::cout << "      </tr>\n";
      std::cout << "   </tbody>\n";
      std::cout << "</table>\n";
      
      if(ep.tags.size() > 0)
      {
         std::cout << "Tags: ";
         for(int j=0;j<ep.tags.size()-1;++j)
         {
            std::cout << ep.tags[j] << ", ";
         }
         std::cout << ep.tags[ep.tags.size()-1];
         std::cout << "<br />\n";
      }      
   }

   outputDocEnd();

   return 0;
}



