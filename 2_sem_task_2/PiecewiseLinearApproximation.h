#pragma once

#include "Point.h"

#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <vector>

/**
 * @brief Кусочно-постоянная аппроксимация по точкам.
 *
 * Точки хранятся в порядке возрастания абсцисс. На каждом участке
 * возвращается ордината его левой точки.
 */
class PiecewiseLinearApproximation
{
private:
    std::vector<Point> points;

    /** @brief Проверяет наличие двух и более точек с возрастающими x. */
    void ValidatePoints() const;

public:
    /** @brief Создаёт аппроксимацию из вектора точек. */
    explicit PiecewiseLinearApproximation(const std::vector<Point>& points);

    /** @brief Создаёт аппроксимацию из списка точек. */
    PiecewiseLinearApproximation(std::initializer_list<Point> points);

    /** @brief Вычисляет ординату кусочно-постоянного сигнала. */
    double getY(const double x) const;

    /** @brief Добавляет точку с абсциссой больше абсцисс ранее добавленных точек. */
    void AddPoint(const Point& point);

    /** @return Константная ссылка на точки аппроксимации. */
    const std::vector<Point>& GetPoints() const;

    /**
     * @brief Считывает заданное количество точек из потока.
     * @param input Поток, из которого читаются пары x y.
     * @param count Количество точек; должно быть не меньше двух.
     * @return Прочитанные точки.
     */
    static std::vector<Point> ReadPoints(std::istream& input, std::size_t count);
};
