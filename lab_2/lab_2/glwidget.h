#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <GL/freeglut.h>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void initializeGL();
    void paintGL() override;
    void draw(float, float, GLenum);

    int indexOfFigure;
    int alphaTestIndex;
    int alphaTestValue;
    int blendTestIndexBegin;
    int blendTestIndexEnd;
    int scissorTestX;
    int scissorTestY;
    int scissorTestW;
    int scissorTestH;

public slots:
    void setFigure(int);
    void setAlphaIndex(int);
    void setAlphaValue(int);
    void setBlendBegin(int);
    void setBlendEnd(int);
    void setX(int);
    void setY(int);
    void setW(int);
    void setH(int);

};


#endif // GLWIDGET_H
