
#include <stdio.h>
#include <stdlib.h>

#if (!WIN32)

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

static int fdmem = -1 ;      /* �ڴ��豸�������ö˿�Ӳ����ַ�������ַʱ�õ� */


// �� ��д��ʽ ���ڴ�ӳ���ַ��豸�ļ� /dev/mem
int bsp_open(void)
{
	fdmem = open("/dev/mem", O_RDWR | O_SYNC);
	if(fdmem < 0) {
		printf("Can't open mem device entry.Error number:%d\n", fdmem);
		return -1;
	}
	return 0;
}

// �رմ򿪵��ڴ�ӳ���豸�ļ�
int bsp_close(void)
{
	close(fdmem);
	return 0;
}

// ӳ��ָ���ļĴ�������linux������SRAM��
int bsp_mmap(unsigned char ** pp_reg_base_addr, unsigned int reg_base_addr, size_t length)
{	
	*pp_reg_base_addr = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fdmem, reg_base_addr);
	
	if(*pp_reg_base_addr == MAP_FAILED) {
		printf("\n Map failed!\n");
		return -1;
	}
	return 0;
}

// ɾ���ض���ַ����Ķ���ӳ��
int bsp_munmap(size_t length)
{
	munmap(NULL, length);
	return 0;
}

#else

int bsp_open(void) { return -1; };
int bsp_close(void) { return -1; };
int bsp_mmap(unsigned char ** pp_reg_base_addr, unsigned int reg_base_addr, size_t length) { return -1; }
int bsp_munmap(size_t length) { return -1; }


#endif /*!WIN32*/
