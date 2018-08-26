
#include <string.h>

/**************************************************************
 *
 *                       参数单位列表
 *                    [1/25/2012 robot]
 * 说明：第一列为小数点保留位数;第三列如果为NULL则表示不进行单位转换;第六列为常用单位;
 */
const char *param_unit_volt[9] = {
	"2"," "," ","uV","mV","V","kV","ΩV"," ", /*[电压]->[index:0],[base:V]*/
};
const char *param_unit_rate[3] = {
	"1","%",NULL, /*[百分比]->[index:0],[base:%]*/
};
const char *param_unit_time[9] = {
	"2","fs","ns","us","ms","s","ks"," "," ", /*[时间]->[index:1],[base:s]*/
};
const char *param_unit_freq[9] = {
	"4"," "," "," "," ","Hz","kHz","MHz","GHz", /*[频率]->[index:2],[base:Hz]*/
};
const char *param_unit_degree[3] = {
	"2","°",NULL, /*[相位]->[index:2],[base:°]*/
};
const char *param_unit_none[3] = {
	"2"," ",NULL, /*[无效缺省单位]->[index:2],[base:--]*/
};


