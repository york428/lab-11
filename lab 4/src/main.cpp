#include <iostream>
#include "TDoublyQueue.h"       // Для ручного примера
#include <gtest/gtest.h>
#include "TestTDoublyQueue.h"   // Для запуска тестов

// ==========================================
// Функция с простым ручным примером
// ==========================================
void RunSimpleExample() {
    std::cout << "=== Ручной пример работы TDoublyQueue ===\n";

    TDoublyQueue<int> q;

    // Добавляем элементы
    q.PushBack(10);  // Очередь: [10]
    q.PushBack(20);  // Очередь: [10, 20]
    q.PushFront(5);  // Очередь: [5, 10, 20]

    std::cout << "Размер очереди: " << q.Size() << "\n";
    std::cout << "Первый элемент (Front): " << q.Front() << "\n";
    std::cout << "Последний элемент (Back): " << q.Back() << "\n";

    // Извлекаем элементы
    std::cout << "Извлечен из начала: " << q.PopFront() << "\n";
    std::cout << "Извлечен из конца:  " << q.PopBack() << "\n";

    std::cout << "Остаток в очереди: " << q.Front() << "\n";
    std::cout << "=========================================\n\n";
}

// ==========================================
// Точка входа
// ==========================================
int main(int argc, char** argv) {
    // 1. Сначала запускаем ручной пример
    RunSimpleExample();

    // 2. Затем инициализируем и запускаем тесты
    std::cout << "=== Запуск Google Test ===\n";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}