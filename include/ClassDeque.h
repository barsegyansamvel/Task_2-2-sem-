#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>

/** @brief Дек целых чисел на динамическом массиве. */
class Deque
{
private:
    /** @brief Указатель на массив элементов дека. */
    int* data;
    /** @brief Количество элементов дека. */
    std::size_t count;

    /**
     * @brief Проверяет наличие элементов перед чтением или удалением.
     * @throws std::out_of_range Если дек пуст.
     */
    void checkNotEmpty() const;

public:
    /** @brief Конструктор по умолчанию: создаёт пустой дек. */
    Deque() noexcept;

    /**
     * @brief Создаёт дек из списка инициализации, сохраняя порядок чисел.
     * @param values Список целых чисел, например {1, 2, 3}.
     */
    Deque(std::initializer_list<int> values);

    /**
     * @brief Конструктор копирования: создаёт независимую копию массива.
     * @param other Дек, элементы которого копируются.
     */
    Deque(const Deque& other);

    /**
     * @brief Конструктор перемещения: забирает массив, оставляя other пустым.
     * @param other Дек, передающий владение своим массивом.
     */
    Deque(Deque&& other) noexcept;

    /** @brief Деструктор: освобождает память динамического массива. */
    ~Deque();

    /**
     * @brief Заменяет содержимое дека независимой копией другого дека.
     * @param other Дек, элементы которого копируются.
     * @return Ссылка на текущий дек для цепочки присваиваний.
     */
    Deque& operator=(const Deque& other);

    /**
     * @brief Освобождает свой массив и забирает массив другого дека.
     * @param other Дек, который после перемещения становится пустым.
     * @return Ссылка на текущий дек. Самоприсваивание его не изменяет.
     */
    Deque& operator=(Deque&& other) noexcept;

    /**
     * @brief Добавляет число в конец дека.
     * @param value Добавляемое число.
     */
    void push_back(int value);

    /**
     * @brief Добавляет число в начало дека, сдвигая остальные элементы.
     * @param value Добавляемое число.
     */
    void push_front(int value);

    /**
     * @brief Удаляет последний элемент дека.
     * @return Значение удалённого элемента.
     * @throws std::out_of_range Если дек пуст.
     */
    int pop_back();

    /**
     * @brief Удаляет первый элемент и сдвигает оставшиеся элементы к началу.
     * @return Значение удалённого элемента.
     * @throws std::out_of_range Если дек пуст.
     */
    int pop_front();

    /**
     * @brief Читает последний элемент без удаления.
     * @return Значение последнего элемента.
     * @throws std::out_of_range Если дек пуст.
     */
    int back() const;

    /**
     * @brief Читает первый элемент без удаления.
     * @return Значение первого элемента.
     * @throws std::out_of_range Если дек пуст.
     */
    int front() const;

    /**
     * @brief Проверяет, есть ли в деке элементы.
     * @return true, если дек пуст; иначе false.
     */
    bool empty() const noexcept;

    /**
     * @brief Преобразует содержимое дека в строку от первого элемента к последнему.
     * @return Строка вида {1, 2, 3}; для пустого дека — {}.
     */
    std::string toString() const;

    /**
     * @brief Оператор <<: добавляет число в конец дека через push_back().
     * @param value Добавляемое число.
     * @return Ссылка на дек для записи вида deque << 1 << 2.
     */
    Deque& operator<<(int value);

    /**
     * @brief Оператор >>: извлекает число из начала дека через pop_front().
     * @param value Переменная, в которую записывается извлечённое число.
     * @return Ссылка на дек для записи вида deque >> first >> second.
     * @throws std::out_of_range Если дек пуст.
     */
    Deque& operator>>(int& value);
};
