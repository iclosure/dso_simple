
#ifndef DSO_GLOBAL_H
#define DSO_GLOBAL_H

#include "dso_type.h"


/**********************************************************
 *
 *                 系统信息(变量、??)
 */
PROJECT_INFO	prj_info;

/********************************************************************
 *
 *                      Functions
 */
// isdel=1表示释放指针变量占用的空间，否则申请空间
void dso_initVariable(PROJECT_INFO *info,int isdel);




#endif /*DSO_GLOBAL_H*/
