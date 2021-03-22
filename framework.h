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

#define PI 3.14

using namespace std;

void initFramework();

class Point2D;
class Circle;
class Rectangle;
class Color;
class Random;
class Collision;

class Util {
public:
    static GLfloat degToRad(GLfloat angle) {
        GLfloat rad = (angle*PI)/180.0;
        return rad;
    }
    
    static GLfloat radToDeg(GLfloat angle) {
        GLfloat deg = (angle*180.0)/PI;
        return deg;
    }
    
    static GLfloat map(GLfloat x, GLfloat in_min, GLfloat in_max, GLfloat out_min, GLfloat out_max)
    {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
    
    static GLfloat clamp(GLfloat v, GLfloat lo, GLfloat hi) {
        GLfloat clamped_value = v;
        if      ( v < lo ) clamped_value = lo;
        else if ( v > hi ) clamped_value = hi;
        return clamped_value;
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
    
        // Angle in degrees
        GLfloat getAngle() {
            GLfloat theta_rad = atan2(this->y, this->x);
            GLfloat theta_deg = (theta_rad/M_PI*180) + (theta_rad > 0 ? 0 : 360);
            
            return theta_deg;
        }
        
        Point2D operator-(Point2D other) {
//            cout << this->toString() << " - " << other.toString() << "=" << Point2D(this->x - other.x, this->y - other.y).toString() << endl;
            
            return Point2D(this->x - other.x, this->y - other.y);
        }
    
        string toString() {
            return "Point(" + to_string(this->x) + "," + to_string(this->y) + ")";
        }
};




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
    
    string colorString;
    
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
    
    Color(string _color): colorString(_color) {}
};

class Circle {
public:
    GLfloat x;
    GLfloat y;
    Point2D point;
    GLfloat radius;
    Color color;
    
    void setColor(Color _color);
    
    Circle(GLfloat px, GLfloat py, GLfloat pradius) : x(px), y(py), radius(pradius), point(Point2D(px, py)) {}
    
    string toString() {
        return "Circle(" + to_string(this->x) + "," + to_string(this->y) + "," + to_string(this->radius) + ")";
    }
};

class Rectangle {
public:
    GLfloat x;
    GLfloat y;
    GLfloat width;
    GLfloat height;
    
    Rectangle(GLfloat px, GLfloat py, GLfloat pwidth, GLfloat pheight) : x(px), y(py), width(pwidth), height(pheight) {}
    
    string toString() {
        return "Rectangle(" + to_string(this->x) + "," + to_string(this->y) + "," + to_string(this->x + this->width) + "," + to_string(this->y + this->height) + ")";
    }
};

class Collision {
public:
    
    static bool circleInsideRectIntersect(Circle circle, Rectangle rect) {
        GLfloat leftWall = rect.x;
        GLfloat rightWall = rect.x + rect.width;
        GLfloat bottomWall = rect.y;
        GLfloat topWall = rect.y + rect.height;
        
        if(circle.x - circle.radius < leftWall) return true;
        if(circle.x + circle.radius > rightWall) return true;
        if(circle.y - circle.radius < bottomWall) return true;
        if(circle.y + circle.radius > topWall) return true;
        return false;
    }
    
    static bool circleCircleIntersect(Circle circle1, Circle circle2) {
        GLfloat intersectionRadius = circle1.radius + circle2.radius;
        return circle2.point.distanceTo(&circle1.point) < intersectionRadius;
    }
};

class Transformation {
    private:
        bool shouldLog = false;
        
        void log();
        
        void logTranslate(GLfloat x, GLfloat y);
        
        void logScale(GLfloat x, GLfloat y);
    
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
    
        void scale2d(GLfloat Sx, GLfloat Sy);

        void rotate2d(GLfloat angle);

        void apply(Point2D* point);
    
        void logMode(bool state);
};


#endif	/* FRAMEWORK_H */
