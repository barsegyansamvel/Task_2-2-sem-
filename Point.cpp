#include "Point.h"
#include <iostream>

Point::Point(double p_x, double p_y)
{
    x=p_x;
    y=p_y;
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

void Point::print() const
{
    std::cout << "x:" << x << "\t y: " << y << std::endl;
}