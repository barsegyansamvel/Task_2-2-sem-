#include "ClassDeque.h"

#include <stdexcept>
#include <utility>

Deque::Deque() noexcept : data(nullptr), count(0)
{
}

Deque::Deque(std::initializer_list<int> values) : Deque()
{
    if (values.size() != 0)
    {
        data = new int[values.size()];
        for (int value : values)
        {
            data[count++] = value;
        }
    }
}

Deque::Deque(const Deque& other) : Deque()
{
    if (!other.empty())
    {
        data = new int[other.count];
        count = other.count;
        for (std::size_t i = 0; i < count; ++i)
        {
            data[i] = other.data[i];
        }
    }
}

Deque::Deque(Deque&& other) noexcept : data(other.data), count(other.count)
{
    // Исходный объект больше не владеет массивом и не удалит его в деструкторе.
    other.data = nullptr;
    other.count = 0;
}

Deque::~Deque()
{
    delete[] data;
}

Deque& Deque::operator=(const Deque& other)
{
    if (this != &other)
    {
        // Сначала создаём копию: при ошибке выделения памяти текущий дек сохранится.
        Deque copy(other);
        // После обмена временный объект освободит прежний массив текущего дека.
        std::swap(data, copy.data);
        std::swap(count, copy.count);
    }
    return *this;
}

Deque& Deque::operator=(Deque&& other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        count = other.count;
        other.data = nullptr;
        other.count = 0;
    }
    return *this;
}

void Deque::checkNotEmpty() const
{
    if (empty())
    {
        throw std::out_of_range("Deque is empty");
    }
}

void Deque::push_back(int value)
{
    // Выделяем новый массив с местом для добавляемого элемента.
    int* newData = new int[count + 1];
    for (std::size_t i = 0; i < count; ++i)
    {
        newData[i] = data[i];
    }
    newData[count] = value;
    delete[] data;
    data = newData;
    ++count;
}

void Deque::push_front(int value)
{
    int* newData = new int[count + 1];
    newData[0] = value;
    // При копировании сдвигаем прежние элементы на одну позицию вправо.
    for (std::size_t i = 0; i < count; ++i)
    {
        newData[i + 1] = data[i];
    }
    delete[] data;
    data = newData;
    ++count;
}

int Deque::pop_back()
{
    checkNotEmpty();
    // Уменьшаем число элементов; сам массив будет освобождён позже.
    return data[--count];
}

int Deque::pop_front()
{
    checkNotEmpty();
    const int value = data[0];
    for (std::size_t i = 1; i < count; ++i)
    {
        data[i - 1] = data[i];
    }
    --count;
    return value;
}

int Deque::back() const
{
    checkNotEmpty();
    return data[count - 1];
}

int Deque::front() const
{
    checkNotEmpty();
    return data[0];
}

bool Deque::empty() const noexcept
{
    return count == 0;
}

std::string Deque::toString() const
{
    std::string result = "{";
    for (std::size_t i = 0; i < count; ++i)
    {
        if (i != 0)
        {
            result += ", ";
        }
        result += std::to_string(data[i]);
    }
    return result + "}";
}

Deque& Deque::operator<<(int value)
{
    push_back(value);
    return *this;
}

Deque& Deque::operator>>(int& value)
{
    value = pop_front();
    return *this;
}
