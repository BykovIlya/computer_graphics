#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class MainWindow;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void initializeGL();
    void paintGL() override;
    void draw(float, float, GLenum);
};

#endif // GLWIDGET_H
