#pragma once

#include <iosfwd>

/**
 * @brief Декартова точка на плоскости.
 */
class Point
{
private:
    double x;
    double y;

public:
    /**
     * @brief Создаёт точку с заданными координатами.
     * @param x Абсцисса.
     * @param y Ордината.
     */
    Point(const double x = 0.0, const double y = 0.0);

    /** @return Абсцисса точки. */
    double getX() const;
    /** @return Ордината точки. */
    double getY() const;

    /** @brief Сравнивает точки с учётом допуска для вещественных чисел. */
    bool operator==(const Point& other) const;
    /** @brief Проверяет неравенство точек. */
    bool operator!=(const Point& other) const;

    /** @brief Записывает координаты точки как x пробел y. */
    friend std::ostream& operator<<(std::ostream& output, const Point& point);
    /** @brief Читает координаты точки как x пробел y. */
    friend std::istream& operator>>(std::istream& input, Point& point);
};
