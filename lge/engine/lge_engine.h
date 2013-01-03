#pragma once
#include "lge_singleton.h"

NAMESPACE_BEGIN
class Renderer;

class Engine : public MySingleton<Engine>
{
public:
    Engine();
    ~Engine();
    
    bool initGraphic(HWND hWnd);
    bool initSound();
    
    void beginScene();
    void endScene();
    void flip();
    void clear();
private:
    Renderer* m_renderer;
};

NAMESPACE_END