#ifndef KEY_H_
#define KEY_H_

#include "dso_type.h"

/*******************************************************************
 *
 *                   按键处理函数
 */
void key_getDecode	(KEY_INFO *info);
void key_up			(MENUPAGE_INFO *info);
void key_down		(MENUPAGE_INFO *info);
void key_back		(MENUPAGE_INFO *info);
I8 menu_isValidId	(MENUPAGE_INFO info,I8 id);
void key_response	(KEY_INFO *info);



#endif /*KEY_H_*/
