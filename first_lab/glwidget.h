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
    //void resizeGL(int w, int h);
    void paintGL() override;
    void paintFigure(int);
};

#endif // GLWIDGET_H
