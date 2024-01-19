#pragma once

#include "../Impl/UI/Menu/AMenuComponent.h"

template<class T, class U>
concept Derived = std::is_base_of_v<U, T>;

class IDrawable
{
public:
    virtual void draw() = 0;
    virtual void on_wnd_proc() = 0;
    virtual float width() = 0;
};

template <Derived<AMenuComponent> T>
class ADrawable : public IDrawable
{
protected:
    T* component;

public:
    ADrawable(T* component) : component(component) { }
};
