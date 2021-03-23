#include "xmlparser.h"
#include "framework.h"
#include <map>

Rectangle XMLParser::parseRectangle(XMLNode* xmlNode) {
    GLfloat x = xmlNode->ToElement()->DoubleAttribute("x");
    GLfloat y = xmlNode->ToElement()->DoubleAttribute("y");
    GLfloat width = xmlNode->ToElement()->DoubleAttribute("width");
    GLfloat height = xmlNode->ToElement()->DoubleAttribute("height");
    
    Rectangle rect = Rectangle(x, y, width, height);
    return rect;
}

Circle XMLParser::parseCircle(XMLNode* xmlNode) {
    GLfloat cx = xmlNode->ToElement()->DoubleAttribute("cx");
    GLfloat cy = xmlNode->ToElement()->DoubleAttribute("cy");
    GLfloat radius = xmlNode->ToElement()->DoubleAttribute("r");
    string color = xmlNode->ToElement()->Attribute("fill");
    
    Circle circle = Circle(cx, cy, radius);
    circle.setColor(Color(color));
    return circle;
}

GameInitObject XMLParser::parseArena(string xmlPath) {
    std::string str;
    const char * c = xmlPath.c_str();
    XMLDocument doc;
    XMLError error = doc.LoadFile(c);
  
    if(error != XMLError::XML_SUCCESS){
        exit(1);
    }

    XMLNode* first = doc.FirstChildElement()->FirstChild();
    string firstColor = first->ToElement()->Attribute("fill");
    XMLNode* second = first->NextSibling();
    string secondColor = second->ToElement()->Attribute("fill");
    XMLNode* third = second->NextSibling();
    string thirdColor = third->ToElement()->Attribute("fill");
    
    map<string, XMLNode*> elementMap;
    
    elementMap[firstColor] = first;
    elementMap[secondColor] = second;
    elementMap[thirdColor] = third;
    
    Rectangle arena = XMLParser::parseRectangle(elementMap["blue"]);
    
    Circle playerCircle = XMLParser::parseCircle(elementMap["green"]);
    Circle enemyCircle = XMLParser::parseCircle(elementMap["red"]);
    
    PlayerObject* player1;
    PlayerObject* player2;
    
    auto changeYCoordinates = [=](Point2D &point) -> void
    {
        GLfloat ypos = 2*arena.y + arena.height - point.y;
        point.y = ypos;
    };
    
    Point2D firstPoint = Point2D(playerCircle.x, playerCircle.y);
    changeYCoordinates(firstPoint);
    Point2D secondPoint = Point2D(enemyCircle.x, enemyCircle.y);
    changeYCoordinates(secondPoint);
    
    GLfloat anglep1 = (Point2D(secondPoint.x, secondPoint.y) - Point2D(firstPoint.x, firstPoint.y)).getAngle();
    GLfloat anglep2 = (Point2D(firstPoint.x, firstPoint.y) - Point2D(secondPoint.x, secondPoint.y)).getAngle();
    
    player1 = new PlayerObject(playerCircle.radius, Point2D(firstPoint.x, firstPoint.y), anglep1);
    player2 = new PlayerObject(enemyCircle.radius, Point2D(secondPoint.x,  secondPoint.y), anglep2);
    
    return GameInitObject(arena, *player1, *player2);
}
