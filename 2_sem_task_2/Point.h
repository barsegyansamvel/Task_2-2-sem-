#pragma once

#include <iostream>

/**
@brief Декартова точка на плоскости.
*/
class Point
{
private:
    double x;
    double y;

public:
    /**
    @brief Создаёт точку с заданными координатами.
    @param x Абсцисса.
    @param y Ордината.
    */
    Point(const double x = 0.0, const double y = 0.0);

    /**
    @return Абсцисса точки.
    */
    double getX() const;

    /**
    @return Ордината точки.
    */
    double getY() const;

    /**
    @brief Проверяет равенство координат точки с допуском DBL_EPSILON.
    @param other Точка для сравнения.
    @return true, если разности обеих пар координат не превышают DBL_EPSILON.
    */
    bool operator==(const Point& other) const;

    /**
    @brief Проверяет, что точки не равны.
    @param other Точка для сравнения.
    @return Результат, противоположный operator==.
    */
    bool operator!=(const Point& other) const;

    /**
    @brief Записывает координаты точки в поток в формате «x y».
    @param output Поток вывода.
    @param point Записываемая точка.
    @return Тот же поток вывода, чтобы можно было объединять операции <<.
    */
    friend std::ostream& operator<<(std::ostream& output, const Point& point);

    /**
    @brief Читает из потока две координаты в формате «x y».
    @param input Поток ввода.
    @param point Точка, координаты которой будут заменены при успешном чтении.
    @return Тот же поток; при ошибке его состояние сообщает о неудаче.
    */
    friend std::istream& operator>>(std::istream& input, Point& point);
};
