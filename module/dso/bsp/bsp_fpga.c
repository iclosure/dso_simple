

#if (!WIN32)

#include "s3c6410_addr.h"
#include "bsp.h"

/*
void bsp_fpga_init(void)
{	
    bsp_SysBus_mmap();
	
    //����GPA15ΪnGCS4ΪƬѡ������GPA0ΪADDR0
    rGPACON |= (1 << 15) | (1 << 0); 
	
    //S3C2440_BWSCON
    rBWSCON = rBWSCON & ~(0x0A << 16) | (1 << 19);
    
    //S3C2440_BANKCON4
    rBANKCON4 = 0x7FFC;
}
*/
#else

void bsp_fpga_init(void) { }


#endif /*!WIN32*/