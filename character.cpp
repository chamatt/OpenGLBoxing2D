#include <math.h>
#include <iostream>
#include <vector>
#include "character.h"
#include "framework.h"
#define PI 3.14

using namespace std;

void Character::DrawRectangle(GLint height, GLint width, Color color)
{
    GLint x1 = -width/2, x2 = width/2;
    GLint y1 = 0, y2 = height;
    glBegin(GL_POLYGON);
        glColor3f(color.R, color.G, color.B);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void Character::DrawCircle(GLint radius, Color color)
{
    float theta;
    float step = 20.0;
    glColor3f(color.R, color.G, color.B);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360/step; i++) {
            theta = i*step*3.14/180;
            glVertex2f(radius*cos(theta), radius*sin(theta));
        }
    glEnd();
}

void Character::DrawStroke(GLint radius, Color color)
{
    float theta;
    float step = 20.0;
    glColor3f(color.R, color.G, color.B);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 360/1; i++) {
            theta = i*1*3.14/180;
            glVertex2f(radius*cos(theta), radius*sin(theta));
        }
    glEnd();
}

void Character::DrawCircleDashed(GLint radius, Color color)
{
    glPointSize(2);
    float theta;
    glColor3f(color.R, color.G, color.B);
    glBegin(GL_POINTS);
        for(int i = 0; i < 360/10; i++) {
            theta = i*10*3.14/180;
            glVertex2f(radius*cos(theta), radius*sin(theta));
        }
    glEnd();
}

//void Character::DrawArms(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
//{
//    glPushMatrix();
//   
//    glTranslatef(x, y, 0); /* Move to first paddle base */
//    glRotatef(theta1, 0, 0, 1);
//    this->DrawRectangle(paddleHeight, paddleWidth, Color(0, 0, 1));
//    
//    glTranslatef(0, paddleHeight, 0);  /* Move to second paddle base */
//    glRotatef(theta2, 0, 0, 1);
//    this->DrawRectangle(paddleHeight, paddleWidth, Color(1, 1, 0));
//    
//    glTranslatef(0, paddleHeight, 0);  /* Move to third paddle base */
//    glRotatef(theta3, 0, 0, 1);
//    this->DrawRectangle(paddleHeight, paddleWidth, Color(0, 1, 0));
//    
//    glPopMatrix();
//}

void Character::DrawLeftArms(GLfloat x, GLfloat y)
{
    glPushMatrix();
    
    glTranslatef(x, y, 0); /* Move to left arm base */
    glRotatef(this->leftArmFirstJointAngle, 0, 0, 1);
    this->DrawCircle(5, this->armsColor); /* Smooth joint */
    this->DrawRectangle(firstPaddleHeight, paddleWidth, this->armsColor);
    
    glTranslatef(0, firstPaddleHeight, 0);  /* Move to second left arm joint */
    glRotatef(this->leftArmSecondJointAngle, 0, 0, 1);
    this->DrawCircle(5, this->armsColor); /* Smooth joint */
    this->DrawRectangle(secondPaddleHeight, paddleWidth, this->armsColor);
    
    glTranslatef(0, secondPaddleHeight, 0);  /* Move to second right arm tip */
    glTranslatef(0, handRadius, 0);
    this->DrawHand();
    
    glPopMatrix();
}

void Character::DrawRightArms(GLfloat x, GLfloat y)
{
    glPushMatrix();
    
    glTranslatef(x, y, 0); /* Move to right arm base */
    glRotatef(this->rightArmFirstJointAngle, 0, 0, 1);
    this->DrawCircle(5, this->armsColor); /* Smooth joint */
    this->DrawRectangle(firstPaddleHeight, paddleWidth, this->armsColor);
    
    glTranslatef(0, firstPaddleHeight, 0);  /* Move to second right arm joint */
    glRotatef(this->rightArmSecondJointAngle, 0, 0, 1);
    this->DrawCircle(5, this->armsColor); /* Smooth joint */
    this->DrawRectangle(secondPaddleHeight, paddleWidth, this->armsColor);
    
    glTranslatef(0, secondPaddleHeight, 0);  /* Move to second right arm tip */
    glTranslatef(0, handRadius, 0);
    this->DrawHand();
    
    glPopMatrix();
}

void Character::RotateLeftArm(GLfloat inc)
{
    this->leftArmFirstJointAngle += inc;
    this->leftArmSecondJointAngle -= inc/1.7;
}

void Character::RotateRightArm(GLfloat inc)
{
    this->rightArmFirstJointAngle -= inc;
    this->rightArmSecondJointAngle += inc/1.7;
}

void Character::DrawHand()
{
    this->DrawCircle(handRadius, this->handColor);
    this->DrawStroke(handRadius, this->handStroke);
}

void Character::DrawTorso()
{
    this->DrawCircle(torsoRadius, this->torsoColor);
    this->DrawStroke(torsoRadius, this->torsoStroke);
}
void Character::DrawNose()
{
    glPushMatrix();
    glTranslatef(0, torsoRadius, 0);
    
    glTranslatef(0, noseRadius, 0);
    this->DrawCircle(noseRadius, this->noseColor);
    this->DrawStroke(noseRadius, this->noseStroke);
    glPopMatrix();
}

void Character::DrawCharacter(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    
    this->DrawLeftArms(-torsoRadius, 0);
    this->DrawRightArms(torsoRadius, 0);
    
    
    /* Draw torso above arm*/
    this->DrawTorso();
    this->DrawNose();
    
    this->DrawCircleDashed(outsideRadius, Color(255, 255, 255));
    
//    this->DrawRectangle(baseHeight, baseWidth, 1, 0, 0);
//    this->DrawArms(0, baseHeight, theta1, theta2, theta3);
    
//    this->DrawWheel(-baseWidth/2, 0, thetaWheel, 1, 1, 1);
//    this->DrawWheel(baseWidth/2, 0, thetaWheel, 1, 1, 1);
    
    glPopMatrix();
}

void Character::RotateArm1(GLfloat inc)
{
    this->gTheta1 += inc;
}

void Character::RotateArm2(GLfloat inc)
{
    this->gTheta2 += inc;
}

void Character::RotateArm3(GLfloat inc)
{
    this->gTheta3 += inc;
}

void Character::MoveInX(GLfloat dx)
{
    this->gX += dx;
    
    float deltaTheta = - 2 * PI * radiusWheel * dx / 360;
    
    this->gThetaWheel += deltaTheta;
    
    cout << "move: " << dx << endl;
}

//Tiro* Character::Atira()
//{
//    Point2D* base = new Point2D(0, 0);
//    Point2D* tip = new Point2D(0, 0);
//
//    Transformation* tr = new Transformation();
//    tr->logMode(true);
//    tr->translate2d(gX, gY);
//    tr->translate2d(0, baseHeight); /* Move to first paddle base */
//    tr->rotate2d(gTheta1);
//    tr->translate2d(0, paddleHeight); /* Move to second paddle base */
//    tr->rotate2d(gTheta2);
//    tr->translate2d(0, paddleHeight);/* Move to third paddle base */
//    tr->apply(base);
//
//    tr->rotate2d(gTheta3);
//    tr->translate2d(0, paddleHeight); /* Move to third paddle tip */
//    tr->apply(tip);
//
//    GLfloat angle = atan2(tip->y - base->y, tip->x - base->x);
//    GLfloat rad = (angle*180)/PI;
//
//    cout << tip->y - base->y << "," << tip->x - base->x << ": " << rad << endl;
//
//    return new Tiro(tip->x, tip->y, rad);
//}
