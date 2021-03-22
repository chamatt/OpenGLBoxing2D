//
//  xmlparse.cpp
//  OpenGLBoxing2D
//
//  Created by Matheus Leanon on 20/03/21.
//

#include "xmlparser.h"
#include "framework.h"

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

    XMLNode* rectangle = doc.FirstChildElement()->FirstChild();
    Rectangle arena = XMLParser::parseRectangle(rectangle);
    XMLNode* firstCircleNode = rectangle->NextSibling();
    Circle firstCircle = XMLParser::parseCircle(firstCircleNode);
    XMLNode* secondCircleNode = firstCircleNode->NextSibling();
    Circle secondCircle = XMLParser::parseCircle(secondCircleNode);
    
    PlayerObject* player1;
    PlayerObject* player2;
    
    auto changeYCoordinates = [=](Point2D &point) -> void
    {
        GLfloat ypos = 2*arena.y + arena.height - point.y;
        point.y = ypos;
    };
    
    Point2D firstPoint = Point2D(firstCircle.x, firstCircle.y);
    changeYCoordinates(firstPoint);
    Point2D secondPoint = Point2D(secondCircle.x, secondCircle.y);
    changeYCoordinates(secondPoint);
    
    GLfloat anglep1 = (Point2D(secondPoint.x, secondPoint.y) - Point2D(firstPoint.x, firstPoint.y)).getAngle();
    GLfloat anglep2 = (Point2D(firstPoint.x, firstPoint.y) - Point2D(secondPoint.x, secondPoint.y)).getAngle();
    
    if(firstCircle.color.colorString == "green") {
        player1 = new PlayerObject(firstCircle.radius, Point2D(firstPoint.x, firstPoint.y), anglep1);
        player2 = new PlayerObject(secondCircle.radius, Point2D(secondPoint.x,  secondPoint.y), anglep2);
    } else {
        player2 = new PlayerObject(firstCircle.radius, Point2D(firstPoint.x,  firstPoint.y), anglep1);
        player1 = new PlayerObject(secondCircle.radius, Point2D(secondPoint.x,  secondPoint.y), anglep2);
    }
    
    return GameInitObject(arena, *player1, *player2);
}
