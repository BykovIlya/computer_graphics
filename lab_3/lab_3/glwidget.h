#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <cmath>

struct Point {
    GLfloat x;
    GLfloat y;
    bool f;
    Point();
    Point(GLfloat, GLfloat, bool);
    GLfloat len(Point);
    Point centerOfInscribedCircle(Point, Point, Point, GLfloat, GLfloat, GLfloat);
    void operator = (const Point &);
};

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void initializeGL();
    void paintGL() override;
    int deg = 1;
    std::vector < Point > drawFractal(Point, Point, Point, int, std::vector < Point >, int , int);
    void drawBridge(Point, Point, Point, Point, int);
public slots:
    void setDeg(int);
};

#endif // GLWIDGET_H
