#ifndef POINT_H
#define POINT_H

class Point {
public:
    float x, y;


    Point() {
        x = 0;
        y = 0;
    }

    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }

    const Point & operator= (const Point &rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }

    float getX() {
        return this->x;
    }

    float getY() {
        return this->y;
    }
};

#endif // POINT_H
