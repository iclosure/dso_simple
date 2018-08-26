
/******************************************************************
 * 
 *                   Ѱ��һ�����������е�����[��С�������������]
 */

#include "integer.h"

/********************************************************
*          Name : dsp_mostnum
*      Function : �����������в��ҳ��ִ�������Ԫ��, ������[��С�������������].
*        Inputs : data[] -- ������������;
*                 n      -- ������������ߴ�.
*                 mid    -- �������������е�������ֵ.
*                 *pLarge-- ; *pSmall-- 
*   Description : >*pSmall -- ��С����; *pLarge -- �������.
*                 >������data[]��, С�������ǵ���mid������, ���������Ǵ���mid������.
********************************************************/
void dsp_mostnum(I16 data[], int n, float mid,I16 *pLarge, I16 *pSmall)
{
    int i;
    int cnt, cnt1=1,cnt2=1;
    for(i=0; i<n-1; i++) {
        cnt= 1;
        while(data[i] == data[i+1]) {   // �ۼ���ͬԪ�ظ���.
            cnt++; i++;
        }
        
        if(cnt >= n-1) {   // ���������һ��Ԫ����ǰ����������ȫ��ͬ, ��ô�ڵ��÷���֮ǰ��Ҫ�����һ��ֵ���� p[1].
            *pSmall= data[0];
            *pLarge= data[n-1];
            return ;
        } else if((i == n-2) && (cnt2 == 1)) {
            *pLarge= data[n-1];
            return;
        }
        
        if(data[i] <= mid) {  // Ѱ��С����ֵ������.
            if((cnt1 == 1) && (cnt == cnt1)) { // ���������С����, ��ȡ��Сֵ��Ϊ��ֵ.
                *pSmall= data[0];
            } else if(cnt > cnt1) {            // ȡ���ɵ�����.
                cnt1= cnt; *pSmall= data[i];
            }
        } else {     // Ѱ�Ҵ�����ֵ������.
            if((cnt2 == 1) && (cnt == cnt2)) {  // ��������ڴ�����, ��ȡ��Сֵ��Ϊ��ֵ.
                *pLarge= data[n-1];
            } else if(cnt > cnt2) {     // ȡ���ɵ�����.
                cnt2= cnt; *pLarge= data[i];
            }
        }
    }
}