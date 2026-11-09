#include "Segment.h"

#include <istream>
#include <ostream>

Segment::Segment(const Point& leftPoint, const Point& rightPoint)
    : approximation(std::vector<Point>{
        leftPoint,
        Point(rightPoint.getX(), leftPoint.getY())
    })
{
}

Point Segment::getLeftPoint() const
{
    return approximation.GetPoints().front();
}

Point Segment::getRightPoint() const
{
    return approximation.GetPoints().back();
}

double Segment::getY(const double x) const
{
    return approximation.getY(x);
}

Segment Segment::Read(std::istream& input)
{
    const std::vector<Point> points =
        PiecewiseLinearApproximation::ReadPoints(input, 2);
    return Segment(points[0], points[1]);
}

std::ostream& operator<<(std::ostream& output, const Segment& segment)
{
    return output << "[" << segment.getLeftPoint()
                  << "; " << segment.getRightPoint() << "]";
}
