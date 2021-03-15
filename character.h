#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifndef character_hpp
#define character_hpp
#include "game.h"
#include "framework.h"
// Dimensions
#define firstPaddleHeight 50
#define secondPaddleHeight 40
#define paddleWidth 10
#define baseHeight 40
#define baseWidth 100
#define radiusWheel 30

class Game;

class Character {
    Game* gameObject;
    
    Color torsoColor;
    Color torsoStroke;
    Color noseColor;
    Color noseStroke;
    Color armsColor;
    Color handColor;
    Color handStroke;
    
    GLfloat torsoRadius;
    GLfloat handRadius;
    GLfloat noseRadius;
    GLfloat outsideRadius;
    
    GLfloat leftArmFirstJointAngle = 120;
    GLfloat leftArmSecondJointAngle = -120;
    GLfloat rightArmFirstJointAngle = -120;
    GLfloat rightArmSecondJointAngle = 120;
    
    GLfloat gX;
    GLfloat gY;
    GLfloat gTheta;
    GLfloat direction;
private:
    void DrawRectangle(GLint height, GLint width, Color color);
    void DrawCircle(GLint radius, Color color);
    void DrawStroke(GLint radius, Color color);
    void DrawCircleDashed(GLint radius, Color color);
    void DrawWheel(GLfloat x, GLfloat y, GLfloat thetaWheel, Color color);
    void DrawArms(GLfloat x, GLfloat y, GLfloat theta1,
                    GLfloat theta2, GLfloat theta3);
    void DrawLeftArms(GLfloat x, GLfloat y);
    void DrawRightArms(GLfloat x, GLfloat y);
    void DrawTorso();
    void DrawNose();
    void DrawHand();
    void DrawCharacter(GLfloat x, GLfloat y);
    
    Transformation* moveForwardTransform(GLfloat dx) {
        Transformation* tr = new Transformation();
        tr->translate2d(gX, gY);
        tr->rotate2d(gTheta);
        tr->translate2d(0, dx);
        return tr;
    }

public:
    Character(Game* game, GLfloat size);
    
    void setInitialPos(GLfloat x, GLfloat y, GLfloat angle) {
        this->gX = x;
        this->gY = y;
        this->gTheta = angle;
    }
    
    bool willColideWithGameWalls(GLfloat dx);
    
    bool willColideWithOtherPlayer(Character* another, GLfloat dx);
    
    bool willColide(Game* game, GLfloat dx);
    
    void Draw(){
        DrawCharacter(gX, gY);
    };
    void RotateLeftArm(GLfloat inc);
    void RotateRightArm(GLfloat inc);
    void RotateBody(GLfloat inc);
    void MoveForward(Game* game, GLfloat dx);
    GLfloat GetX(){
        return gX;
    };
    GLfloat GetY(){
        return gY;
    };
};

#endif /* character_hpp */

