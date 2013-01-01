#pragma once
#include "lge_singleton.h"

extern bool lge_init_graphic(HWND hWnd, int width, int height);
extern bool lge_init_sound();

class LEngine : public MySingleton<LEngine>
{
};