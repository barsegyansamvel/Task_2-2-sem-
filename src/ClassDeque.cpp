#include "ClassDeque.h"

#include <stdexcept>
#include <utility>

Deque::Deque() noexcept : data(nullptr), count(0)
{
}

Deque::Deque(const std::initializer_list<int> values) : Deque()
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
        Deque copy(other);
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

void Deque::push_back(const int value)
{
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

void Deque::push_front(const int value)
{
    int* newData = new int[count + 1];
    newData[0] = value;
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

Deque& Deque::operator<<(const int value)
{
    push_back(value);
    return *this;
}

Deque& Deque::operator>>(int& value)
{
    value = pop_front();
    return *this;
}
