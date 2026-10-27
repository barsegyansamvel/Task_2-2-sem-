#pragma once
#include "Point.h"

class Quadrilateral
{
private:
    Point points[4];
    double hypotenuse(Point a, Point b) const;

public:
    Quadrilateral(const Point a, const Point b,  const Point c,  const Point d);

    void print() const;

    bool isConvex() const;

    bool canDescribe() const;
};
