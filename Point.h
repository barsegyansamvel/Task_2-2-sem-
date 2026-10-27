#pragma once

class Point
{
private:
    double x;
    double y;

public:
    Point(double p_x, double p_y);

    double getX() const;
    double getY() const;

    void print() const;
};