#include "Segment.h"

#include <istream>
#include <ostream>
#include <stdexcept>

Segment::Segment(const Point& leftPoint, const Point& rightPoint)
    : leftPoint(leftPoint), rightPoint(rightPoint.getX(), leftPoint.getY())
{
    if (rightPoint.getX() < leftPoint.getX())
    {
        throw std::invalid_argument("Абсцисса правой точки меньше абсциссы левой");
    }
}

Point Segment::getLeftPoint() const
{
    return leftPoint;
}

Point Segment::getRightPoint() const
{
    return rightPoint;
}

double Segment::getY(const double x) const
{
    if (x < leftPoint.getX() || x > rightPoint.getX())
    {
        throw std::out_of_range("Абсцисса находится вне отрезка");
    }

    return leftPoint.getY();
}

Segment Segment::Read(std::istream& input)
{
    Point left;
    Point right;

    if (!(input >> left >> right))
    {
        throw std::runtime_error("Не удалось прочитать две точки отрезка");
    }

    return Segment(left, right);
}

std::ostream& operator<<(std::ostream& output, const Segment& segment)
{
    return output << '[' << segment.leftPoint << "; " << segment.rightPoint << ']';
}