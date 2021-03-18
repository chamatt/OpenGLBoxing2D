#include "game.h"
#include "character.h"

void Game::initializeCharacters(GLfloat sizep1, GLfloat sizep2){
    this->player1 = new Character(this, 20);
    this->player2 = new Character(this, 20);
}

void Game::keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 'w':
        case 'W':
             keyStatus[(int)('w')] = 1; //Using keyStatus trick
             break;
        case 's':
        case 'S':
             keyStatus[(int)('s')] = 1; //Using keyStatus trick
             break;
        case 'f':
        case 'F':
             player1->RotateLeftArm(+INC_KEY);
             break;
        case 'r':
        case 'R':
             player1->RotateLeftArm(-INC_KEY);
             break;
        case 'g':
        case 'G':
             player1->RotateRightArm(+INC_KEY);
             break;
        case 't':
        case 'T':
             player1->RotateRightArm(-INC_KEY);
             break;
            
        case 'l':
        case 'L':
             keyStatus[(int)('l')] = 1; //Using keyStatus trick
             break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}


void Game::setPlayerStartPosition(Character* pl, GLfloat x, GLfloat y, GLfloat angle) {
    pl->setInitialPos(x, y, angle);
}
