#include "Segment.h"

#include <exception>
#include <iostream>

int main()
{
    try
    {
        std::cout << "Введите координаты левой и правой точек " << "(x Левой y Левой x Правой y Правой): ";

        const Segment segment = Segment::Read(std::cin);

        std::cout << "Построенный отрезок: " << segment << '\n';

        std::cout << "Введите абсциссу x внутри отрезка: ";

        double x;
        if (!(std::cin >> x))
        {
            std::cerr << "Ошибка ввода абсциссы.\n";
            return 1;
        }

        std::cout << "Значение сигнала: " << segment.getY(x) << '\n';
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }

    return 0;
}