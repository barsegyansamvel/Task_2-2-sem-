#pragma once

class Point
{
private:
    double x;
    double y;

public:
    Point(const double p_x, const double p_y);

    double getX() const;
    double getY() const;

    void print() const;
};
