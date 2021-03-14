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
#include "framework.h"
// Dimensions
#define paddleHeight 80
#define paddleWidth 10
#define baseHeight 40
#define baseWidth 100
#define radiusWheel 30

class Character {
    GLfloat gX;
    GLfloat gY;
    GLfloat gTheta1;
    GLfloat gTheta2;
    GLfloat gTheta3;
    GLfloat gThetaWheel;
    GLfloat direction;
private:
    void DrawRectangle(  GLint height, GLint width,
                    GLfloat R, GLfloat G, GLfloat B);
    void DrawCircle(  GLint radius, GLfloat R,
                    GLfloat G, GLfloat B);
    void DrawWheel(GLfloat x, GLfloat y, GLfloat thetaWheel,
                    GLfloat R, GLfloat G, GLfloat B);
    void DrawArms(   GLfloat x, GLfloat y, GLfloat theta1,
                    GLfloat theta2, GLfloat theta3);
    void DrawCharacter( GLfloat x, GLfloat y, GLfloat thetaWheel,
                    GLfloat theta1, GLfloat theta2, GLfloat theta3);

public:
    Character(){
        gX = 0;
        gY = -200;
        gTheta1 = 0;
        gTheta2 = 0;
        gTheta3 = 0;
        gThetaWheel = 0;
    };
    void Draw(){
        DrawCharacter(gX, gY, gThetaWheel, gTheta1,
                gTheta2, gTheta3);
    };
    void RotateArm1(GLfloat inc);
    void RotateArm2(GLfloat inc);
    void RotateArm3(GLfloat inc);
    void MoveInX(GLfloat dx);
    GLfloat GetX(){
        return gX;
    };
    GLfloat GetY(){
        return gY;
    };
};

#endif /* character_hpp */

