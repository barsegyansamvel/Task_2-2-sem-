#pragma once

#include "Point.h"

#include <iostream>

/**
@brief Отрезок экстраполятора нулевого порядка.

Левая точка сохраняется без изменения. У правой точки абсцисса
берётся из заданной правой точки, а ордината — из левой.
*/
class Segment
{
private:
    Point leftPoint;
    Point rightPoint;

public:
    /**
    @brief Создаёт отрезок по заданным левой и правой точкам.
    @param leftPoint Заданная левая точка.
    @param rightPoint Заданная правая точка; используется её абсцисса.
    @throw std::invalid_argument если правая абсцисса меньше левой.
    */
    Segment(const Point& leftPoint = Point(), const Point& rightPoint = Point());

    /**
    @return Левая точка отрезка.
    */
    Point getLeftPoint() const;

    /**
    @return Правая точка построенного отрезка.
    */
    Point getRightPoint() const;

    /**
    @brief Вычисляет значение сигнала на заданной абсциссе.
    @param x Абсцисса внутри отрезка, включая обе границы.
    @return Ордината левой точки.
    @throw std::out_of_range если x находится вне отрезка.
    */
    double getY(const double x) const;

    /**
    @brief Считывает две точки из потока.
    @param input Поток ввода.
    @return Созданный отрезок.
    */
    static Segment Read(std::istream& input);

    /**
    @brief Выводит координаты обоих концов отрезка.
    */
    friend std::ostream& operator<<(
        std::ostream& output,
        const Segment& segment
    );
};