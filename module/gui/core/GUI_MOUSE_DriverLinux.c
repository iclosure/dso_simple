/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_MOUSE_DriverLinux.C
Purpose     : Touch screen manager
----------------------------------------------------------------------
This module handles the touch screen. It is configured in the file
GUITouch.conf.h (Should be located in the Config\ directory).
----------------------------------------------------------------------
*/
#if (!WIN32)
#include "GUIConf.h"
#if  GUI_LINUX    /* if it's Linux system */

#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Protected.h"
#include <stdlib.h>
#include <stdio.h>

/* for linux framebuffer */
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <pthread.h>
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static int  _ScreenX              = 0;    /* x-pos              */
static int  _ScreenY              = 0;    /* y-pos              */
static int  _NumBytesInBuffer     = 0;    /* bytes in rx buffer */
static U8   _Buttons              = 0;    /* button status      */
static U8   _abInBuffer[3];               /* mouse rx buffer    */

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _EvaPacket
*
* Purpose:
*   Process data packet from mouse:
*
*             | D7    D6    D5    D4    D3    D2    D1    D0
*   ----------+----------------------------------------------
*   1st byte  | --    --    Y-    X-     1    --    LB    RB
*   2nd byte  | X7    X6    X5    X4    X3    X2    X1    X0
*   3rd byte  | Y7    Y6    Y5    Y4    Y3    Y2    Y1    Y0
*/
static void _EvaPacket(void) {
  char a;
  GUI_PID_STATE State;
  _Buttons = _abInBuffer[0] & 0x03;
  a = _abInBuffer[1];
  /* test x move sign. */
  if(_abInBuffer[0] & 0x10) {
    a=-a;
    _ScreenX  -= a;
  }        /* direction is negative, move left */
  else {
    _ScreenX  += a;
  }
  a = _abInBuffer[2];
  /* test y move sign. */
  if(_abInBuffer[0] & 0x20) {
    a=-a;
    _ScreenY  += a;
  }  /* direction is negative, move down */ else {
    _ScreenY  -= a;
  }
  /* check min/max positions */    
  if (_ScreenX < 0) {
    _ScreenX = 0;
  } else if (_ScreenX > LCD_XSIZE-1) {
    _ScreenX = LCD_XSIZE-1;
  } if (_ScreenY < 0) {
    _ScreenY = 0;
  } else if (_ScreenY > LCD_YSIZE-1) {
    _ScreenY = LCD_YSIZE-1;
  }
  /* signal new mouse data */
  State.x       = _ScreenX;
  State.y       = _ScreenY;
  State.Pressed = _Buttons;
  GUI_MOUSE_StoreState(&State);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MOUSE_DRIVER_PS2_OnRx
*
* Purpose:
*   Mouse receive interrupt handler. The PS2 mouse interrupt gets
*   in three bytes from the mouse, then wakes up the mouse LSR.
*/
void GUI_MOUSE_DRIVER_PS2_OnRx(unsigned char Data) {
  if (!_NumBytesInBuffer) {
    /* check for start frame */
    if ((Data & 0x0c) == 0x08) {
      _abInBuffer[0] = Data;
      _NumBytesInBuffer++;
    }
  } else {
    _abInBuffer[_NumBytesInBuffer] = Data;
    _NumBytesInBuffer++;
    if (_NumBytesInBuffer >= 3) {
      _EvaPacket();
      _NumBytesInBuffer = 0;
    }
  }
}

void *ThreadReamMouse(void)
{
	int ret;
    int fd;
    fd_set readfs; 
    int maxfd = 0;
    
    fd = open ("/dev/input/mice",O_RDWR);  // USB->...mice; PS2->...mouse0
    if (fd < 0) 
    {
    	printf ("%s open failed\n", "/dev/input/mice");
        printf ("Error: opening %s. Check kernel config\n","/dev/input/mice");
        return NULL;
    }
    
    printf("open %s success, fd is %d\n", "/dev/input/mice", fd);
    maxfd = fd + 1;  
    for (; ;)
    {
    	FD_ZERO(&readfs); 
    	FD_SET(fd, &readfs); 
    	ret = select(maxfd, &readfs, NULL, NULL, NULL);
    	if (ret < 0)
    	{
    		printf("select failure!\n");
    		return NULL;
    	}

    	if (FD_ISSET(fd, &readfs))
    	{  
    		/* ¶ÁÈ¡Êó±ê */
    		_NumBytesInBuffer = read(fd, _abInBuffer, sizeof(_abInBuffer));
    		if ((_NumBytesInBuffer == 3) && ((_abInBuffer[0] & 0x0c) == 0x08))
    		{
    			_EvaPacket();
    			printf("Get mouse data!\n");
    		}
    	} 
    }
}

/*********************************************************************
*
*       GUI_MOUSE_DRIVER_PS2_Init
*/
void GUI_MOUSE_DRIVER_PS2_Init(void) {

	int i;
	
	printf("Start GUI_MOUSE_DRIVER_PS2_Init...\n");
	
	pthread_t pidReadMouse; 

	_NumBytesInBuffer = 0; 

	i = pthread_create(&pidReadMouse, NULL, (void *)ThreadReamMouse, (void*)3);
	if(!i)
		printf("Create thread sucess!\n");
	else
		printf("Create thread false!\n");
}

#endif

#else

#endif /* !WIN32 */

/*************************** End of file ****************************/
