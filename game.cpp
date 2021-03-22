#include "game.h"
#include "character.h"
#include "game-config.h"
#include "xmlparser.h"

void Game::initializeCharacters(GLfloat sizep1, GLfloat sizep2){
    this->player1 = new Character(this, 20);
    this->player2 = new Character(this, 20);
}

void Game::PrintScore()
{
   GLfloat x = this->arena.x+20, y = this->arena.y+20;
   glColor3f(1.0, 1.0, 1.0);
   //Cria a string a ser impressa
   char *tmpStr;
   sprintf(this->str, "Player 1: %d X Player 2: %d", this->player1->hitScore, this->player2->hitScore);
   //Define a posicao onde vai comecar a imprimir
   glRasterPos2f(x, y);
   //Imprime um caractere por vez
   tmpStr = this->str;
   while( *tmpStr ){
       glutBitmapCharacter(this->font, *tmpStr);
       tmpStr++;
   }
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

Game::Game(string xmlPath) {
    GameInitObject initObject = XMLParser::parseArena(xmlPath);
    
    this->player1 = new Character(this, initObject.player1.headSize, initObject.player1.position,  initObject.player1.angle - 90);
    this->player1->setColor(Color(90, 128, 184));
    this->player1->setPlayerType(CharacterType::PLAYER);
    this->player2 = new Character(this, initObject.player2.headSize, initObject.player2.position,  initObject.player2.angle - 90);
    this->player2->setColor(Color(78, 173, 71));
    this->player2->setPlayerType(CharacterType::ENEMY);

    this->arena = initObject.arena;
}

Game::Game() {
    this->arena = Rectangle(0,0,0,0);
}
