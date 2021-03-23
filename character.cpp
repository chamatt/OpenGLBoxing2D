#include <math.h>
#include <iostream>
#include <vector>
#include "character.h"
#include "framework.h"
#include "game.h"
#define PI 3.14

using namespace std;


Character::Character(Game* game, GLfloat size){
    this->gameObject = game;
    
    gX = 0;
    gY = -200;
    gTheta = 0;
    
    handColor = defaultColors.handColor;
    handStroke = defaultColors.handStroke;
    
    this->torsoRadius = size;
    this->handRadius = (3.0/4.0) * size;
    this->noseRadius = size / 4;
    this->outsideRadius = size * 4.0;
    
    this->armLength = size*1.5;
    this->foreArmLength = size*1.75;
    this->armWidth = size/3;
};

Character::Character(Game* game, GLfloat size, Point2D position, GLfloat angle){
    this->gameObject = game;
    
    armsColor = defaultColors.armsColor;
    handColor = defaultColors.handColor;
    handStroke = defaultColors.handStroke;
    
    this->torsoRadius = size;
    this->handRadius = (3.0/4.0) * size;
    this->noseRadius = size / 4;
    this->outsideRadius = size * 3.0;
    
    this->armLength = size*1.5;
    this->foreArmLength = size*1.75;
    this->armWidth = size/3;
    
    this->gX = position.x;
    this->gY = position.y;
    this->gTheta = angle;
};

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
    this->DrawCircle(this->armWidth/2, this->armsColor); /* Smooth joint */
    this->DrawRectangle(this->armLength, this->armWidth, this->armsColor);
    
    glTranslatef(0, this->armLength, 0);  /* Move to second left arm joint */
    glRotatef(this->leftArmSecondJointAngle, 0, 0, 1);
    this->DrawCircle(this->armWidth/2, this->armsColor); /* Smooth joint */
    this->DrawRectangle(this->foreArmLength, this->armWidth, this->armsColor);
    
    glTranslatef(0, this->foreArmLength, 0);  /* Move to second right arm tip */
    glTranslatef(0, handRadius, 0);
    this->DrawHand();
    
    glPopMatrix();
}

void Character::DrawRightArms(GLfloat x, GLfloat y)
{
    glPushMatrix();
    
    glTranslatef(x, y, 0); /* Move to right arm base */
    glRotatef(this->rightArmFirstJointAngle, 0, 0, 1);
    this->DrawCircle(this->armWidth/2, this->armsColor); /* Smooth joint */
    this->DrawRectangle(this->armLength, this->armWidth, this->armsColor);
    
    glTranslatef(0, this->armLength, 0);  /* Move to second right arm joint */
    glRotatef(this->rightArmSecondJointAngle, 0, 0, 1);
    this->DrawCircle(this->armWidth/2, this->armsColor); /* Smooth joint */
    this->DrawRectangle(this->foreArmLength, this->armWidth,  this->armsColor);
    
    glTranslatef(0, this->foreArmLength, 0);  /* Move to second right arm tip */
    glTranslatef(0, handRadius, 0);
    this->DrawHand();
    
    glPopMatrix();
}

bool Character::RotateLeftArm(GLfloat inc, bool applyFix)
{
    if(!characterIsEnabled) return false;
    
    if(applyFix)
        inc = this->gameObject->applyTimeFix(inc);
    
    if(this->leftArmFirstJointAngle >= MIN_LEFT_ANGLE && inc > 0) {
        this->nextNPCState(CharacterPunchSignal::MIN_REACHED);
        return false;
    }
    else if(this->leftArmFirstJointAngle <= MAX_LEFT_ANGLE && inc < 0) {
        this->nextNPCState(CharacterPunchSignal::MAX_REACHED);
        return false;
    }
    
    this->leftArmFirstJointAngle += inc;
    this->leftArmSecondJointAngle -= inc*0.80;
    return true;
}

bool Character::RotateRightArm(GLfloat inc, bool applyFix)
{
    if(!characterIsEnabled) return false;
    
    if(applyFix)
        inc = this->gameObject->applyTimeFix(inc);
    
    if(this->rightArmFirstJointAngle <= MIN_RIGHT_ANGLE && inc > 0) {
        this->nextNPCState(CharacterPunchSignal::MIN_REACHED);
        return false;
    }
    else if(this->rightArmFirstJointAngle >= MAX_RIGHT_ANGLE && inc < 0) {
        this->nextNPCState(CharacterPunchSignal::MAX_REACHED);
        return false;
    }
    
    this->rightArmFirstJointAngle -= inc;
    this->rightArmSecondJointAngle += inc*0.80;
    return true;
}

void Character::RotateLeftArmToAngle(GLfloat angle)
{
    this->leftArmFirstJointAngle = angle;
    this->leftArmSecondJointAngle = -MIN_ANGLE - (angle - MIN_ANGLE)*0.80;
}
void Character::RotateRightArmToAngle(GLfloat angle)
{
    this->rightArmFirstJointAngle = angle;
    this->rightArmSecondJointAngle = MIN_ANGLE - (angle+MIN_ANGLE)*0.80;
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
    
    if(showOutsideRadius){
        this->DrawCircleDashed(outsideRadius, Color(255, 255, 255));
    }
    
    glPopMatrix();
}

void Character::MoveForward(GLfloat dx, bool applyFix)
{
    if(applyFix)
        dx = this->gameObject->applyTimeFix(dx);
    
    Point2D* charPosition = new Point2D(0, 0);
    
    this->nextNPCState(CharacterPunchSignal::NONE);
    
    if(willColide(gameObject, dx)) return;
    
    moveForwardTransform(dx)->apply(charPosition);
    
    this->gX = charPosition->x;
    this->gY = charPosition->y;
}

bool Character::willColideWithOtherPlayer(Character* another, GLfloat dx)
{
    if(another == this) return false;
    Point2D* thisPoint = new Point2D(0, 0);
    moveForwardTransform(dx)->apply(thisPoint);
    
    Circle thisCircle = Circle(thisPoint->x, thisPoint->y, this->torsoRadius);
    Circle anotherCircle = Circle(another->gX, another->gY, this->outsideRadius);
    
    return Collision::circleCircleIntersect(thisCircle, anotherCircle);
}

void Character::AnotherCharacterIsWithinRadius(Character* another, GLfloat dx)
{
    if(another == this) return;
    Point2D* thisPoint = new Point2D(0, 0);
    moveForwardTransform(dx)->apply(thisPoint);
    
    Circle thisCircle = Circle(thisPoint->x, thisPoint->y, this->outsideRadius);
    Circle anotherCircle = Circle(another->gX, another->gY, another->outsideRadius);
    
    bool colliding = Collision::circleCircleIntersect(thisCircle, anotherCircle);
    if(colliding){
        this->charState = CharacterState::AGGRESSIVE;
    } else {
        this->charState = CharacterState::PASSIVE;
    }
}

bool Character::willColideWithGameWalls(GLfloat dx) {
    Rectangle rect = Rectangle(this->gameObject->arena.x, this->gameObject->arena.y, this->gameObject->arena.width, this->gameObject->arena.height);

    Point2D* thisPoint = new Point2D(0, 0);
    moveForwardTransform(dx)->apply(thisPoint);
    Circle circ = Circle(thisPoint->x, thisPoint->y, this->torsoRadius);

    bool isIntersecting = Collision::circleInsideRectIntersect(circ, rect);
    return isIntersecting;
}


bool Character::willColide(Game* game, GLfloat dx) {
    dx = this->gameObject->applyTimeFix(dx);
    
    // Test aggresiveness
    AnotherCharacterIsWithinRadius(game->player1, dx);
    AnotherCharacterIsWithinRadius(game->player2, dx);
    
    if(willColideWithOtherPlayer(game->player1, dx)) return true;
    if(willColideWithOtherPlayer(game->player2, dx)) return true;
    if(willColideWithGameWalls(dx)) return true;
    
    return false;
}

void Character::hitDetection(Character* another) {
    if(!characterIsEnabled) return;
    if(another == this) return;
    
    if(this->punchState == CharacterPunchState::LEFT_PUNCH) {
        Point2D* thisPoint = new Point2D(0, 0);
        leftGloveTransform()->apply(thisPoint);
    
        Circle thisCircle = Circle(thisPoint->x, thisPoint->y, this->handRadius);
        Circle anotherCircle = Circle(another->gX, another->gY, this->torsoRadius);
        
        bool didCollide = Collision::circleCircleIntersect(thisCircle, anotherCircle);
        if(didCollide && countPoint){
            handleHitOpponent(another);
        }
        
    } else if(this->punchState == CharacterPunchState::RIGHT_PUNCH) {
        Point2D* thisPoint = new Point2D(0, 0);
        rightGloveTransform()->apply(thisPoint);
    
        Circle thisCircle = Circle(thisPoint->x, thisPoint->y, this->handRadius);
        Circle anotherCircle = Circle(another->gX, another->gY, another->torsoRadius);
        
        bool didCollide = Collision::circleCircleIntersect(thisCircle, anotherCircle);
        if(didCollide && countPoint){
            handleHitOpponent(another);
        }
    }
}


void Character::RotateBody(GLfloat inc) {
    inc = this->gameObject->applyTimeFix(inc);
    this->gTheta -= inc;
}

void Character::followCharacter(Game* game, Character* other, GLfloat dx) {
    if(!characterIsEnabled) return;
    Point2D* charPosition = new Point2D(0, 0);
    
    GLfloat angle = atan2(this->gY - other->gY, this->gX - other->gX);
    GLfloat deg = (angle*180)/PI;
    
    this->gTheta = deg + 90;
    
    this->MoveForward(dx/2);
}

void Character::setColor(Color _color) {
    this->torsoColor = _color;
}

GLfloat Character::getLeftMouseAngle(GLfloat xDistance) {
    GLfloat mappedValue = Util::map(xDistance, 0, (float)this->gameObject->arena.width/2, MIN_LEFT_ANGLE, MAX_LEFT_ANGLE);
    return Util::clamp(mappedValue, MAX_LEFT_ANGLE, MIN_LEFT_ANGLE);
}
GLfloat Character::getRightMouseAngle(GLfloat xDistance) {
    GLfloat mappedValue = Util::map(xDistance, 0, (float)this->gameObject->arena.width/2, MIN_RIGHT_ANGLE, MAX_RIGHT_ANGLE);
    return Util::clamp(mappedValue, MIN_RIGHT_ANGLE, MAX_RIGHT_ANGLE);
}

void Character::handlePlayerPunchControls() {
    if(!characterIsEnabled) return;
    
    if(this->gameObject->player1 == this){
        if(this->gameObject->mouse.leftButton.isPressed && !characterIsMoving()) {
            GLfloat xDistance = this->gameObject->mouse.currentPosition.x - this->gameObject->mouse.leftButton.clickPosition.x;
            
            GLfloat finalAngle;
            if(this->gameObject->mouse.currentPosition.x > this->gameObject->mouse.leftButton.clickPosition.x){
                if(punchState == CharacterPunchState::LEFT_PUNCH) resetHitOpponent();
                
                this->setPunchState(CharacterPunchState::RIGHT_PUNCH);
                finalAngle = getRightMouseAngle(abs(xDistance));
                this->RotateRightArmToAngle(finalAngle);
                this->RotateLeftArmToAngle(MIN_ANGLE);
            }
            else if(this->gameObject->mouse.currentPosition.x < this->gameObject->mouse.leftButton.clickPosition.x){
                if(punchState == CharacterPunchState::RIGHT_PUNCH) resetHitOpponent();
                
                this->setPunchState(CharacterPunchState::LEFT_PUNCH);
                finalAngle = getLeftMouseAngle(abs(xDistance));
                this->RotateLeftArmToAngle(finalAngle);
                this->RotateRightArmToAngle(-MIN_ANGLE);
            }
            else {
                resetHitOpponent();
                
                this->RotateLeftArmToAngle(MIN_LEFT_ANGLE);
                this->RotateRightArmToAngle(MIN_RIGHT_ANGLE);
            }
        } else {
            this->setPunchState(CharacterPunchState::IDLE);
            this->RotateRightArm(4, false);
            this->RotateLeftArm(4, false);
        }
    }
}

void Character::Draw(){
    DrawCharacter(gX, gY);
    
    hitDetection(this->gameObject->player1);
    hitDetection(this->gameObject->player2);
    
    handlePunchControls();
};

bool Character::characterIsMoving() {
    vector<char> moveKeys = {'w', 'a', 's', 'd', 'W', 'A', 'S', 'D'};
    for(char key : moveKeys) {
        if(this->gameObject->isKeyPressed(key)){
            this->gameObject->mouse.leftButton.setIsPressed(false);
            return true;
        }
    }
    return false;
}
