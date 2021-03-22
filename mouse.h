#ifndef mouse_hpp
#define mouse_hpp

#include "framework.h"

enum MouseButton
{
   LEFT_MOUSE_BUTTON = 0,
   RIGHT_MOUSE_BUTTON = 1,
};

class MouseStatus
{
public:
    bool isPressed = false;
    Point2D clickPosition = Point2D(0, 0);
    Point2D unclickPosition = Point2D(0, 0);

    MouseStatus() {}

    void setIsPressed(bool pressed)
    {
      this->isPressed = pressed;
    }
    void setClickPosition(float x, float y)
    {
        this->clickPosition.x = x;
        this->clickPosition.y = y;
    }
    void setUnclickPosition(float x, float y)
    {
        this->unclickPosition.x = x;
        this->unclickPosition.y = y;
    }
};

class Mouse
{
public:
    MouseStatus leftButton;
    Point2D currentPosition = Point2D(0, 0);

    Mouse() {}

    Mouse(float x, float y)
    {
        this->currentPosition.x = x;
        this->currentPosition.y = y;
    }

    void setPosition(float x, float y)
    {
        this->currentPosition.x = x;
        this->currentPosition.y = y;
    }
};



#endif /* mouse_hpp */
