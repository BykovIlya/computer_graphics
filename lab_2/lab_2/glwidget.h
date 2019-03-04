#ifndef GLWIDGET_H
#define GLWIDGET_H
//#include <GL/freeglut.h>
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
    void draw(float, float, int);
    void opacityTest();
    void blendTest();
    void scissorTest();
    void start();

    int filter = 0;
    int indexOfFigure;
    int alphaTestIndex = 0;
    double alphaTestValue = 0;
    int blendTestIndexBegin = 0;
    int blendTestIndexEnd = 0;
    double scissorTestX = 0;
    double scissorTestY = 0;
    double scissorTestW = 550;
    double scissorTestH = 450;

public slots:
    void setFilter(int);
    void setFigure(int);
    void setAlphaIndex(int);
    void setAlphaValue(double);
    void setBlendBegin(int);
    void setBlendEnd(int);
    void setX(double);
    void setY(double);
    void setW(double);
    void setH(double);

};


#endif // GLWIDGET_H
