#pragma once

NAMESPACE_BEGIN

class Renderer
{
public:
    virtual void beginScene() = 0;
    virtual void endScene() = 0;
	virtual void flip() = 0;
    virtual void clear() = 0;
};

NAMESPACE_END
