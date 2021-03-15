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
    this->DrawCircle(this->torsoRadius, this->torsoColor);
    this->DrawStroke(this->torsoRadius, this->torsoStroke);
}
void Character::DrawNose()
{
    glPushMatrix();
    glTranslatef(0, this->torsoRadius, 0);
    
    glTranslatef(0, this->noseRadius, 0);
    this->DrawCircle(this->noseRadius, this->noseColor);
    this->DrawStroke(this->noseRadius, this->noseStroke);
    glPopMatrix();
}

void Character::DrawCharacter(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    
    glRotatef(this->gTheta, 0, 0, 1);
    
    this->DrawLeftArms(-this->torsoRadius, 0);
    this->DrawRightArms(this->torsoRadius, 0);
    
    /* Draw torso above arm*/
    this->DrawTorso();
    this->DrawNose();
    
    this->DrawCircleDashed(outsideRadius, Color(255, 255, 255));
    
    this->DrawCircle(5, Color(255,255,0));
    glPopMatrix();
}

void Character::MoveForward(GLfloat dx) {
    Point2D* charPosition = new Point2D(0, 0);
    moveForwareTransform(dx)->apply(charPosition);
    
    this->gX = charPosition->x;
    this->gY = charPosition->y;
}

void Character::RotateBody(GLfloat inc) {
    this->gTheta -= inc;
}
