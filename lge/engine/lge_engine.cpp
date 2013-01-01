
#include "lge_platform.h"

#ifdef WIN32
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#endif

#include "lge_engine.h"

bool lge_init_graphic(HWND hWnd, int width, int height)
{
	return true;
}

bool lge_init_sound()
{
	return true;
}