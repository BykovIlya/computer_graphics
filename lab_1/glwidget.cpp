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
   /* glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);*/
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
    glBegin(type);
        for (int i = 0; i < n; i++) {
            float angle = 2 * 3.14 * i / (n);
            float x_ = (( -0.2 + cos(angle) * 0.8 + x));
            float y_ = (( -0.1 + sin(angle) * 0.8 + y));
            glColor3f((float)1/i,(float)2/i,(float)3/i);
            glVertex2f(x_, y_);
        }
    glEnd();
}

void GLWidget::paintFigure(int name) {
//    makeCurrent();
   // QMessageBox::information(this, "ho-ho", arr[name]);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    if (name == 0) {
    glBegin(GL_POINTS);
        glVertex2f(-0.3,0.8);
        glVertex2f(0.0,0.8);
        glVertex2f(0.3,0.8);
    glEnd();
  } else if (name == 1 ) {
    glBegin(GL_LINES);
      glVertex2f(-0.3,0.6);
      glVertex2f(0.3,0.6);
      glVertex2f(-0.6,0.2);
      glVertex2f(0.6,0.2);
      glVertex2f(-0.6,-0.2);
      glVertex2f(0.6,-0.2);
      glEnd();
    } else if (name == 2 ) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.3,0.6);
    glVertex2f(0.3,0.6);
    glVertex2f(-0.6,0.2);
    glVertex2f(0.6,0.2);
    glVertex2f(-0.6,-0.2);
    glVertex2f(0.6,-0.2);
      glEnd();
    } else if (name == 3 ) {
      glBegin(GL_LINE_LOOP);
      glVertex2f(-0.3,0.6);
      glVertex2f(0.3,0.6);
      glVertex2f(-0.6,0.2);
      glVertex2f(0.6,0.2);
      glVertex2f(-0.6,-0.2);
      glVertex2f(0.6,0.);
      glEnd();
    } else if (name == 4 ) {
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f( 0.0,  0.5, 0);
    glEnd();
    } else if (name == 5 ) {
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
      glVertex3f(0.2, 0.2,0.0);
      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.8, 0.2,0.0);
      glVertex3f(0.2, 0.5,0.0);
      glVertex3f(0.8, 0.5,0.0);
      glVertex3f(0.2, 0.8,0.0);
      glVertex3f(0.8, 0.8,0.0);
     glEnd();
    } else if (name == 6 ) {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0.1, 0.1,0.0);
      glVertex3f(0.6, 0.1,0.0);
      glVertex3f(0.8,0.3,0.0);
      glVertex3f(0.6,0.6,0.0);
      glVertex3f(0.1,0.6,0.0);
      glVertex3f(0.0,0.3,0.0);
     glEnd();
    } else if (name == 7 ) {
    glBegin(GL_QUADS);
         glVertex3f(-0.5f, -0.5f,  0.0f );
         glVertex3f(-0.5f,  0.5f,  0.0f );
         glVertex3f( 0.5f,  0.5f,  0.0f );
         glVertex3f( 0.5f, -0.5f,  0.0f );
    glEnd();
    } else if (name == 8 ) {
        glBegin(GL_QUAD_STRIP);
             glVertex3f(-0.5f, -0.5f,  0.0f );
             glVertex3f(0.5f, 0.5f,  0.0f );
             glVertex3f(-0.5f,  0.5f,  0.0f );
             glVertex3f(0.5f, -0.5f,  0.0f );
             glVertex3f( 0.5f,  0.5f,  0.0f );
             glVertex3f(-0.5f, -0.5f,  0.0f );
             glVertex3f( 0.5f, -0.5f,  0.0f );
             glVertex3f(-0.5f, 0.5f,  0.0f );
        glEnd();
    } else if (name == 9 ) {
        glBegin ( GL_POLYGON );
          glVertex2f(-0.5, -0.2);
          glVertex2f(0.0, -1.0);
          glVertex2f(0.4, 0.6);
          glVertex2f(0.5, 0.4);
          glVertex2f(0.3, 0.3);
        glEnd();
    }
}

/*
void GLWidget::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPersive(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0,0,5,0,0,0,0,1,0);
}
*/
