#include <iostream>
#include "Quadrilateral.h"

int main()
{
    double ax, ay;
    double bx, by;
    double cx, cy;
    double dx, dy;

    std::cout << "Enter A, B, C, D in boundary order.\n";
    std::cout << "Enter x and y for each point:\n";

    std::cin >> ax >> ay;
    std::cin >> bx >> by;
    std::cin >> cx >> cy;
    std::cin >> dx >> dy;

    if (std::cin.fail())
    {
        std::cout << "Input error.\n";
        return 1;
    }

    Point a{ax, ay};
    Point b{bx, by};
    Point c{cx, cy};
    Point d{dx, dy};

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