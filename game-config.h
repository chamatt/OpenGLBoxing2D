#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifndef game_config_h
#define game_config_h

#include <stdio.h>
#include "framework.h"

class PlayerObject {
public:
    GLfloat headSize;
    Point2D position;
    GLfloat angle;
    
    PlayerObject(GLfloat _headSize, Point2D _position, GLfloat _angle): headSize(_headSize), position(_position), angle(_angle) {}
};

class GameInitObject {
public:
    Rectangle arena;
    
    GameInitObject(Rectangle _arena, PlayerObject _player1, PlayerObject _player2): arena(_arena), player1(_player1), player2(_player2) {}
  
    PlayerObject player1;
    PlayerObject player2;
};

#endif /* game_init_hpp */
