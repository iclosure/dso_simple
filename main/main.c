/**
 *
 *
 */



#include "dso.h"
#include "global.h"
#include "thread.h"
#include <stdlib.h>


/*���������*/
int main(void) {

	dso_init(&prj_info);
	dso_start(&prj_info);
	
	return 0;
}


