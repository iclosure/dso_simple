#ifndef BSP_H_
#define BSP_H_

#include "GUIType.h"
#include <stdlib.h>


/**************************************************************
 *
 *              BSP: 硬件层基本函数
 */

int bsp_open  (void);
int bsp_close (void);
int bsp_mmap  (unsigned char ** pp_reg_base_addr, unsigned int reg_base_addr, size_t length);
int bsp_munmap(size_t length);

/**************************************************************
 *
 *              BSP: 硬件层的 FPGA驱动
 */
#define FPGA_Init()     bsp_fpga_init()
// s3c2440 使用nGCS4
#define FPGA_MEMORY_BASE  (0x20000000)

#define IDE_ReadByte(addr, x)   x = *(volatile U8 *)(FPGA_MEMORY_BASE + addr)
#define IDE_WriteByte(addr, x)  *(volatile U8 *)(FPGA_MEMORY_BASE + addr) = x

#define IDE_ReadWord(addr, x)   x = *(volatile U16 *)(FPGA_MEMORY_BASE + addr)
#define IDE_WriteWord(addr, x)  *(volatile U16 *)(FPGA_MEMORY_BASE + addr) = x


void bsp_fpga_init(void);

/**************************************************************
 *
 *              BSP: 硬件层的 LCD驱动
 */
int  LCDDEV_Init (void);
void lcd_displayRect(LCD_RECT rect,int x0,int y0);
void lcd_display (void);

/**************************************************************
 *
 *              BSP: 硬件层的 系统总线驱动
 */
#define sysBus_mmap()     bsp_sysbus_mmap()
#define sysBus_munmap()   bsp_sysbus_munmap()

int bsp_sysbus_mmap  (void);
int bsp_sysbus_munmap(void);

/**************************************************************
 *
 *              BSP: 硬件层的 UART驱动
 */

#define Uart_Init()           bsp_uart_init()
#define Uart_SendByte(data)   bsp_uart_sendbyte(data)
#define Uart_SendString(pt)   bsp_uart_sendstring(pt)
#define Uart_Print(pt)        bsp_uart_print(pt)

void bsp_uart_init      (void);
void bsp_uart_sendbyte  (int data);
void bsp_uart_sendstring(char *pt);
void bsp_uart_print     (char *pt);

/**************************************************************
 *
 *              BSP: 硬件层的 xxx
 */




#endif /*BSP_H_*/
