<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" indent="yes" doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd" doctype-public="-//W3C//DTD XHTML 1.0 Transitional//EN"/>

 
   <xsl:template match="/">
      <html xmlns="http://www.w3.org/1999/xhtml" dir="ltr">
         <head>
            <title>dlog of <xsl:value-of select="dlogsheet/username" /> <br /></title>
            <script type="text/javascript" src="http://math.etsu.edu/LaTeXMathML/LaTeXMathML.js"></script>
            <link rel="stylesheet" type="text/css" href="http://math.etsu.edu/LaTeXMathML/LaTeXMathML.standardarticle.css" />
         </head>
         
         <body lang="en-US">
            <h3> This is the dlog of <xsl:value-of select="dlogsheet/username" /> </h3>
         
            <xsl:for-each select="dlogsheet/dlog" >
               <hr />
                 <table width="100%" cellpadding="2" border="0">
                     <colgroup span="3" valign="top">
                        <col width="18%" />
                        <col width="44%" />
                         <col width="18%" />
                     </colgroup>
                     <tbody>
                     <tr align="left">
                        <td><xsl:value-of select="yr" />-<xsl:value-of select="mo" />-<xsl:value-of select="dy" />T<xsl:value-of select="hr" />:<xsl:value-of select="mn" />:<xsl:value-of select="ss" />.<xsl:value-of select="ns" /></td>
                        <td> </td>
                        <td> <xsl:value-of select="username" /></td>
                     </tr>
                     </tbody> 
                  </table>
                  <table width="100%" cellpadding="2" border="0">
                     <colgroup span="3" valign="top">
                        <col width="18%" />
                        <col width="5%" />
                        <col width="77%" />
                     </colgroup>
                     <tbody>
                        <tr align="left">
                           <td />
                           <xsl:choose>
                              <xsl:when test="@t='todo'" >
                                 <td>todo</td>
                              </xsl:when>
                              <xsl:otherwise>
                                 <td />
                              </xsl:otherwise>
                           </xsl:choose>
                            
                           <xsl:choose>
                              <xsl:when test="@t='basic'">
                              <td>
                                 <xsl:for-each select="line">
                                    <xsl:value-of select="." /><br /> 
                                 </xsl:for-each>
                               </td>   
                              </xsl:when>
                              <xsl:otherwise>
                                  <xsl:for-each select="td">
                                    <xsl:copy-of select="." />
                                  </xsl:for-each>
                              </xsl:otherwise>
                           </xsl:choose>
                          
                        </tr>
                     </tbody> 
                  </table>
            </xsl:for-each>
            <hr />
         </body>
      </html>
   </xsl:template>
</xsl:stylesheet>

