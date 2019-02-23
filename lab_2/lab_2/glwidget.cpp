#include "glwidget.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <vector>
#include <cstdlib>
#include <QDebug>

std::vector<GLenum> arrOfFigures = {GL_POINTS,GL_LINES,GL_LINE_STRIP,GL_LINE_LOOP,GL_TRIANGLES,GL_TRIANGLE_STRIP,GL_TRIANGLE_FAN,GL_QUADS,GL_QUAD_STRIP,GL_POLYGON};

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
    indexOfFigure = 0;
}

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
    draw(0.1, 0.1, arrOfFigures[indexOfFigure]);
}

void GLWidget::draw(float x, float y, GLenum type) {
    int n = 8;
    glPointSize(2);
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

void GLWidget::setFigure(int par) {
    indexOfFigure = par;
    update();
}

void GLWidget::setAlphaIndex(int par) {
    alphaTestIndex = par;
    update();
}

void GLWidget::setAlphaValue(int par) {
    alphaTestValue = par;
    update();
}

void GLWidget::setBlendBegin(int par) {
    blendTestIndexBegin = par;
    update();
}

void GLWidget::setBlendEnd(int par) {
    blendTestIndexEnd = par;
    update();
}

void GLWidget::setX(int par) {
    scissorTestX = par;
    update();
}

void GLWidget::setY(int par) {
    scissorTestY = par;
    update();
}

void GLWidget::setW(int par) {
    scissorTestW = par;
    update();
}

void GLWidget::setH(int par) {
    scissorTestH = par;
    update();
}
