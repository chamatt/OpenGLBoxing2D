#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "framework.h"
#include "character.h"
#include "game.h"
#define INC_KEY 13
#define INC_KEYIDLE 2

#define PI 3.14

Game* game;

void renderScene(void)
{
     // Clear the screen.
     glClear(GL_COLOR_BUFFER_BIT);
 
     game->player1->Draw();
     game->player2->Draw();
    
     game->PrintScore();

     glutSwapBuffers(); // Desenha the new frame of the game->
}

void keyup(unsigned char key, int x, int y)
{
    game->keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       game->keyStatus[i] = 0;
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(game->arena.x,     // X coordinate of left edge
            game->arena.x + game->arena.width,     // X coordinate of right edge
            game->arena.y,     // Y coordinate of bottom edge
            game->arena.y + game->arena.height,     // Y coordinate of top edge
            -100,     // Z coordinate of the “near” plane            
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
      
}


GLdouble currentTime, timeDiference;

GLfloat moveByTime(GLfloat amount) {
    return amount * (timeDiference/20);
}

void frameCorrectionFix() {
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    //Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    // Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;
    //Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;
}

void idle(void)
{
    game->frameCorrectionFix();
    double inc = INC_KEYIDLE;
    
    game->player2->followCharacter(game, game->player1, inc);
    
    //Treat keyPress
    if(game->isKeyPressed('a'))
    {
        game->player1->RotateBody(-inc);
    }
    if(game->isKeyPressed('d'))
    {
        game->player1->RotateBody(inc);
    }
    
    if(game->isKeyPressed('w'))
    {
        game->player1->MoveForward(game, inc);
    }
    if(game->isKeyPressed('s'))
    {
        game->player1->MoveForward(game, -inc);
    }
    
   
    
//    //Trata o tiro (soh permite um tiro por vez)
//    //Poderia usar uma lista para tratar varios tiros
//    if(tiro){
//        tiro->Move(timeDiference/100);
//
//        //Trata colisao
//        if (alvo.Atingido(tiro)){
//            atingido++;
//            alvo.Recria(rand()%500 - 250, 200);
//        }
//
//        if (!tiro->Valido()){
//            delete tiro;
//            tiro = NULL;
//        }
//    }
    
    
    
//    //Control animation
//    if (animate){
//        static int dir = 1;
//        if (robo.ObtemX() > (ViewingWidth/2)){
//            dir *= -1;
//        }
//        else if (robo.ObtemX() < -(ViewingWidth/2)){
//            dir *= -1;
//        }
//        robo.MoveEmX(moveByTime(dir*INC_KEYIDLE));
//    }
    
    glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y) {
    game->keyPress(key, x, y);
}

void mouseEvent(int button, int state, int x, int y) {
    game->mouseEvent(button, state, x, y);
};
void mouseMovement(int x, int y) {
    game->mouseMovement(x, y);
}
 
int main(int argc, char *argv[])
{
    initFramework();
    
    game = new Game(argv[1]);
    
//    game.initializeCharacters(20, 20);
//    game.setPlayerStartPosition(game.player1, -150, -150, -45);
//    game.setPlayerStartPosition(game.player2, 150, 150, 120);
    
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(game->arena.width, game->arena.height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Boxing 2D");
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
  
    glutMouseFunc(mouseEvent);
    glutPassiveMotionFunc(mouseMovement);
    glutMotionFunc(mouseMovement);
    
    init();
 
    glutMainLoop();
 
    return 0;
}
