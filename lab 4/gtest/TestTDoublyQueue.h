#ifndef TEST_TDOUBLY_QUEUE_H
#define TEST_TDOUBLY_QUEUE_H

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "TDoublyQueue.h" // Подключаем ваш класс

// =========================================================================
// ТЕСТ 1: Базовые операции добавления и извлечения (LIFO и FIFO)
// cmake -B build
//cmake --build build
// =========================================================================
TEST(TDoublyQueueTest, BasicOperations) {
    TDoublyQueue<int> deque;                                // Создаем пустую очередь

    EXPECT_TRUE(deque.IsEmpty());                           // Проверяем, что она пуста
    EXPECT_EQ(deque.Size(), 0);                             // Размер должен быть 0

    // Добавляем элементы в оба конца
    deque.PushBack(10);                                     // Очередь: [10]
    deque.PushBack(20);                                     // Очередь: [10, 20]
    deque.PushFront(5);                                     // Очередь: [5, 10, 20]

    EXPECT_FALSE(deque.IsEmpty());                          // Теперь очередь не пуста
    EXPECT_EQ(deque.Size(), 3);                             // Размер должен стать 3

    // Проверка доступа к крайним элементам (без удаления)
    EXPECT_EQ(deque.Front(), 5);                            // Первый элемент — 5
    EXPECT_EQ(deque.Back(), 20);                            // Последний элемент — 20

    // Извлекаем элементы (проверяем правильность удаления)
    EXPECT_EQ(deque.PopFront(), 5);                         // Извлекли первый элемент (5)
    EXPECT_EQ(deque.PopBack(), 20);                         // Извлекли последний элемент (20)

    EXPECT_EQ(deque.Size(), 1);                             // Остался только один элемент
    EXPECT_EQ(deque.Front(), 10);                           // И это число 10
}

// =========================================================================
// ТЕСТ 2: Обработка исключений при работе с пустой очередью
// =========================================================================
TEST(TDoublyQueueTest, EmptyQueueExceptions) {
    TDoublyQueue<int> deque;                                // Создаем пустую очередь

    // Проверяем, что методы извлечения и просмотра кидают исключение std::out_of_range
    EXPECT_THROW(deque.PopFront(), std::out_of_range);      // Попытка PopFront из пустой
    EXPECT_THROW(deque.PopBack(), std::out_of_range);       // Попытка PopBack из пустой
    EXPECT_THROW(deque.Front(), std::out_of_range);         // Попытка прочитать Front
    EXPECT_THROW(deque.Back(), std::out_of_range);          // Попытка прочитать Back

    // Проверяем, что после всех этих попыток очередь осталась невредимой
    EXPECT_TRUE(deque.IsEmpty());                           // Размер по-прежнему 0
}

// =========================================================================
// ТЕСТ 3: Глубокое копирование (Copy) и очистка (Clear)
// =========================================================================
TEST(TDoublyQueueTest, CopyAndClear) {
    TDoublyQueue<std::string> deque1;                       // Очередь строк
    deque1.PushBack("Apple");                               // Добавляем "Apple"
    deque1.PushBack("Banana");                              // Добавляем "Banana"

    // Проверяем конструктор копирования
    TDoublyQueue<std::string> deque2 = deque1;              // Копируем очередь 1 в очередь 2

    EXPECT_EQ(deque2.Size(), 2);                            // Копия должна иметь тот же размер
    EXPECT_EQ(deque2.Front(), "Apple");                     // И те же данные

    // Модифицируем копию и проверяем, что оригинал не изменился (Глубокое копирование)
    deque2.PopFront();                                      // Удаляем "Apple" из копии
    EXPECT_EQ(deque2.Size(), 1);                            // Размер копии уменьшился
    EXPECT_EQ(deque1.Size(), 2);                            // Оригинал НЕ изменился
    EXPECT_EQ(deque1.Front(), "Apple");                     // В оригинале все еще "Apple"

    // Проверяем метод очистки
    deque1.Clear();                                         // Очищаем оригинал
    EXPECT_TRUE(deque1.IsEmpty());                          // Должна стать пустой
    EXPECT_EQ(deque1.Size(), 0);                            // Размер 0

    // Очищаем копию (проверка, что нет утечек памяти при уничтожении)
    deque2.Clear();
    EXPECT_TRUE(deque2.IsEmpty());
}

#endif // TEST_TDOUBLY_QUEUE_H