#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "character.h"
#include "framework.h"
#include "game-config.h"
#include "mouse.h"

#define INC_KEY 13
#define INC_KEYIDLE 2

#define PI 3.14

class Character;

class Game {
public:
    //Key status
    int keyStatus[256];

    Mouse mouse;
    
    Rectangle arena = Rectangle(0,0,0,0);
    
    Character* player1;
    Character* player2;
    
    GLdouble currentTime, timeDiference;

    GLfloat applyTimeFix(GLfloat amount) {
        return amount * (timeDiference/20);
    }

    void frameCorrectionFix() {
        static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        timeDiference = currentTime - previousTime;
        previousTime = currentTime;
    }
    
    Game();
    Game(string xmlPath);
    
    void initializeCharacters(GLfloat sizep1, GLfloat sizep2);
    
    int score = 0;
    char str[1000];
    void * font = GLUT_BITMAP_9_BY_15;
    void PrintScore()
    {
       GLfloat x = this->arena.x+20, y = this->arena.y+20;
       glColor3f(1.0, 1.0, 1.0);
       //Cria a string a ser impressa
       char *tmpStr;
       sprintf(this->str, "Score: %d", score);
       //Define a posicao onde vai comecar a imprimir
       glRasterPos2f(x, y);
       //Imprime um caractere por vez
       tmpStr = this->str;
       while( *tmpStr ){
           glutBitmapCharacter(this->font, *tmpStr);
           tmpStr++;
       }
    }
    
    
    void keyPress(unsigned char key, int x, int y);

    bool isKeyPressed(int key) {
        return keyStatus[key];
    }
    
    void setPlayerStartPosition(Character* pl, GLfloat x, GLfloat y, GLfloat angle);
    
    void mouseEvent(int button, int state, int x, int y)
    {
            y = 2*arena.y + arena.height - y;
            if (button == GLUT_LEFT_BUTTON)
            {
               if (state == GLUT_UP)
               {
                  mouse.leftButton.setIsPressed(false);
                  mouse.leftButton.setUnclickPosition(x,y);
//                  player1->mouseUnclick();
               }
               else if (state == GLUT_DOWN)
               {
                  mouse.leftButton.setIsPressed(true);
                  mouse.leftButton.setClickPosition(x,y);
               }
            }
            glutPostRedisplay();
    }
    
    void mouseMovement(int x, int y)
    {
       y = 2*arena.y + arena.height - y;
       mouse.setPosition(x, y);
       glutPostRedisplay();
    }
};

#endif /* Game_hpp */
