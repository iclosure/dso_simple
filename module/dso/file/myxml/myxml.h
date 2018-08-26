
#ifndef myxml_h__
#define myxml_h__


#include <stdio.h>


void myxml_fgetString(const char **pstr,const char *type,FILE *fp);
FILE*myxml_ready(const char *file);
void myxml_gotoNextLine(FILE *fp);
void myxml_readTxtString(const char **list,const char *format,FILE *fp);


#endif // myxml_h__
