
#include "utypes.h"
#include "dso_type.h"
#include "myxml.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*****************************************************************
 *
 *                       static code
 *
 ******************************************************************
 */
static FILE*  _fopen(const char *file) {
	FILE *fp;
	fp = fopen(file,"rb");
	if(!fp) { exit(1); }
	return fp;
}
/*
 * 搜索字符串
 * 返回1表示找到,-1表示str=NULL或未找到.
 * origen<0表示找到后要退回到str的开始位置;否则指向str的结束位置.
 */
static int fgotostr(const char *str,int origen,FILE *fp) {
	if(!str) {
		exit(1);
	} else {
		int len=strlen(str);
		while(1) {
			int i=0;
			do {
				char ch=fgetc(fp);
				if(ch == EOF) exit(1);
				if(ch != str[i]) break;
			} while(++i < len);
			if(i == len) 
				break;
			else 
				fseek(fp,-i,SEEK_CUR);
		}
		if(origen < 0)
			fseek(fp,-len,SEEK_CUR);
		return 1;
	}
}
/*
 * 获取字符串的位置偏移量(以字节为单位长度)
 * 返回值>=0表示正确返回偏移量,为-1表示str=NULL或未找到.
 * origen<0表示找到后要退回到str的开始位置;否则指向str的结束位置.
 */
static long fstroffset(const char *str,FILE *fp) {
	if(!str) {
		exit(1);
	} else {
		long offset=0;
		int len=strlen(str);
		while(1) {
			int i=0;
			do {
				char ch = fgetc(fp);
				if(ch == EOF) exit(1);
				offset ++;
				if(ch != str[i]) break;
			} while(++i < len);
			if(i == len) 
				break;
			else {
				offset -= i;
				fseek(fp,-i,SEEK_CUR);
			}
		}
		return offset;
	}
}
/*
 * 转换字符串中存在的非打印字符
 * 返回值：无
 */
static void myxml_converString(char *str) {
	int len=strlen(str);
	if(len < 2) {
		return ;
	} else {
		char s[2];
		while(*(str+1)) {
			memcpy(s,str,2);
			if(s[0] == '\\') {
				switch(s[1]) {
				case 'n': *str = '\n'; break;
				case '[': *str = '<'; break;
				case ']': *str = '>'; break;
				default : continue;
				}
				strcpy(str+1,str+2);
			}
			str++;
		}
	}
}
/*****************************************************************
 *
 *                       public code
 *
 ******************************************************************
 */
/*
 * 获取一个引用字符串文本(被"和"包围起来的类型为type的部分)
 * 返回值>=0表示正确返回偏移量,为-1表示str=NULL或未找到.
 * origen<0表示找到后要退回到str的开始位置;否则指向str的结束位置.
 */
void myxml_fgetString(const char **pstr,const char *type,FILE *fp) {
	long offset;
	char *str;
	fgotostr(type,1,fp);
	fgotostr("\"",1,fp);
	offset = fstroffset("\"",fp);
	str = (char*)malloc(offset);
	fseek(fp,-offset,SEEK_CUR);
	fgets(str,offset,fp);
	myxml_converString(str);
	*pstr=strdup(str);
	free(str);
}
/*
 * 打开xml文件并将文件指针指向以 < 开头的正文紧接着的前面
 * 输入：文件名
 * 返回值：文件句柄
 */
FILE* myxml_ready(const char *file) {
	FILE *fp=_fopen(file);
	fgotostr("<string>",1,fp);
	fgotostr("<",-1,fp);
	return fp;
}
/*
 * 将xml文件指针指向以 < 开头的正文紧接着的前面
 * 输入：文件名
 * 返回值：无
 */
void myxml_gotoNextLine(FILE *fp) {
	if(fgetc(fp) != '<')
		fgotostr("<",-1,fp);
}
/*******************************************************************
 *
 *                         读取文本字符串
 *                       [1/31/2012 robot]
 * format:"%d %s %s %s... " 即%d为读取个数;%s为读取对象名称
 */
void myxml_readTxtString(const char **list,const char *format,FILE *fp) {
	int n=atoi(format);
	format = strchr(format,' ');
	while(*++format == ' ');
	while(n--) {
		if(n==0 && !strchr(format,' ')) {
			myxml_fgetString(list,format,fp);
		} else {
			int len=strchr(format,' ') - format;
			char *str0=(char*)malloc(len+1);
			memcpy(str0,format,len);
			str0[len] = '\0';
			myxml_fgetString(list,str0,fp);
			free(str0);
			format = strchr(format,' ');
			while(*++format == ' ');
		}
		list ++;
	}
}
