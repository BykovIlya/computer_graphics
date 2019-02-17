#include "glwidget.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <vector>
#include <cstdlib>

int flag = -1;

std::vector<GLenum> arrOfFigures = {GL_POINTS,GL_LINES,GL_LINE_STRIP,GL_LINE_LOOP,GL_TRIANGLES,GL_TRIANGLE_STRIP,GL_TRIANGLE_FAN,GL_QUADS,GL_QUAD_STRIP,GL_POLYGON};
std::vector<QString> arr = {"GL_POINT","GL_LINES","GL_LINE_STRIP","GL_LINE_LOOP","GL_TRIANGLES","GL_TRIANGLE_STRIP","GL_TRIANGLE_FAN","GL_QUADS","GL_QUAD_STRIP","GL_POLYGON"};

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}


void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw(0.1, 0.1, arrOfFigures[flag]);
    flag++;
    if (flag == 10) flag = 0;

}

void GLWidget::draw(float x, float y, GLenum type) {
    int n = 8;
    glPointSize(2);
    //glColor3f((float)2,(float)1,(float)2);
    glBegin(type);
        for (int i = 0; i < n; i++) {
            float angle = 2 * 3.14 * i / (n);
            float x_ = (( -0.2 + cos(angle) * 0.8 + x));
            float y_ = (( -0.1 + sin(angle) * 0.8 + y));
            glColor3f((float)1/(i+1),(float)2/(i+1),(float)3/(i+1));
            glVertex2f(x_, y_);
        }
    glEnd();
}
