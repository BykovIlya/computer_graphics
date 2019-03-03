#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <cmath>

struct Point {
    double x;
    double y;
    Point(double, double);
    double len(Point);
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
    std::vector < Point > drawFractal(Point, Point, Point, int, std::vector < Point >, int flag);
public slots:
    void setDeg(int);
};

#endif // GLWIDGET_H
