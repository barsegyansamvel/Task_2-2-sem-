#include <iostream>
#include "Quadrilateral.h"
Point getPoint()
{
    double x, y;
    std::cin >> x >> y;

    if (std::cin.fail())
    {
        std::cout << "Input error.\n";
        std::exit(1);
    }

    return Point{x, y};
}

int main()
{
    std::cout << "Enter vertices in order A -> B -> C -> D.\n";

    std::cout << "A (x y): ";
    Point a = getPoint();

    std::cout << "B (x y): ";
    Point b = getPoint();

    std::cout << "C (x y): ";
    Point c = getPoint();

    std::cout << "D (x y): ";
    Point d = getPoint();

    Quadrilateral figure{a, b, c, d};

    std::cout << "\nVertices:\n";
    figure.print();

    if (figure.isConvex())
    {
        std::cout << "Convex: yes\n";
    }
    else
    {
        std::cout << "Convex: no\n";
    }

    if (figure.canDescribe())
    {
        std::cout << "Circumscribed circle: yes\n";
    }
    else
    {
        std::cout << "Circumscribed circle: no\n";
    }

    return 0;
}
