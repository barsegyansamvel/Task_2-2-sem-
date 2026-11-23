#include "ClassDeque.h"

#include <iostream>
#include <utility>

/**
 * @brief Демонстрирует создание дека, операции с обоих концов, копирование,
 * перемещение, присваивание, операторы << и >> и проверку пустоты.
 * @return 0 при нормальном завершении программы.
 */
int main()
{
    Deque deque{10, 20, 30};
    std::cout << "Initial deque: " << deque.toString() << '\n';

    deque.push_front(5);
    deque.push_back(40);
    std::cout << "After insertion: " << deque.toString() << '\n';
    std::cout << "Front: " << deque.front() << ", back: " << deque.back() << '\n';
    std::cout << "pop_front(): " << deque.pop_front() << '\n';
    std::cout << "pop_back(): " << deque.pop_back() << '\n';
    std::cout << "After removal: " << deque.toString() << '\n';

    Deque copy(deque);
    Deque moved(std::move(copy));
    Deque assigned;
    assigned = deque;
    Deque moveAssigned;
    moveAssigned = std::move(assigned);
    std::cout << "Copy and move constructors: " << moved.toString() << '\n';
    std::cout << "Copy and move assignment: " << moveAssigned.toString() << '\n';

    deque << 50;
    int value = 0;
    deque >> value;
    std::cout << "Extracted by >>: " << value << '\n';
    std::cout << "After << and >>: " << deque.toString() << '\n';

    Deque empty;
    std::cout << "Default deque is empty: " << std::boolalpha << empty.empty() << '\n';
    return 0;
}
