
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
 * �����ַ���
 * ����1��ʾ�ҵ�,-1��ʾstr=NULL��δ�ҵ�.
 * origen<0��ʾ�ҵ���Ҫ�˻ص�str�Ŀ�ʼλ��;����ָ��str�Ľ���λ��.
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
 * ��ȡ�ַ�����λ��ƫ����(���ֽ�Ϊ��λ����)
 * ����ֵ>=0��ʾ��ȷ����ƫ����,Ϊ-1��ʾstr=NULL��δ�ҵ�.
 * origen<0��ʾ�ҵ���Ҫ�˻ص�str�Ŀ�ʼλ��;����ָ��str�Ľ���λ��.
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
 * ת���ַ����д��ڵķǴ�ӡ�ַ�
 * ����ֵ����
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
 * ��ȡһ�������ַ����ı�(��"��"��Χ����������Ϊtype�Ĳ���)
 * ����ֵ>=0��ʾ��ȷ����ƫ����,Ϊ-1��ʾstr=NULL��δ�ҵ�.
 * origen<0��ʾ�ҵ���Ҫ�˻ص�str�Ŀ�ʼλ��;����ָ��str�Ľ���λ��.
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
 * ��xml�ļ������ļ�ָ��ָ���� < ��ͷ�����Ľ����ŵ�ǰ��
 * ���룺�ļ���
 * ����ֵ���ļ����
 */
FILE* myxml_ready(const char *file) {
	FILE *fp=_fopen(file);
	fgotostr("<string>",1,fp);
	fgotostr("<",-1,fp);
	return fp;
}
/*
 * ��xml�ļ�ָ��ָ���� < ��ͷ�����Ľ����ŵ�ǰ��
 * ���룺�ļ���
 * ����ֵ����
 */
void myxml_gotoNextLine(FILE *fp) {
	if(fgetc(fp) != '<')
		fgotostr("<",-1,fp);
}
/*******************************************************************
 *
 *                         ��ȡ�ı��ַ���
 *                       [1/31/2012 robot]
 * format:"%d %s %s %s... " ��%dΪ��ȡ����;%sΪ��ȡ��������
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
