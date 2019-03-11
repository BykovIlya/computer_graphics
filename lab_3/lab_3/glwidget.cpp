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
    Point C(-0.9 + std::sqrt(3.0),  -0.9000,0);        // угол 30 градусов
    std::vector < Point > points;
    // 108 126 135 207
    // deg = 6 => 99 135 153 531 621 639 693
    points = drawFractal(A, B, C, deg, points, 0, 0);
   /* glBegin(GL_LINES);
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
            //15 69 (3 33)
            if ((i + 1) % k == 0 && (i + 1) % 2 != 0 && (i + 1) % 5 != 0 && (i + 1) % 69 != 0 && points[i].f == 0 && ((i <= points.size()/3) || (i >= points.size() * 2 / 3-1))) {
                glVertex2f(points[i].x, points[i].y);
                glVertex2f(points[i + k].x, points[i + k].y);
                points[i].f = 1;
                //12 24 66 72 (4 8 22 24)
            } else if ((i + 1) % k == 0 && (i + 1) % 2 == 0 && (i + 1) % 12 == 0 && (i + 1) % 36 != 0
                       && points[i].f == 0 && ((i <= points.size()/3) || (i >= points.size() * 2 / 3))) {
                glVertex2f(points[i-k + 1].x, points[i-k + 1].y);
                glVertex2f(points[i + k -2].x, points[i + k -2].y);
                points[i].f = 1;
                // 36 (12)
            } else if ((i + 1) % k == 0 && (i + 1) % 2 == 0 && (i + 1) % 36 == 0 && points[i].f == 0 && ((i > points.size()/3 + 1) && (i < points.size() * 2 / 3 - 1))) {
                glVertex2f(points[i].x, points[i].y);
                glVertex2f(points[i + k].x, points[i + k].y);
                points[i].f = 1;
                // 39 45 (13 15)
            } else if ((i + 1) % k == 0 && (i + 1) % 2 != 0 && (i + 1) % 39 != 0 && (i + 1) % 45 != 0  && points[i].f == 0 && ((i > points.size()/3 + 1) && (i < points.size() * 2 / 3 ))) {
                glVertex2f(points[i-k + 1].x, points[i-k + 1].y);
                glVertex2f(points[i + k -2].x, points[i + k -2].y);
                points[i].f = 1;
            }
        }
        k = k / 3;
    }
    glEnd();*/


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

    std::vector < Point > K_1, K_2, K_3;
    K_1 = {Point(0,0,0), Point(0,0,0)};
    K_2 = {Point(0,0,0), Point(0,0,0)};
    K_3 = {Point(0,0,0), Point(0,0,0)};

    if (flag_2 == 1) {
        if (flag == 0) {
            std::vector < Point > ret = {O_1, O_3};
            return ret;
        } else if (flag == 1) {
            std::vector < Point > ret = {O_1, O_3};
            return ret;
        } else {
            std::vector < Point > ret = {O_1, O_3};
            return ret;
        }
    /*    double AB = A.len(B);
        double AC = A.len(C);
        double BC = B.len(C);
        Point O;
        O.centerOfInscribedCircle(A, B, C, AB, BC, AC);
        std::vector < Point > ret = {O, O};
        return ret;*/
        //return ret;
    } else {
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
        glPointSize(5);
        glBegin(GL_POINTS);
            glColor3f(1,1,1);
            glVertex2f(A.x, A.y);
            glColor3f(0,1,0);
            glVertex2f(B.x, B.y);
            glColor3f(1,0,0);
            glVertex2f(C.x, C.y);
        glEnd();

        if (deg > 1) {
            K_1 = drawFractal(A_1, B_1, C_1, deg-1, points, 0, 0);
            K_2 = drawFractal(A_2, B_2, C_2, deg-1, points, 1, 0);
            K_3 = drawFractal(A_3, B_3, C_3, deg-1, points, 2, 0);
         }

        std::vector < Point > bridge;
      //  drawBridge(K_1[1], K_2[0], K_2[1], K_3[0]);
        if (deg == 1) {
            glBegin(GL_LINES);
                glColor3f(1,1,1);
                glVertex2f(O_2.x, O_2.y);
                glVertex2f(O_1.x, O_1.y);
                glVertex2f(O_2.x, O_2.y);
                glVertex2f(O_3.x, O_3.y);
            glEnd();
            GLfloat len = O_1.len(O_2);
            //double len_X = O_1.len(A);
            //if (flag == 1) {
                if ((A.y == C.y) && (A.x == B.x) && (B.y > A.y) && (A.x > C.x)) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        if (fabs(O_1.y + 0.90000f - small(len)) < precision ) {
                            glVertex2f(O_1.x, O_1.y);
                            glVertex2f(O_1.x + len, O_1.y);
                        }
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x - small(len), O_3.y + big(len));
                    glEnd();
                } /*else if((B.x == C.x) && (A.x > B.x) && (B.y > C.y)) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x + big(len) , O_1.y - small(len));
                        //glVertex2f(O_3.x, O_3.y);
                        //glVertex2f(O_3.x - len, O_3.y);
                    glEnd();
                } */else if((B.x == C.x) && (A.x < B.x) && (B.y > C.y)) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        //glVertex2f(O_1.x, O_1.y);
                        //glVertex2f(O_1.x + big(len) , O_1.y - small(len));
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x + len, O_3.y);
                    glEnd();
                }/*else if (A.x == B.x && A.y == C.y && C.x > B.x && B.y > C.y && ((A.x) != -0.9L)) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x - len, O_1.y);
                        //glVertex2f(O_3.x, O_3.y);
                        //glVertex2f(O_3.x + len / 2.0, O_3.y + sqrt3() * len / 2.0);
                    glEnd();
                } */else if (C.x < A.x && A.x < B.x && A.y < B.y && B.y < C.y) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x - big(len), O_3.y - small(len));
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x + small(len), O_1.y - big(len));
                    glEnd();
                } else if (B.y < A.y && A.y < C.y && C.x < B.x && B.x < A.x) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x - big(len), O_3.y - small(len));
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x + big(len), O_1.y - small(len));
                    glEnd();
                } else if (C.y < B.y && B.y < A.y && B.x < A.x && A.x < C.x) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x - small(len), O_3.y - big(len));
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x - small(len), O_1.y + big(len));
                    glEnd();
                } else if (C.y > B.y && B.y == A.y && B.x < A.x && A.x == C.x) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x - small(len), O_3.y - big(len));
                        //glVertex2f(O_1.x, O_1.y);
                        //glVertex2f(O_1.x - len / 2.0, O_1.y + sqrt3() * len / 2.0);
                    glEnd();
                } else if (B.y == C.y && C.x > B.x && A.y < B.y && B.x < A.x && A.x < C.x) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x, O_3.y +len);
                        //glVertex2f(O_1.x, O_1.y);
                        //glVertex2f(O_1.x - big(len), O_1.y - small(len));
                    glEnd();
                } else if (A.x < B.x && B.x < C.x && B.y < A.y && A.y < C.y) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x + big(len), O_3.y - small(len));
                        //glVertex2f(O_1.x, O_1.y);
                        //glVertex2f(O_1.x - big(len), O_1.y - small(len));
                    glEnd();
                } else if (A.y == B.y && A.x == C.x && B.x > A.x && B.y > C.y) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                  //      glVertex2f(O_3.x, O_3.y);
                  //      glVertex2f(O_3.x + sqrt3() * len / 2.0, O_3.y - len / 2.0);
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x, O_1.y + len);
                    glEnd();
                } else if (A.y == B.y && A.x == C.x && B.x < A.x && B.y > C.y) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x + len, O_3.y);
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x, O_1.y + len);
                    glEnd();
                } /*else if (C.x < A.x && A.x < B.x && C.y < B.y && B.y < A.y) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x + small(len), O_3.y - big(len));
                    glEnd();
                } */else if (A.x < B.x && B.x == C.x && B.y < A.y && A.y < C.y) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x - big(len), O_3.y + small(len));
                     //   glVertex2f(O_1.x, O_1.y);
                     //   glVertex2f(O_1.x - len / 2.0, O_1.y - sqrt3() * len / 2.0);
                    glEnd();
                } else if (B.x < A.x && (A.x == C.x) && (B.y == A.y)) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_3.x, O_3.y);
                        glVertex2f(O_3.x + len, O_3.y);
                    glEnd();
                }
                /* else if (A.x == C.x) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x, O_1.y - O_1.len(O_2));
                    glEnd();
                } else if ((B.x == C.x && (A.x < B.x)) || ((B.x < A.x) && (A.x < C.x) && (B.y != C.y))
                           || ((C.x < A.x) && (A.x < B.x) && (B.y != C.y))) {
                    glBegin(GL_LINES);
                        glColor3f(1,1,1);
                        glVertex2f(O_1.x, O_1.y);
                        glVertex2f(O_1.x  - (O_1.len(O_2) / 2.0), O_1.y + sqrt(3) * O_1.len(O_2) / 2.0);
                    glEnd();
                }*/
            //}
       //     K_1 = drawFractal(A, B, C, deg-1, points, 0, 1);
       //     K_2 = drawFractal(A, B, C, deg-1, points, 1, 1);
       //     K_3 = drawFractal(A, B, C, deg-1, points, 2, 1);
           // drawBridge(K_1[1], K_2[0], K_2[1], K_3[0], 1);
       /*     for (int i = 0; i < 2; i++) {
                qDebug() << "k_1: " << K_1[i].x << " : " << K_1[i].y << "\n";
                qDebug() << "k_2: " << K_2[i].x << " : " << K_2[i].y << "\n";
                qDebug() << "k_3: " << K_3[i].x << " : " << K_3[i].y << "\n";
            }*/
           // drawBridge(K_1[1], K_2[0], K_2[1], K_3[0]);
            /*if (flag == 0 && deg == 1) {
                bridge = {Point(0,0,0), O_3};
                return bridge;
            } else if (flag == 1 && deg == 1) {
                bridge = {O_3, O_1};
                return bridge;
            } else if (flag == 2 && deg == 1){
                bridge = {O_1, Point(0,0,0)};
                return bridge;
            }*/
        }
        std::vector < Point > ret = {O_1, O_3};
        return ret;
    }
  /*  points.push_back(O_1);
    points.push_back(O_2);
    points.push_back(O_3);*/

  //  if (deg == 1) {
       // if (flag == 0) {
    //        glBegin(GL_LINES);
      //          glColor3f(1,1,1);
        //        glVertex2f(O_2.x, O_2.y);
          //      glVertex2f(O_1.x, O_1.y);
           //     glVertex2f(O_2.x, O_2.y);
           //     glVertex2f(O_3.x, O_3.y);
          //  glEnd();
         //   points.push_back(O_1);
         //   points.push_back(O_2);
         //   points.push_back(O_3);
       // } else {
           /*  glBegin(GL_LINES);
                glColor3f(1,1,1);
                glVertex2f(O_2.x, O_2.y);
                glVertex2f(O_1.x, O_1.y);
                glVertex2f(O_2.x, O_2.y);
                glVertex2f(O_3.x, O_3.y);

                glVertex2f(O_1.x, O_1.y);
                glVertex2f(O_1.x, O_1.y);

                glVertex2f(O_3.x, O_3.y);
                glVertex2f(O_3.x, O_3.y);

            glEnd();*/
  /*          points.push_back(O_1);
            points.push_back(O_2);
            points.push_back(O_3);

            points.push_back(Point(O_3.x, O_3.y));
            points.push_back(Point(O_2.x, O_2.y));
            points.push_back(Point(O_1.x, O_1.y));*/
    //    }
//        return points;
   // }


 //   return points;
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
