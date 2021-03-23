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
#include <algorithm>
#include "game.h"
#include "framework.h"
// Dimensions
#define firstPaddleHeight 50
#define secondPaddleHeight 40
#define paddleWidth 10
#define baseHeight 40
#define baseWidth 100
#define radiusWheel 30

#define MIN_LEFT_ANGLE 140
#define MAX_LEFT_ANGLE 25
#define MIN_RIGHT_ANGLE -140
#define MAX_RIGHT_ANGLE -25

#define MIN_ANGLE 140

#define BACKWARD_HIT_MOVE -10

using namespace std;

class Game;

class DefaultColors {
public:
    DefaultColors(){}
    // Nose
    Color playerNoseColor = Color(90, 128, 184);
    Color playerNoseStroke = Color(90, 128, 184);
    Color enemyNoseColor = Color(78, 173, 71);
    Color enemyNoseStroke = Color(78, 173, 71);
    
    // Arms
    Color armsColor = Color(161, 186, 102);
    
    // Hand
    Color handColor = Color(179, 87, 81);
    Color handStroke = Color(130, 61, 57);
    Color hitHandColor = Color(255, 0, 255);
    Color hitHandStroke = Color(255, 10, 255);
    
    // torso
    Color playerTorsoColor = Color(90, 128, 184);
    Color playerTorsoStroke = Color(90, 128, 184);
    Color enemyTorsoColor = Color(78, 173, 71);
    Color enemyTorsoStroke = Color(78, 173, 71);
};

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
    
    DefaultColors defaultColors;
    
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
    
    GLfloat leftArmFirstJointAngle = MIN_ANGLE;
    GLfloat leftArmSecondJointAngle = -MIN_ANGLE;
    GLfloat rightArmFirstJointAngle = -MIN_ANGLE;
    GLfloat rightArmSecondJointAngle = MIN_ANGLE;
    
    CharacterType charType = CharacterType::PLAYER;
    CharacterState charState = CharacterState::PASSIVE;
    CharacterPunchState punchState = CharacterPunchState::IDLE;
    
    int countPoint = true;
    
    void setPunchState(CharacterPunchState state) {
        switch(state) {
            case CharacterPunchState::IDLE:
                resetHitOpponent();
                this->punchState = state;
                break;
            default:
                this->punchState = state;
                break;
        }
    }
    void hitDetection(Character* another);
    
    void handleHitOpponent(Character* another) {
        if(countPoint){
            this->countPoint = false;
            if(showHitmark){
                this->handColor = defaultColors.hitHandColor;
                this->handStroke = defaultColors.hitHandStroke;
            }
            this->hitScore++;
//            another->MoveForward(BACKWARD_HIT_MOVE);
        }
    }
    
    void resetHitOpponent() {
        this->countPoint = true;
        this->handColor = defaultColors.handColor;
        this->handStroke = defaultColors.handStroke;
    }

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
    
    Transformation* rightGloveTransform() {
        Transformation* tr = new Transformation();
        
        tr->translate2d(gX, gY);
        tr->rotate2d(gTheta);
        tr->translate2d(this->torsoRadius, 0);
        tr->rotate2d(this->rightArmFirstJointAngle);
        tr->translate2d(0, this->armLength);  /* Move to second left arm joint */
        tr->rotate2d(this->rightArmSecondJointAngle);
        tr->translate2d(0, this->foreArmLength);  /* Move to second left arm joint */
        tr->translate2d(0, handRadius);  /* Move to second left arm joint */
        
        return tr;
    }
    
    Transformation* leftGloveTransform() {
        Transformation* tr = new Transformation();
        
        tr->translate2d(gX, gY);
        tr->rotate2d(gTheta);
        tr->translate2d(-this->torsoRadius, 0);
        tr->rotate2d(this->leftArmFirstJointAngle);
        tr->translate2d(0, this->armLength);  /* Move to second left arm joint */
        tr->rotate2d(this->leftArmSecondJointAngle);
        tr->translate2d(0, this->foreArmLength);  /* Move to second left arm joint */
        tr->translate2d(0, handRadius);  /* Move to second left arm joint */
        
        return tr;
    }

public:
    
    GLfloat gX;
    GLfloat gY;
    GLfloat gTheta;
    
    int hitScore = 0;
    
    bool characterIsEnabled = true;
    void toggleCharacterEnabled() {
       this->characterIsEnabled = !characterIsEnabled;
    }
    bool showOutsideRadius = false;
    void toggleOutsideRadius() {
       this->showOutsideRadius = !showOutsideRadius;
    }
    bool showHitmark = false;
    void toggleShowHitmark() {
       this->showHitmark = !showHitmark;
    }
    
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
    
    bool hitDetection(Game* game, GLfloat dx);
    
    void handlePunchControls() {
        switch(charType){
            case CharacterType::ENEMY:
                handleEnemyPunchControls();
                break;
            case CharacterType::PLAYER:
                handlePlayerPunchControls();
                break;
            default: break;
        }
    }
    
    void handleEnemyPunchControls() {
        if(punchState == CharacterPunchState::LEFT_PUNCH) {
            this->RotateLeftArm(-4, false);
        }
        if(punchState == CharacterPunchState::RETURN_LEFT_PUNCH) {
            this->RotateLeftArm(4, false);
        }
        if(punchState == CharacterPunchState::RIGHT_PUNCH) {
            this->RotateRightArm(-4, false);
        }
        if(punchState == CharacterPunchState::RETURN_RIGHT_PUNCH) {
            this->RotateRightArm(4, false);
        }
    }
    
    GLfloat getLeftMouseAngle(GLfloat xDistance);
    GLfloat getRightMouseAngle(GLfloat xDistance);
    
    void handlePlayerPunchControls();
    void Draw();
    bool RotateLeftArm(GLfloat inc, bool applyFix = true);
    bool RotateRightArm(GLfloat inc, bool applyFix = true);
    
    void RotateLeftArmToAngle(GLfloat angle);
    void RotateRightArmToAngle(GLfloat angle);
    
    void RotateBody(GLfloat inc);
    void MoveForward(GLfloat dx, bool applyFix = true);
    
    void followCharacter(Game* game, Character* other, GLfloat dx);
    
    void setPlayerType(CharacterType type) {
        this->charType = type;
        if(type == CharacterType::PLAYER) {
            this->torsoColor = defaultColors.playerTorsoColor;
            this->torsoStroke = defaultColors.playerTorsoStroke;
            this->noseColor = defaultColors.playerNoseColor;
            this->noseStroke = defaultColors.playerNoseStroke;
        } else if(type == CharacterType::ENEMY) {
            this->torsoColor = defaultColors.enemyTorsoColor;
            this->torsoStroke = defaultColors.enemyTorsoStroke;
            this->noseColor = defaultColors.enemyNoseColor;
            this->noseStroke = defaultColors.enemyNoseStroke;
        }
        
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
                
                if(random == 0) this->setPunchState(CharacterPunchState::LEFT_PUNCH);
                else this->setPunchState(CharacterPunchState::RIGHT_PUNCH);
            }
        }
        else if(punchState == LEFT_PUNCH) {
            if(signal == CharacterPunchSignal::MAX_REACHED) {
                this->setPunchState(CharacterPunchState::RETURN_LEFT_PUNCH);
            }
        }
        else if(punchState == RETURN_LEFT_PUNCH) {
            if(signal == CharacterPunchSignal::MIN_REACHED) {
                this->setPunchState(CharacterPunchState::IDLE);
            }
        }
        else if(punchState == RIGHT_PUNCH) {
            if(signal == CharacterPunchSignal::MAX_REACHED) {
                this->setPunchState(CharacterPunchState::RETURN_RIGHT_PUNCH);
            }
        }
        else if(punchState == RETURN_RIGHT_PUNCH) {
            if(signal == CharacterPunchSignal::MIN_REACHED) {
                this->setPunchState(CharacterPunchState::IDLE);
            }
        }
    }
    
    bool characterIsMoving();
};

#endif /* character_hpp */

