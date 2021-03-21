//
//  xmlparse.hpp
//  OpenGLBoxing2D
//
//  Created by Matheus Leanon on 20/03/21.
//

#ifndef xmlparse_hpp
#define xmlparse_hpp

#include <stdio.h>
#include "game-config.h"
#include "framework.h"
#include "tinyxml2lib.h"

using namespace tinyxml2;

class XMLParser {
public:
    XMLParser() {}
    
    static Rectangle parseRectangle(XMLNode* xmlNode);
    
    static Circle parseCircle(XMLNode* xmlNode);
    
    static GameInitObject parseArena(string xmlPath);
};

#endif /* xmlparse_hpp */
