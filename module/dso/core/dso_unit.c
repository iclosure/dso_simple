
#include <string.h>

/**************************************************************
 *
 *                       ������λ�б�
 *                    [1/25/2012 robot]
 * ˵������һ��ΪС���㱣��λ��;���������ΪNULL���ʾ�����е�λת��;������Ϊ���õ�λ;
 */
const char *param_unit_volt[9] = {
	"2"," "," ","uV","mV","V","kV","��V"," ", /*[��ѹ]->[index:0],[base:V]*/
};
const char *param_unit_rate[3] = {
	"1","%",NULL, /*[�ٷֱ�]->[index:0],[base:%]*/
};
const char *param_unit_time[9] = {
	"2","fs","ns","us","ms","s","ks"," "," ", /*[ʱ��]->[index:1],[base:s]*/
};
const char *param_unit_freq[9] = {
	"4"," "," "," "," ","Hz","kHz","MHz","GHz", /*[Ƶ��]->[index:2],[base:Hz]*/
};
const char *param_unit_degree[3] = {
	"2","��",NULL, /*[��λ]->[index:2],[base:��]*/
};
const char *param_unit_none[3] = {
	"2"," ",NULL, /*[��Чȱʡ��λ]->[index:2],[base:--]*/
};


