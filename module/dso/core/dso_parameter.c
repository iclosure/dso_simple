
#include "dpo.h"
#include "dso.h"
#include "wave.h"
#include "menu.h"
#include "thread.h"
#include "dso_unit.h"
#include "GUI.h"
#include <string.h>
#include <stdio.h>


const char **param_unit[4] = {
	param_unit_volt,
	param_unit_rate,
	param_unit_time,
	param_unit_freq,
};

/**************************************************************
 *
 *                       参数显示处理
 *                      [1/7/2012 lkh]
 */
/*参数初始化*/
void param_init(PROJECT_INFO *info) {

}
/*参数显示*/
void param_dislpay(MEASURE_INFO *info) {
	PROJECT_INFO *prj=info->parent->parent->parent->parent;
	//MEASVOLT_DATA *v=&info->param.i.v;
	infobar_dispParam(prj->infobar);
}
/*************************************************************
 *
 *                      参数单位处理
 *                    [1/25/2012 robot]
 */
void param_toStringWithUnit(char* dest,t_param *src,const char *unit[]) {
	I8 index;
	t_param tsrc=*src>=0.0?*src : -*src;
	if(unit[2]) {
		if(strcmp(unit[4]," ")) {  // 
			if(tsrc == 0.0) {
				index = 5; goto goto_end;
			} else if(tsrc < 1.0e-009) {
				tsrc = *src * 1.0e+012; index = 1; 
				goto goto_end;
			} else if(tsrc < 1.0e-006) {
				tsrc = *src * 1.0e+009; index = 2; 
				goto goto_end;
			} else if(tsrc < 1.0e-003) {
				tsrc = *src * 1.0e+006; index = 3; 
				goto goto_end;
			} else if(tsrc < 1.0e-000) {
				tsrc = *src * 1.0e+003; index = 4; 
				goto goto_end;
			} else if(tsrc < 1.0e+003) {
				index = 5; 
				goto goto_end;
			}
		} else {
			if(tsrc < 1.0e+003) {
				index = 5; 
				goto goto_end;
			}
		}
		if(1.0e+003<=tsrc && tsrc<1.0e+006) {
			tsrc = *src * 1.0e-003; index = 6;
		} else if(tsrc < 1.0e+009) {
			tsrc = *src * 1.0e-006; index = 7;	
		} else if(tsrc < 1.0e+012) {
			tsrc = *src * 1.0e-009; index = 8;
		} else {
			sprintf(dest,"%s","+INF");
			return ;
		}
	} else {
		index = 1;
	}
goto_end:
	if(strcmp(unit[index]," ")) {
		sprintf(dest,"%.*f%s",atoi(unit[0]),tsrc,unit[index]);
	} else {
		sprintf(dest,"%s","---");
	}
}

