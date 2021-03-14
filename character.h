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
#define firstPaddleHeight 50
#define secondPaddleHeight 40
#define paddleWidth 10
#define baseHeight 40
#define baseWidth 100
#define radiusWheel 30

#define torsoRadius 20
#define handRadius 15
#define noseRadius 5

#define outsideRadius 102

class Character {
    Color torsoColor;
    Color torsoStroke;
    Color noseColor;
    Color noseStroke;
    Color armsColor;
    Color handColor;
    Color handStroke;
    
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

public:
    Character(){
        gX = 0;
        gY = -200;
        gTheta = 0;
        
        torsoColor = Color(90, 128, 184);
        torsoStroke = Color(64, 92, 134);
        noseColor = Color(90, 128, 184);
        noseStroke = Color(64, 92, 134);
        armsColor = Color(161, 186, 102);
        handColor = Color(179, 87, 81);
        handStroke = Color(130, 61, 57);
    };
    void Draw(){
        DrawCharacter(gX, gY);
    };
    void RotateLeftArm(GLfloat inc);
    void RotateRightArm(GLfloat inc);
    void RotateBody(GLfloat inc);
    void MoveForward(GLfloat dx);
    GLfloat GetX(){
        return gX;
    };
    GLfloat GetY(){
        return gY;
    };
};

#endif /* character_hpp */

