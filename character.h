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

enum CharacterType {
    PLAYER,
    ENEMY
};

enum CharacterState {
    PASSIVE,
    AGGRESSIVE
};

enum CharacterPunchState {
    IDLE,
    LEFT_PUNCH,
    RETURN_LEFT_PUNCH,
    RIGHT_PUNCH,
    RETURN_RIGHT_PUNCH
};
enum CharacterPunchSignal {
    NONE,
    MAX_REACHED,
    MIN_REACHED
};

class Character {
    Game* gameObject;
    
    Color torsoColor;
    Color torsoStroke;
    Color noseColor;
    Color noseStroke;
    Color armsColor;
    Color handColor;
    Color handStroke;
    
    GLfloat armLength;
    GLfloat foreArmLength;
    GLfloat armWidth;
    
    GLfloat torsoRadius;
    GLfloat handRadius;
    GLfloat noseRadius;
    GLfloat outsideRadius;
    
    GLfloat leftArmFirstJointAngle = 120;
    GLfloat leftArmSecondJointAngle = -120;
    GLfloat rightArmFirstJointAngle = -120;
    GLfloat rightArmSecondJointAngle = 120;
    
    CharacterType charType = CharacterType::PLAYER;
    CharacterState charState = CharacterState::PASSIVE;
    CharacterPunchState punchState = CharacterPunchState::IDLE;
    
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
    
    GLfloat gX;
    GLfloat gY;
    GLfloat gTheta;
    GLfloat direction;
    
    Character(Game* game, GLfloat size);
    Character(Game* game, GLfloat size, Point2D position, GLfloat angle);
    
    void setInitialPos(GLfloat x, GLfloat y, GLfloat angle) {
        this->gX = x;
        this->gY = y;
        this->gTheta = angle;
    }
    
    bool willColideWithGameWalls(GLfloat dx);
    
    bool willColideWithOtherPlayer(Character* another, GLfloat dx);
    
    void AnotherCharacterIsWithinRadius(Character* another, GLfloat dx);
    
    bool willColide(Game* game, GLfloat dx);
    
    void Draw(){
        if(punchState == CharacterPunchState::LEFT_PUNCH) {
            this->RotateLeftArm(-2);
        }
        if(punchState == CharacterPunchState::RETURN_LEFT_PUNCH) {
            this->RotateLeftArm(2);
        }
        if(punchState == CharacterPunchState::RIGHT_PUNCH) {
            this->RotateRightArm(-2);
        }
        if(punchState == CharacterPunchState::RETURN_RIGHT_PUNCH) {
            this->RotateRightArm(2);
        }
        
        DrawCharacter(gX, gY);
    };
    bool RotateLeftArm(GLfloat inc);
    bool RotateRightArm(GLfloat inc);
    void RotateBody(GLfloat inc);
    void MoveForward(Game* game, GLfloat dx);
    
    void followCharacter(Game* game, Character* other, GLfloat dx);
    
    void setPlayerType(CharacterType type) {
        this->charType = type;
    }
    
    GLfloat GetX(){
        return gX;
    };
    GLfloat GetY(){
        return gY;
    };
    
    Color color;
    
    void setColor(Color _color);
    
    void nextNPCState(CharacterPunchSignal signal = CharacterPunchSignal::NONE) {
        if(charType != CharacterType::ENEMY) return;
        
        if(punchState == IDLE) {
            if(charState == CharacterState::AGGRESSIVE) {
                GLint random = (int)Random(2).number;
                punchState = random == 0 ? CharacterPunchState::LEFT_PUNCH : CharacterPunchState::RIGHT_PUNCH;
            }
        }
        else if(punchState == LEFT_PUNCH) {
            if(signal == CharacterPunchSignal::MAX_REACHED) {
                punchState = CharacterPunchState::RETURN_LEFT_PUNCH;
            }
        }
        else if(punchState == RETURN_LEFT_PUNCH) {
            if(signal == CharacterPunchSignal::MIN_REACHED) {
                punchState = CharacterPunchState::IDLE;
            }
        }
        else if(punchState == RIGHT_PUNCH) {
            if(signal == CharacterPunchSignal::MAX_REACHED) {
                punchState = CharacterPunchState::RETURN_RIGHT_PUNCH;
            }
        }
        else if(punchState == RETURN_RIGHT_PUNCH) {
            if(signal == CharacterPunchSignal::MIN_REACHED) {
                punchState = CharacterPunchState::IDLE;
            }
        }
    }
};

#endif /* character_hpp */

