#include "glwidget.h"
#include "mainwindow.h"
#include <vector>
#include <QDebug>

Point::Point(double x, double y, bool f) {
    this->x = x;
    this->y = y;
    this->f = f;
}

void Point::operator =(const Point& Q) {
    this->x = Q.x;
    this->y = Q.y;
    this->f = Q.f;
}

double Point::len(Point Q) {
    return sqrt((x - Q.x) * (x - Q.x) + (y - Q.y) * (y - Q.y));
}

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
}

GLWidget::~GLWidget() {}
void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0,0,0,0);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Point A(-0.9, -0.9,0);        // прямой угол
    Point B(-0.9, 0.09,0);        // угол 60 градусов
    Point C(0.62, -0.9,0);        // угол 30 градусов
    std::vector < Point > points;
    // 108 126 135 207
    // deg = 6 => 99 135 153 531 621 639 693
    points = drawFractal(A, B, C, deg, points, 0);
    glBegin(GL_LINES);
    for (size_t i = 0; i < points.size() - 1; i++) {
        glColor3f(1,1,1);
        if ((i+1) % 3 != 0) {
            glVertex2f(points[i].x, points[i].y);
            glVertex2f(points[i + 1].x, points[i + 1].y);
        }
    }
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1,1,1);
    int k = points.size() / 3;
    while (k > 2) {
        for (size_t i = 0; i < points.size() - 1; i++) {
            //15 69
            if ((i + 1) % k == 0 && (i + 1) % 2 != 0 && (i + 1) % 5 != 0 && (i + 1) % 69 != 0 && points[i].f == 0 && ((i <= points.size()/3) || (i >= points.size() * 2 / 3-1))) {
                glVertex2f(points[i].x, points[i].y);
                glVertex2f(points[i + k].x, points[i + k].y);
                points[i].f = 1;
                //12 24 66 72
            } else if ((i + 1) % k == 0 && (i + 1) % 2 == 0 && (i + 1) % 2 == 12
                       && (i + 1) % 2 == 24 && (i + 1) % 2 == 66 && (i + 1) % 2 == 72 && points[i].f == 0 && ((i <= points.size()/3) || (i >= points.size() * 2 / 3))) {
                glVertex2f(points[i-k + 1].x, points[i-k + 1].y);
                glVertex2f(points[i + k -2].x, points[i + k -2].y);
                points[i].f = 1;
                // 36
            } else if ((i + 1) % k == 0 && (i + 1) % 2 == 0 && (i + 1) % 36 == 0 && points[i].f == 0 && ((i > points.size()/3 + 1) && (i < points.size() * 2 / 3 - 1))) {
                glVertex2f(points[i].x, points[i].y);
                glVertex2f(points[i + k].x, points[i + k].y);
                points[i].f = 1;
                // 39 51
            } else if ((i + 1) % k == 0 && (i + 1) % 2 != 0 && (i + 1) % 39 != 0 && (i + 1) % 45 != 0  && points[i].f == 0 && ((i > points.size()/3 + 1) && (i < points.size() * 2 / 3 ))) {
                glVertex2f(points[i-k + 1].x, points[i-k + 1].y);
                glVertex2f(points[i + k -2].x, points[i + k -2].y);
                points[i].f = 1;
            }
        }
        k = k / 3;
    }
    glEnd();


        /*else if ((i + 1) % 27 == 0 && (i + 1) % 81 != 0 && (i+1) % 2 != 0  && ((i <= points.size()/3) || (i >= points.size() * 2 / 3))) {
            glVertex2f(points[i].x, points[i].y);
            glVertex2f(points[i + 27].x, points[i + 27].y);
            glVertex2f(points[i + 1].x, points[i + 1].y);
            glVertex2f(points[i + 28].x, points[i + 28].y);
        } else if ((i + 1) % 45 == 0){

        }*/
        //else if ((i+1) % 2 != 0 /*&& (i + 1) % 23 != 0*/ && (i + 1) % 81 != 0 && ((i <= points.size()/3) || (i >= points.size() * 2 / 3))){
          /*  glVertex2f(points[i].x, points[i].y);
            glVertex2f(points[i + 9].x, points[i + 9].y);
            glVertex2f(points[i + 1].x, points[i + 1].y);
            glVertex2f(points[i + 10].x, points[i + 10].y);*/
       // }else if ((i+1) % 2 == 0 && ((i > points.size()/3 + 1) && (i < points.size() * 2 / 3 - 1))){
          /*  glVertex2f(points[i].x, points[i].y);
            glVertex2f(points[i + 9].x, points[i + 9].y);
            glVertex2f(points[i + 1].x, points[i + 1].y);
            glVertex2f(points[i + 10].x, points[i + 10].y);*/
       // }

   // }
   // glEnd();
    /*qDebug() << "Coordinates:\n";
    for (size_t i = 0; i < points.size(); i++) {
        qDebug() << "(" << points[i].x << " , " << points[i].y << ")\n";
    }*/
}

void GLWidget::setDeg(int par) {
    deg = par;
    update();
}

std::vector < Point > GLWidget::drawFractal(Point A, Point B, Point C, int deg, std::vector<Point> points, int flag) {


    Point A_1(A.x, A.y, 0);
    Point B_1((0.5 * C.x + A.x) / 1.5, (0.5 * C.y + A.y) / 1.5, 0);
    Point C_1(B.x, B.y, 0);

    Point A_2((C.x + B.x) / 2.0, (C.y + B.y) / 2.0, 0);
    Point B_2((0.5 * C.x + A.x) / 1.5, (0.5 * C.y + A.y) / 1.5, 0);
    Point C_2(B.x, B.y, 0);

    Point A_3((C.x + B.x) / 2.0, (C.y + B.y) / 2.0, 0);
    Point B_3((0.5 * C.x + A.x) / 1.5, (0.5 * C.y + A.y) / 1.5, 0);
    Point C_3(C.x, C.y, 0);

    double AB_1 = A_1.len(B_1);
    double BC_1 = B_1.len(C_1);
    double AC_1 = A_1.len(C_1);

    double AB_2 = A_2.len(B_2);
    double BC_2 = B_2.len(C_2);
    double AC_2 = A_2.len(C_2);

    double AB_3 = A_2.len(B_3);
    double BC_3 = B_2.len(C_3);
    double AC_3 = A_2.len(C_3);

    Point O_1((AB_1 * C_1.x + BC_1 * A_1.x + AC_1 * B_1.x) / (AB_1 + BC_1 + AC_1),
              (AB_1 * C_1.y + BC_1 * A_1.y + AC_1 * B_1.y) / (AB_1 + BC_1 + AC_1), 0);
    Point O_2((AB_2 * C_2.x + BC_2 * A_2.x + AC_2 * B_2.x) / (AB_2 + BC_2 + AC_2),
              (AB_2 * C_2.y + BC_2 * A_2.y + AC_2 * B_2.y) / (AB_2 + BC_2 + AC_2), 0);
    Point O_3((AB_3 * C_3.x + BC_3 * A_3.x + AC_3 * B_3.x) / (AB_3 + BC_3 + AC_3),
              (AB_3 * C_3.y + BC_3 * A_3.y + AC_3 * B_3.y) / (AB_3 + BC_3 + AC_3), 0);

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

    if (deg == 1) {
        if (flag == 0) {
        /*    glBegin(GL_LINES);
                glColor3f(1,1,1);
                glVertex2f(O_2.x, O_2.y);
                glVertex2f(O_1.x, O_1.y);
                glVertex2f(O_2.x, O_2.y);
                glVertex2f(O_3.x, O_3.y);
            glEnd();*/
            points.push_back(O_1);
            points.push_back(O_2);
            points.push_back(O_3);
        } else {
           /* glBegin(GL_LINES);
                glColor3f(1,1,1);
                glVertex2f(O_2.x, O_2.y);
                glVertex2f(O_1.x, O_1.y);
                glVertex2f(O_2.x, O_2.y);
                glVertex2f(O_3.x, O_3.y);

                glVertex2f(O_1.x, O_1.y);
                glVertex2f(O_1.x, O_1.y);

                glVertex2f(O_3.x, O_3.y);
                glVertex2f(O_3.x, O_3.y);
*/
  //          glEnd();
            points.push_back(O_1);
            points.push_back(O_2);
            points.push_back(O_3);
            /*
            points.push_back(Point(O_3.x, O_3.y));
            points.push_back(Point(O_2.x, O_2.y));
            points.push_back(Point(O_1.x, O_1.y));*/
        }
        return points;
    }

    if (deg > 1) {
        points = drawFractal(A_1, B_1, C_1, deg-1, points, 0);
        points = drawFractal(A_2, B_2, C_2, deg-1, points, 1);
        points = drawFractal(A_3, B_3, C_3, deg-1, points, 0);


    }
    return points;

}
