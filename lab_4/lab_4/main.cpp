#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <QDebug>
#include <GL/glut.h>
#include "point.h"

int SCREEN_HEIGHT = 700;
int points = 0;
std::vector < Point > base;


Point operator * (float p, Point rPoint) {
    return Point(p * rPoint.x, p * rPoint.y);
}

Point operator + (const Point &lPoint, const Point &rPoint) {
    return(Point(lPoint.x + rPoint.x, lPoint.y + rPoint.y));
}

std::ostream&  operator << (std::ostream& s, const Point &p) {
    s << "( " << p.x << " ; " << p.y << " )\n";
    return s;
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 700.0);

}

void drawDot(int x, int y) {
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawLine(Point P1, Point P2) {
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(P1.x, P1.y);
    glVertex2f(P2.x, P2.y);
    glEnd();
    glFlush();
}

void drawControlLine(Point P1, Point P2) {
    glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex2f(P1.x, P1.y);
    glVertex2f(P2.x, P2.y);
    glEnd();
    glFlush();
}

void drawParabol(Point P1, Point P2, Point P3, bool flag, bool flag2) {

    float a = ((P3.y-P1.y)*(P2.x-P1.x)-(P2.y-P1.y)*(P3.x-P1.x)) / ((P3.x*P3.x - P1.x * P1.x)*
                                                                   (P2.x-P1.x) - (P2.x*P2.x - P1.x * P1.x)*(P3.x-P1.x));
    float b = (P2.y-P1.y-a*(P2.x*P2.x - P1.x * P1.x))/(P2.x - P1.x);
    float c = P1.y - (a * P1.x*P1.x + b * P1.x);

    glBegin(GL_LINE_STRIP);
    if (flag == false) {
        glColor3f(1,1,1);
    } else {
        glColor3f(0,1,0);
    }
    if (flag2 == false) {
        for (GLfloat x = std::min(P1.x, P2.x); x < std::max(P1.x,P2.x); x+= 0.001) {
            glVertex2f(x, a * x * x + b * x + c);
        }
    } else {
        for (GLfloat x = std::min(P3.x, P2.x); x < std::max(P3.x,P2.x); x+= 0.001) {
            glVertex2f(x, a * x * x + b * x + c);
        }
    }
    glEnd();
}

float tj(float ti, Point Pi, Point Pj) {
    float alpha = 0.5;
    float xi = Pi.getX();
    float yi = Pi.getY();
    float xj = Pj.getX();
    float yj = Pj.getY();
    return pow(pow((pow((xj - xi),2) + pow((yj - yi), 2)), 0.5), alpha) + ti;
}

std::vector < Point >  CatmullRomSpline(Point P0, Point P1, Point P2, Point P3) {
     float amountOfPoints = 10;

     float t0 = 0;
     float t1 = tj(t0, P0, P1);
     float t2 = tj(t1, P1, P2);
     float t3 = tj(t2, P2, P3);
     std::vector < Point > res;
     for(float t=t1; t<t2; t+=((t2 - t1) / amountOfPoints))
             {
                 Point A1 = ((t1-t)/(t1-t0)) * P0 + ((t-t0)/(t1-t0)) * P1;
                 Point A2 = ((t2-t)/(t2-t1)) * P1 + ((t-t1)/(t2-t1)) * P2;
                 Point A3 = ((t3-t)/(t3-t2)) * P2 + ((t-t2)/(t3-t2)) * P3;

                 Point B1 = ((t2-t)/(t2-t0)) * A1 + ((t-t0)/(t2-t0)) * A2;
                 Point B2 = ((t3-t)/(t3-t1)) * A2 + ((t-t1)/(t3-t1)) * A3;

                 Point C = ((t2-t)/(t2-t1)) * B1 + ((t-t1)/(t2-t1)) * B2;
                 res.push_back(C);
             }
     return res;
}

std::vector < Point > CatmullRomChain(std::vector < Point > points) {
    std::vector < Point > res;
    for (size_t i = 0; i < points.size() - 3; i++) {
        std::vector < Point > buf = CatmullRomSpline(points[i], points[i + 1], points[i + 2], points[i + 3]);
        res.insert(std::end(res), std::begin(buf), std::end(buf));
    }
    return res;
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        base.push_back(Point((float)x, (float)(SCREEN_HEIGHT - y)));
        points++;
        drawDot(x, SCREEN_HEIGHT - y);
        if (points >= 4 /* == 7*/)
         {
            drawParabol(base[0], base[1], base[2], true, false);
            drawParabol(base[base.size() - 4], base[base.size() - 3], base[base.size()-2], false, true);
            drawParabol(base[base.size() - 3], base[base.size() - 2], base[base.size() - 1], true, true);
            std::vector < Point > arr = CatmullRomChain(base);
            for (size_t i = 0; i < arr.size() - 1; i++) {
                drawLine(arr[i], arr[i + 1]);
            }
            /*arr.clear();   // <---несколько сплайнов на листе
            base.clear();
            points = 0;*/
        }
    }
}


void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);

    glutInitWindowPosition(100, 150);
    glutCreateWindow("Catmull Rom spline");
    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
