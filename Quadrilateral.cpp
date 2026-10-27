#include <cmath>
#include "Quadrilateral.h"
#include <algorithm>

Quadrilateral::Quadrilateral(Point a, Point b, Point c, Point d)
    : points {a, b, c, d}
{
}

double Quadrilateral::hypotenuse(Point a, Point b) const
{
    double dx = b.getX() - a.getX();
    double dy = b.getY() - a.getY();

    return std::hypot(dx, dy);
}

void Quadrilateral::print() const
{
    for(int i=0;i<4;i=i+1)
    {
        points[i].print();
    }
}

bool Quadrilateral::isConvex() const
{
    bool positive = false;
    bool negative = false;

    for(int i=0;i<4;i=i+1)
    {
        Point a=points[i];
        Point b=points[(i+1)%4];
        Point c=points[(i+2)%4];

        double check=(b.getX()-a.getX())*(c.getY()-b.getY())-(b.getY()-a.getY())*(c.getX()-b.getX());

        if(std::abs(check)<1e-9)
        {
            return false;
        }
        if (check>0)
        {
            positive=true;
        }
        if(check<0)
        {
            negative=true;
        }
    }
    if(positive && negative)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Quadrilateral::canDescribe() const
{
    if (!isConvex())
    {
        return false;
    }

    double ab = hypotenuse(points[0], points[1]);
    double bc = hypotenuse(points[1], points[2]);
    double cd = hypotenuse(points[2], points[3]);
    double da = hypotenuse(points[3], points[0]);

    double acDiag = hypotenuse(points[0], points[2]);
    double bdDiag = hypotenuse(points[1], points[3]);

    double left = acDiag * bdDiag;
    double right = ab * cd + bc * da;

    double epsilon = 1e-9 * std::max(left, right);

    if (std::abs(left - right) <= epsilon)
    {
        return true;
    }
    else
    {
        return false;
    }
}