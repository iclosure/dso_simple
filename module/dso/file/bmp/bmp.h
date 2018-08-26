#ifndef BITMAP_H_
#define BITMAP_H_

#include "bmp_type.h"
#include "dso_type.h"

/**********************************************************
 *
 *                    defined
 */

#define BI_RGB		    0L
#define BI_RLE8		    1L
#define BI_RLE4		    2L
#define BI_BITFIELDS	3L

#define WIDTHBYTES(i)    ((i+31)/32 * 4)

/**********************************************************
 *
 *                    Éú³ÉÒ»·ùBMPÍ¼
 */
void bmp_to24bpp(PROJECT_INFO *info,const char *file);




#endif /*BITMAP_H_*/
