
/******************************************************************
 * 
 *                   寻找一个升序数组中的众数[最小众数和最大众数]
 */

#include "integer.h"

/********************************************************
*          Name : dsp_mostnum
*      Function : 在升序数组中查找出现次数最多的元素, 即众数[最小众数和最大众数].
*        Inputs : data[] -- 待处理数据组;
*                 n      -- 待处理数据组尺寸.
*                 mid    -- 待处理数据组中的数据中值.
*                 *pLarge-- ; *pSmall-- 
*   Description : >*pSmall -- 存小众数; *pLarge -- 存大众数.
*                 >在数组data[]中, 小众数就是低于mid的众数, 大众数就是大于mid的众数.
********************************************************/
void dsp_mostnum(I16 data[], int n, float mid,I16 *pLarge, I16 *pSmall)
{
    int i;
    int cnt, cnt1=1,cnt2=1;
    for(i=0; i<n-1; i++) {
        cnt= 1;
        while(data[i] == data[i+1]) {   // 累计相同元素个数.
            cnt++; i++;
        }
        
        if(cnt >= n-1) {   // 如果倒数第一个元素以前的所有数据全相同, 那么在调用返回之前就要将最后一个值赋给 p[1].
            *pSmall= data[0];
            *pLarge= data[n-1];
            return ;
        } else if((i == n-2) && (cnt2 == 1)) {
            *pLarge= data[n-1];
            return;
        }
        
        if(data[i] <= mid) {  // 寻找小于中值的众数.
            if((cnt1 == 1) && (cnt == cnt1)) { // 如果不存在小众数, 就取最小值作为低值.
                *pSmall= data[0];
            } else if(cnt > cnt1) {            // 取代旧的众数.
                cnt1= cnt; *pSmall= data[i];
            }
        } else {     // 寻找大于中值的众数.
            if((cnt2 == 1) && (cnt == cnt2)) {  // 如果不存在大众数, 就取最小值作为低值.
                *pLarge= data[n-1];
            } else if(cnt > cnt2) {     // 取代旧的众数.
                cnt2= cnt; *pLarge= data[i];
            }
        }
    }
}