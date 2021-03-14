#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifndef FRAMEWORK_H
#define	FRAMEWORK_H

#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

void initFramework();

class Random {
    public:
        GLfloat number;
        
        Random() {
            this->number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }
        Random(GLfloat X) {
            this->number = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/X));
        }
        Random(GLfloat LO, GLfloat HI) {
            this->number = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        }
};

class Color {
public:
    GLfloat R;
    GLfloat G;
    GLfloat B;
    
    Color() {
        this->R = 0;
        this->G = 0;
        this->B = 0;
    }
    
    Color(GLfloat R, GLfloat G, GLfloat B) {
        this->R = (float)R/(float)255;
        this->G = (float)G/(float)255;
        this->B = (float)B/(float)255;
    }
};

class Point2D {
    public:
        GLfloat x;
        GLfloat y;

        Point2D(GLfloat x, GLfloat y){
            this->x = x;
            this->y = y;
        };
    
        GLfloat distanceTo(Point2D* another) {
            return sqrt(pow(this->x - another->x, 2) + pow(this->y - another->y, 2));
        }
};

class Transformation {
    private:
        bool shouldLog = false;
        
        void log();
        
        void logTranslate(GLfloat x, GLfloat y);
    
        void logRotate(GLfloat angle);
    
        void matrixMultiply(vector< vector<GLfloat> > mat2);

        void matrixVectorMultiply(vector< vector<GLfloat> > vet1,
                                  vector< vector<GLfloat> > &res);

    public:
        vector< vector<GLfloat> > matrix;

        vector< vector<GLfloat> > getIdentity();
        Transformation(){
            this->matrix = this->getIdentity();
            this->log();
        };

        void translate2d(GLfloat x, GLfloat y);

        void rotate2d(GLfloat angle);

        void apply(Point2D* point);
    
        void logMode(bool state);
};


#endif	/* FRAMEWORK_H */
