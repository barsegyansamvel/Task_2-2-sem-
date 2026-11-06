#include "Point.h"

#include <cfloat>
#include <cmath>
#include <istream>
#include <ostream>

Point::Point(const double x, const double y)
    : x(x), y(y)
{
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

bool Point::operator==(const Point& other) const
{
    return std::abs(x - other.x) <= DBL_EPSILON
        && std::abs(y - other.y) <= DBL_EPSILON;
}

bool Point::operator!=(const Point& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& output, const Point& point)
{
    return output << point.x << ' ' << point.y;
}

std::istream& operator>>(std::istream& input, Point& point)
{
    double x;
    double y;

    if (input >> x >> y)
    {
        point = Point(x, y);
    }

    return input;
}
