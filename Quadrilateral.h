#pragma once
#include "Point.h"

class Quadrilateral
{
private:
    Point points[4];
    double hypotenuse(Point a, Point b) const;

public:
    Quadrilateral(Point a, Point b, Point c, Point d);

    void print() const;

    bool isConvex() const;

    bool canDescribe() const;
};