

#include "header.h"
#include "Core.h"
#include <stdio.h>

#ifdef PSP

#include <pspkernel.h>
#include <pspdebug.h>


/* Define the module info section */
PSP_MODULE_INFO("GETREKT", 0, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_MAX();
/* Define printf, just to make typing easier */
//#define printf	pspDebugScreenPrintf
#endif

int main(int argc, char *argv[])
{
//	pspDebugScreenInit();
//	PRINT("2Starting MainLoop\n");
//	sceIoWrite(1, "sceIoWrite stderr\n", strlen("sceIoWrite stderr\n"));
	printf("Testings for science\n");

	//vprintf("Trololol %i\n",NULL);
	CCore oCore;

	oCore.mainLoop();

	return 0;
}
