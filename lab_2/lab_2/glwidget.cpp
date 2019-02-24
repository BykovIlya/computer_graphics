#include "glwidget.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <vector>
#include <cstdlib>
#include <QDebug>

std::vector<GLenum> arrOfFigures = {GL_POINTS,GL_LINES,GL_LINE_STRIP,GL_LINE_LOOP,GL_TRIANGLES,GL_TRIANGLE_STRIP,
                                    GL_TRIANGLE_FAN,GL_QUADS,GL_QUAD_STRIP,GL_POLYGON, GL_CCW};

std::vector<GLenum> opacityTests = {GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL,
                                          GL_ALWAYS};

std::vector<GLenum> blendTests = {GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
                                       GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
                                  GL_SRC_ALPHA_SATURATE};

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
    indexOfFigure = 0;
}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0,0,0,0);
}


void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    start();
}

void GLWidget::start() {
    switch (filter) {
    case 1:
        glEnable(GL_ALPHA_TEST);
        opacityTest();
        draw(0.1, 0.1, indexOfFigure);
        glDisable(GL_ALPHA_TEST);
        break;
    case 2:
        glEnable(GL_BLEND);
        blendTest();
        draw(0.1, 0.1, indexOfFigure);
        glDisable(GL_BLEND);
        break;
    case 3:
        glEnable(GL_SCISSOR_TEST);
        scissorTest();
        draw(0.1, 0.1, indexOfFigure);
        glDisable(GL_SCISSOR_TEST);
        break;
    case 4:
        glEnable(GL_ALPHA_TEST);
        opacityTest();
        glEnable(GL_BLEND);
        blendTest();
        glEnable(GL_SCISSOR_TEST);
        scissorTest();
        draw(0.1, 0.1, indexOfFigure);
        glDisable(GL_SCISSOR_TEST);
        glDisable(GL_BLEND);
        glDisable(GL_ALPHA_TEST);
        break;
    default:
        draw(0.1, 0.1, indexOfFigure);
        break;
    }
}
void GLWidget::draw(float x, float y, int ind) {
    if (ind == arrOfFigures.size() - 1) {
        GLfloat theta;
        GLfloat pi     = acos(-1.0);
        GLfloat radius = 0.4f;
        GLfloat step   = 1.0f;

        glBegin(GL_TRIANGLE_FAN);
        for(GLfloat a = 0.0f; a < 360.0f; a += step) {
            theta = 2.0f * pi * a / 180.0f;
            glColor4f(a/360, 0, 0, a/360);
            glVertex3f(radius * cos(theta)-0.3, radius * sin(theta)-0.3, 0.0f);
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        for(GLfloat a = 0.0f; a < 360.0f; a += step) {
            theta = 2.0f * pi * a / 180.0f;
            glColor4f(0, a/360, 0,  a/360);
            glVertex3f(radius * cos(theta), radius * sin(theta)+0.1, 0.0f);
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        for(GLfloat a = 0.0f; a < 360.0f; a += step) {
            theta = 2.0f * pi * a / 180.0f;
            glColor4f(0, 0, a/360,  a/360);
            glVertex3f(radius * cos(theta)+0.3, radius * sin(theta)-0.3, 0.0f);
        }
        glEnd();
    } else {
        int n = 12;
        glPointSize(3);
        glBegin(arrOfFigures[ind]);
            for (int i = 0; i < n; i++) {
                float angle = 2 * 3.14 * i / (n);
                float x_ = (( -0.2 + cos(angle) * 0.8 + x));
                float y_ = (( -0.1 + sin(angle) * 0.8 + y));
                glColor3f((float)1/(i+1),(float)2/(i+1),(float)3/(i+1));
                glVertex2f(x_, y_);
            }
        glEnd();
    }
}

void GLWidget::setFilter(int par) {
    qDebug() << par;
    filter = par;
    update();
}
void GLWidget::setFigure(int par) {
    indexOfFigure = par;
    update();
}

void GLWidget::setAlphaIndex(int par) {
    alphaTestIndex = par;
    update();
}

void GLWidget::setAlphaValue(double par) {
    alphaTestValue = (double) par / 100;
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

void GLWidget::setX(double par) {
    scissorTestX = par;
    update();
}

void GLWidget::setY(double par) {
    scissorTestY = par;
    update();
}

void GLWidget::setW(double par) {
    scissorTestW = par;
    update();
}

void GLWidget::setH(double par) {
    scissorTestH = par;
    update();
}

void GLWidget::opacityTest() {
    glAlphaFunc(opacityTests[alphaTestIndex], alphaTestValue);
}

void GLWidget::blendTest() {
    glBlendFunc(blendTests[blendTestIndexBegin], blendTests[blendTestIndexEnd]);
}

void GLWidget::scissorTest() {
     glScissor(scissorTestX, scissorTestY, scissorTestW, scissorTestH);
}
