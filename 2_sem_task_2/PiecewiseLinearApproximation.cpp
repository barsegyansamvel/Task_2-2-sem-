#include "PiecewiseLinearApproximation.h"

#include <algorithm>
#include <istream>
#include <iterator>
#include <stdexcept>

PiecewiseLinearApproximation::PiecewiseLinearApproximation(
    const std::vector<Point>& points
) : points(points)
{
    ValidatePoints();
}

PiecewiseLinearApproximation::PiecewiseLinearApproximation(
    std::initializer_list<Point> points
) : points(points)
{
    ValidatePoints();
}

void PiecewiseLinearApproximation::ValidatePoints() const
{
    if (points.size() < 2)
    {
        throw std::invalid_argument(
            "Для аппроксимации необходимо задать минимум две точки"
        );
    }

    for (std::size_t i = 1; i < points.size(); ++i)
    {
        if (points[i].getX() <= points[i - 1].getX())
        {
            throw std::invalid_argument(
                "Абсциссы точек должны строго возрастать"
            );
        }
    }
}

double PiecewiseLinearApproximation::getY(const double x) const
{
    if (x < points.front().getX() || x > points.back().getX())
    {
        throw std::out_of_range("Абсцисса находится вне диапазона точек");
    }

    const auto next = std::upper_bound(
        points.begin(), points.end(), x,
        [](const double value, const Point& point)
        {
            return value < point.getX();
        }
    );

    if (next == points.end())
    {
        return points.back().getY();
    }

    return std::prev(next)->getY();
}

void PiecewiseLinearApproximation::AddPoint(const Point& point)
{
    if (point.getX() <= points.back().getX())
    {
        throw std::invalid_argument(
            "Добавляемая точка должна иметь большую абсциссу"
        );
    }
    points.push_back(point);
}

const std::vector<Point>& PiecewiseLinearApproximation::GetPoints() const
{
    return points;
}

std::vector<Point> PiecewiseLinearApproximation::ReadPoints(
    std::istream& input,
    const std::size_t count
)
{
    if (count < 2)
    {
        throw std::invalid_argument(
            "Необходимо прочитать минимум две точки"
        );
    }

    std::vector<Point> result;
    result.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        Point point;
        if (!(input >> point))
        {
            throw std::runtime_error("Не удалось прочитать точку");
        }
        result.push_back(point);
    }

    return result;
}
