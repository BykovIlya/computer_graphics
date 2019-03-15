#include "glwidget.h"
#include "mainwindow.h"
#include <vector>
#include <QDebug>

Point::Point() {
    this->x = 0.0;
    this->y = 0.0L;
    this->f = false;
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
    Point A(-0.9000, -0.4000 ,0);        // прямой угол
    Point B(-0.9000,  0.50 ,0);        // угол 60 градусов
    Point C(-0.9 + A.len(B) * sqrt(3.0),  -0.4000,0);        // угол 30 градусов
    std::vector < Point > points;
    points = drawFractal(A, B, C, deg, points);
    std::vector < Point > redPoints;
    std::vector < Point > greenPoints;

    for (size_t k = 0; k < pow(3, deg - 1); k++) {
        for (size_t i = k * points.size() / (pow(3, deg - 1));
             i < (k + 1) * points.size() / (pow(3, deg - 1)) - 1; i++) {
             glBegin(GL_LINES);
                glColor3f(1, 1, 1);
                glVertex2f(points[i].x, points[i].y);
                glVertex2f(points[i + 1].x, points[i + 1].y);
            glEnd();
            if ((i + 1) == ((k + 1) * points.size() / (pow(3, deg - 1)) - 1)) {
                redPoints.push_back(points[i + 1]);
            }
            if (i == k * points.size()/ (pow(3, deg - 1))) {
                greenPoints.push_back(points[i]);
            }
        }
    }
    if (deg >= 3) {
        for (size_t i = 9 * 1 - 1; i < points.size() - 9; i += 9 * 3) {
           glBegin(GL_LINES);
               glColor3f(1, 1, 1);
               glVertex2f(points[i].x, points[i].y);
               glVertex2f(points[i + 9].x, points[i + 9].y);
               glVertex2f(points[i + 1].x, points[i + 1].y);
               glVertex2f(points[i + 10].x, points[i + 10].y);
           glEnd();
        }
    }
    if (deg >= 4) {
        for (size_t d = 4; d <= deg; d++) {
            for (size_t i = (int)pow(3, d - 1) - 1; i < points.size() - (int)pow(3, d - 1) + 1; i += (int)pow(3, d)) {
                glBegin(GL_LINES);
                    glColor3f(1, 1, 1);
                    glVertex2f(points[i].x, points[i].y);
                    glVertex2f(points[i + (int)pow(3, d - 1)].x, points[i + (int)pow(3, d - 1)].y);
                    glVertex2f(points[i + 1].x, points[i + 1].y);
                    glVertex2f(points[i + (int)pow(3, d - 1) + 1].x, points[i + (int)pow(3, d - 1) + 1].y);
                glEnd();
            }
        }
    }

    if (deg == 2) {
        glBegin(GL_LINES);
            glVertex2f(greenPoints[1].x, greenPoints[1].y);
            glVertex2f(greenPoints[2].x, greenPoints[2].y);
            glVertex2f(redPoints[0].x, redPoints[0].y);
            glVertex2f(redPoints[1].x, redPoints[1].y);
        glEnd();
    } else {
        for (size_t i = 1; i < greenPoints.size() - 1; i++) {
            if (i % 2 != 0) {
                glBegin(GL_LINES);
                   glVertex2f(greenPoints[i].x, greenPoints[i].y);
                   glVertex2f(greenPoints[i + 1].x, greenPoints[i + 1].y);
                   if (i < greenPoints.size() - 4) {
                        glVertex2f(greenPoints[i + 3].x, greenPoints[i + 3].y);
                        glVertex2f(greenPoints[i + 4].x, greenPoints[i + 4].y);
                   }
                glEnd();
                i+=4;
            }
        }

        for (size_t i = 0; i < redPoints.size() - 1; i++) {
            if (i % 2 == 0) {
                glBegin(GL_LINES);
                    glVertex2f(redPoints[i].x, redPoints[i].y);
                    glVertex2f(redPoints[i + 1].x, redPoints[i + 1].y);
                    if (i < redPoints.size() - 5) {
                        glVertex2f(redPoints[i + 3].x, redPoints[i + 3].y);
                        glVertex2f(redPoints[i + 4].x, redPoints[i + 4].y);
                    }
                glEnd();
                i+=4;
            }
        }
    }
}

void GLWidget::setDeg(int par) {
    deg = par;
    update();
}

std::vector < Point > GLWidget::drawFractal(Point A, Point B, Point C, int deg,
                                            std::vector<Point> points) {

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

    GLfloat AB_3 = A_3.len(B_3);
    GLfloat BC_3 = B_3.len(C_3);
    GLfloat AC_3 = A_3.len(C_3);

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
        points = drawFractal(A_1, B_1, C_1, deg-1, points);
        points = drawFractal(A_2, B_2, C_2, deg-1, points);
        points = drawFractal(A_3, B_3, C_3, deg-1, points);
     }
    if (deg == 1) {
        points.push_back(O_1);
        points.push_back(O_2);
        points.push_back(O_3);
        return points;
    }
    return points ;
}

