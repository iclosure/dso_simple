
#include <stdio.h>
#include <string.h>

#if (!WIN32)

#include "s3c6410_addr.h"
#include "bsp.h"


unsigned char * p_memctl_base_addr;    /* Memory control �������ַ */
unsigned char * p_gpio_base_addr;      /* ϵͳ����(System Peripherals))�������ַ */

/*
// ӳ��ϵͳ���߼Ĵ�������linux������SRAM��
int bsp_sysbus_mmap(void) {	
	bsp_mmap(&p_memctl_base_addr, MEMCTL_BASE_ADDR, MEMCTL_SIZE);
	bsp_mmap(&p_gpio_base_addr,   GPIO_BASE_ADDR,   GPIO_SIZE);

	return 0;
}

// ��linux������SRAM��ɾ��ϵͳ���߼Ĵ�����ַ�����ӳ��
int bsp_sysbus_munmap(void) {			
	bsp_munmap(MEMCTL_SIZE);
	bsp_munmap(GPIO_SIZE);

	return 0;
}
*/
#else

int bsp_sysbus_mmap(void) { return -1; }
int bsp_sysbus_munmap(void) { return -1; }



#endif /*!WIN32*/

