#ifndef mouse_hpp
#define mouse_hpp

enum MouseButton
{
   LEFT_MOUSE_BUTTON = 0,
   RIGHT_MOUSE_BUTTON = 1,
};

class MouseStatus
{
public:
   bool isPressed = false;

   MouseStatus() {}

   void setIsPressed(bool pressed)
   {
      this->isPressed = pressed;
   }
};

class Mouse
{
public:
   MouseStatus leftButton;
   float x = 0;
   float y = 0;

   Mouse() {}

   Mouse(float x, float y)
   {
      this->x = x;
      this->y = y;
   }

   void setPosition(float x, float y)
   {
      this->x = x;
      this->y = y;
   }
    
//    void mouseEvent(int button, int state, int x, int y)
//    {
//       y = -y + TAMANHO_JANELA;
//       if (button == GLUT_LEFT_BUTTON)
//       {
//          if (state == GLUT_UP)
//          {
//             mouse.leftButton.setIsPressed(false);
//             mainSquare.setIsDragging(false);
//          }
//          else if (state == GLUT_DOWN)
//          {
//             mouse.leftButton.setIsPressed(true);
//             if (mainSquare.isWithin(mouse.x, mouse.y))
//             {
//                mainSquare.setIsDragging(true);
//                mainSquare.setAnchor(mouse.x, mouse.y);
//             }
//             else
//             {
//                mainSquare.setIsDragging(false);
//             }
//          }
//       }
//       glutPostRedisplay();
//    }
//
//    void mouseMovement(int x, int y)
//    {
//       y = -y + TAMANHO_JANELA;
//       mouse.setPosition((float)x / TAMANHO_JANELA, (float)y / TAMANHO_JANELA);
//       glutPostRedisplay();
//    }
};



#endif /* mouse_hpp */
