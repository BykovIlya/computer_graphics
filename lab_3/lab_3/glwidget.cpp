#include "glwidget.h"
#include "mainwindow.h"
#include <vector>
#include <QDebug>

Point::Point() {
    this->x = 0.0;
    this->y = 0.0L;
    this->f = 0.0L;
}
Point::Point(GLfloat x, GLfloat y, bool f) {
    this->x = x;
    this->y = y;
    this->f = f;
}

void Point::operator =(const Point& Q) {
    this->x = Q.x;
    this->y = Q.y;
    this->f = Q.f;
}

GLfloat Point::len(Point Q) {
    GLfloat len =  std::sqrt(((x - Q.x) * (x - Q.x) + (y - Q.y) * (y - Q.y)));
    return len;
}

Point Point::centerOfInscribedCircle(Point A, Point B, Point C, GLfloat AB, GLfloat BC, GLfloat AC) {
     *this = Point((AB * C.x + BC * A.x + AC * B.x) / (AB + BC + AC),
            (AB * C.y + BC * A.y + AC * B.y) / (AB + BC + AC), 0);
     return *this;
}

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
}

GLWidget::~GLWidget() {}
void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0,0,0,0);
}

const double precision = 0.000001;

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Point A(-0.9000, -0.9000 ,0);        // прямой угол
    Point B(-0.9000,  0.100 ,0);        // угол 60 градусов
    Point C(-0.9 + A.len(B) * sqrt(3.0),  -0.9000,0);        // угол 30 градусов
    std::vector < Point > points;
    points = drawFractal(A, B, C, deg, points, 0, 0);

    //points = drawFractal(A, B, C, deg, points, 0, 0);
   /* for (int i = 0; i < deg; i++) {
        glBegin(GL_POINTS);
            glColor3f(1,1,1);
            glVertex2f(points[i].x, points[i].y);
        glEnd();
    }*/

    for (int k = 0; k < pow(3, deg - 1); k++) {
        //glBegin(GL_LINES);
        for (size_t i  = k * points.size()/ (pow(3, deg - 1));
             i < (k+1) * points.size()/ (pow(3, deg - 1)) - 1; i++) {
          //  glColor3f(1,1,1);
            //    glVertex2f(points[i].x, points[i].y);
            //    glVertex2f(points[i + 1].x, points[i + 1].y);
                if ((i+1) == ((k+1) * points.size()/ (pow(3, deg - 1)) - 1)) {
                   /* glVertex2f(points[i+1].x, points[i+1].y);
                    glVertex2f(points[i + ((k+1) * points.size()/ (pow(3, deg - 1)) - 1)].x,
                            points[i + ((k+1) * points.size()/ (pow(3, deg - 1)) - 1)].y);*/
                    glBegin(GL_POINTS);
                    glColor3f(1,0,0);
                    glVertex2f(points[i+1].x, points[i+1].y);
                    glEnd();
                }
                if (i == k * points.size()/ (pow(3, deg - 1))) {
                    glBegin(GL_POINTS);
                    glColor3f(0,1,0);
                    glVertex2f(points[i].x, points[i].y);
                    //glVertex2f(points[i + k * points.size()/ (pow(3, deg - 1))].x, points[i + k * points.size()/ (pow(3, deg - 1))].y);
                    glEnd();
                }
        }
     //   glEnd();
    }
}

void GLWidget::setDeg(int par) {
    deg = par;
    update();
}

GLfloat big(GLfloat len);
GLfloat small(GLfloat len);

std::vector < Point > GLWidget::drawFractal(Point A, Point B, Point C, int deg,
                                            std::vector<Point> points, int flag, int flag_2) {


    Point A_1(A.x, A.y, 0);
    Point B_1((0.5 * C.x + A.x) / 1.5, (0.5 * C.y + A.y) / 1.5, 0);
    Point C_1(B.x, B.y, 0);

    Point A_2((C.x + B.x) / 2.0, (C.y + B.y) / 2.0, 0);
    Point B_2((0.5 * C.x + A.x) / 1.5, (0.5 * C.y + A.y) / 1.5, 0);
    Point C_2(B.x, B.y, 0);

    Point A_3((C.x + B.x) / 2.0, (C.y + B.y) / 2.0, 0);
    Point B_3((0.5 * C.x + A.x) / 1.5, (0.5 * C.y + A.y) / 1.5, 0);
    Point C_3(C.x, C.y, 0);

    GLfloat AB_1 = A_1.len(B_1);
    GLfloat BC_1 = B_1.len(C_1);
    GLfloat AC_1 = A_1.len(C_1);

    GLfloat AB_2 = A_2.len(B_2);
    GLfloat BC_2 = B_2.len(C_2);
    GLfloat AC_2 = A_2.len(C_2);

    GLfloat AB_3 = A_2.len(B_3);
    GLfloat BC_3 = B_2.len(C_3);
    GLfloat AC_3 = A_2.len(C_3);

    Point O_1;
    O_1.centerOfInscribedCircle(A_1, B_1, C_1, AB_1, BC_1, AC_1);
    Point O_2;
    O_2.centerOfInscribedCircle(A_2, B_2, C_2, AB_2, BC_2, AC_2);
    Point O_3;
    O_3.centerOfInscribedCircle(A_3, B_3, C_3, AB_3, BC_3, AC_3);


    glBegin(GL_LINE_LOOP);
        glColor3f(0,0,1);
        glVertex2f(A.x, A.y);
        glVertex2f(B.x, B.y);
        glVertex2f(C.x, C.y);
    glEnd();



    glBegin(GL_LINE_LOOP);
        glColor3f(0,0,1);
        glVertex2f(B.x, B.y);
        glVertex2f((0.5 * C.x + A.x) / 1.5, (0.5 * C.y + A.y) / 1.5);
        glVertex2f((C.x + B.x) / 2.0, (C.y + B.y) / 2.0);
    glEnd();


    if (deg > 1) {
        points = drawFractal(A_1, B_1, C_1, deg-1, points, 0, 0);
        points = drawFractal(A_2, B_2, C_2, deg-1, points, 1, 0);
        points = drawFractal(A_3, B_3, C_3, deg-1, points, 2, 0);
     }
    if (deg == 1) {
     /*   glBegin(GL_POINTS);
            glColor3f(1,1,1);
            glVertex2f(O_2.x, O_2.y);
            glVertex2f(O_1.x, O_1.y);
            glVertex2f(O_2.x, O_2.y);
            glVertex2f(O_3.x, O_3.y);
        glEnd();
*/

        points.push_back(O_1);
        points.push_back(O_2);
        points.push_back(O_3);
        return points;
    }
    return points ;
}

void GLWidget::drawBridge(Point l, Point lc, Point rc, Point r, int flag) {
    glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex2f(l.x, l.y);
        glVertex2f(rc.x, rc.y);
        glVertex2f(lc.x, lc.y);
        glVertex2f(r.x, r.y);
    glEnd();
}


GLfloat big(GLfloat len) {
    return std::sqrt(3) * len / 2;
}

GLfloat small(GLfloat len) {
    return len / 2;
}
