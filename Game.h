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

#define INC_KEY 13
#define INC_KEYIDLE 2

#define PI 3.14

class Game {
public:
    //Key status
    int keyStatus[256];

    // Window dimensions
    const GLint Width = 700;
    const GLint Height = 700;

    // Viewing dimensions
    const GLint ViewingWidth = 500;
    const GLint ViewingHeight = 500;
    
    Character player1 = Character(20);
    Character player2 = Character(20);
    
    
    Game() { }
    
    int score = 0;
    char str[1000];
    void * font = GLUT_BITMAP_9_BY_15;
    void PrintScore()
    {
       GLfloat x = -this->ViewingWidth/2 + 20, y = -this->ViewingHeight/2 + 20;
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
    
    
    void keyPress(unsigned char key, int x, int y)
    {
        switch (key)
        {
//            case '1':
//                 animate = !animate;
//                 break;
            case 'a':
            case 'A':
                 keyStatus[(int)('a')] = 1; //Using keyStatus trick
                 break;
            case 'd':
            case 'D':
                 keyStatus[(int)('d')] = 1; //Using keyStatus trick
                 break;
            case 'w':
            case 'W':
                 keyStatus[(int)('w')] = 1; //Using keyStatus trick
                 break;
            case 's':
            case 'S':
                 keyStatus[(int)('s')] = 1; //Using keyStatus trick
                 break;
            case 'f':
            case 'F':
                 player1.RotateLeftArm(+INC_KEY);
                 break;
            case 'r':
            case 'R':
                 player1.RotateLeftArm(-INC_KEY);
                 break;
            case 'g':
            case 'G':
                 player1.RotateRightArm(+INC_KEY);
                 break;
            case 't':
            case 'T':
                 player1.RotateRightArm(-INC_KEY);
                 break;
            case 27 :
                 exit(0);
        }
        glutPostRedisplay();
    }

    bool isKeyPressed(int key) {
        return keyStatus[key];
    }
    
    void setPlayerStartPosition(Character &pl, GLfloat x, GLfloat y, GLfloat angle) {
        pl.setInitialPos(x, y, angle);
    }
};

#endif /* Game_hpp */
