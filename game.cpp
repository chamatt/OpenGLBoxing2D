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
   sprintf(this->str, "Player: %d vs Enemy: %d", this->player1->hitScore, this->player2->hitScore);
   //Define a posicao onde vai comecar a imprimir
   glRasterPos2f(x, y);
   //Imprime um caractere por vez
   tmpStr = this->str;
   while( *tmpStr ){
       glutBitmapCharacter(this->font, *tmpStr);
       tmpStr++;
   }
}

void Game::Output(int x, int y, Color color, string str)
{
  glColor3f( color.R, color.G, color.B );
  glRasterPos2f(x, y);
  int len, i;
  len = str.size();
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(this->font, str[i]);
  }
}

void Game::DrawGameOver()
{
    auto calcSize = [](string newStr) -> int { return (newStr.size() * 9)/2; };
    
    string winString = "You Win!";
    string loseString = "You Lose!";
    string tieString = "Game Over!";
    string restartString = "Press 'M' to restart the game";
    
    GLfloat centerX =this->arena.x+this->arena.width/2;
    GLfloat centerY = this->arena.y+this->arena.height/2;
    
    if(player1->hitScore > player2->hitScore)
        Output(centerX - calcSize(winString), centerY, Color(0,255,0), winString);
    
    if(player1->hitScore < player2->hitScore)
        Output(centerX - calcSize(loseString), centerY, Color(255,0,0), loseString);
    
    if(player1->hitScore == player2->hitScore)
        Output(centerX - calcSize(tieString), centerY, Color(0,0,255), tieString);
    
    Output(centerX - calcSize(restartString), centerY - 20, Color(255,255,255), restartString);
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
        case 'p':
        case 'P':
             player2->toggleCharacterEnabled();
             break;
        case 'o':
        case 'O':
            player1->toggleOutsideRadius();
            player2->toggleOutsideRadius();
            break;
        case 'm':
        case 'M':
            resetGame();
            break;
        case 'i':
        case 'I':
            this->maxScore = maxScore == 10 ? 50 : 10;
            break;
        case 'h':
        case 'H':
            player1->toggleShowHitmark();
            player2->toggleShowHitmark();
            break;
        case 27 :
            if(gameIsOver)
             exit(0);
            else {
                this->player1->hitScore = 0;
                this->player2->hitScore = 0;
                gameOver();
            }
        
    }
    
    glutPostRedisplay();
}


void Game::setPlayerStartPosition(Character* pl, GLfloat x, GLfloat y, GLfloat angle) {
    pl->setInitialPos(x, y, angle);
}

Game::Game(string xmlPath) {
    this->xmlPath = xmlPath;
    GameInitObject initObject = XMLParser::parseArena(xmlPath);
    
    this->player1 = new Character(this, initObject.player1.headSize, initObject.player1.position,  initObject.player1.angle - 90);
//    this->player1->setColor(Color(90, 128, 184));
    this->player1->setPlayerType(CharacterType::PLAYER);
    this->player2 = new Character(this, initObject.player2.headSize, initObject.player2.position,  initObject.player2.angle - 90);
//    this->player2->setColor(Color(78, 173, 71));
    this->player2->setPlayerType(CharacterType::ENEMY);

    this->arena = initObject.arena;
}

void Game::resetGame() {
    gameIsOver = false;
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

void Game::gameOver() {
    this->player1->characterIsEnabled = false;
    this->player2->characterIsEnabled = false;
    gameIsOver = true;
}

void Game::checkGameOver() {
    if(this->player1->hitScore >= this->maxScore || this->player2->hitScore >= this->maxScore) {
        gameOver();
    }
}
