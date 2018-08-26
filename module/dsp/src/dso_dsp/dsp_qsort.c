
#include "integer.h"


// 可变类型的比较函数(升序排序)
int dsp_compareup(const void *_key , const void *_base)
{
    return *(I16 *)_key - *(I16 *)_base;
}
// 可变类型的比较函数(降序排序)
int dsp_comparedown(const void *_key , const void *_base)
{
    return *(I16 *)_base - *(I16 *)_key;
}

// Shell sort [希尔排序] 
void shellsort(int v[], int n) {
	int gap, i,j,temp;
	for(gap=n/2; gap>0; gap/=2) {
		for(i = gap;i<n;i++) {
			for(j = i-gap;j>=0&&v[j]>v[j+gap];j-=gap) {
				temp = v[j]; 
				v[j] = v[j+gap]; 
				v[j+gap] = temp;
			}
		}
	}
}

