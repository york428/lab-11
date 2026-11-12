#include <iostream>
#include <stdexcept>
#include "TDoublyQueue.h"

int main() {
    // Устанавливаем локаль для корректного вывода русского текста в консоли Windows
    setlocale(LC_ALL, "Russian");

    std::cout << "=== Демонстрация работы TDoublyQueue ===\n\n";

    // 1. Создаем пустую очередь
    TDoublyQueue<int> deque;
    std::cout << "Очередь создана. Размер: " << deque.Size() << "\n";
    std::cout << "Очередь пуста? " << (deque.IsEmpty() ? "Да" : "Нет") << "\n\n";

    // 2. Добавляем элементы в конец и в начало
    std::cout << "Добавляем 10 и 20 в конец (PushBack)...\n";
    deque.PushBack(10);
    deque.PushBack(20);

    std::cout << "Добавляем 5 в начало (PushFront)...\n";
    deque.PushFront(5);

    // Текущее состояние: [5] <-> [10] <-> [20]
    std::cout << "Текущий размер: " << deque.Size() << "\n";
    std::cout << "Первый элемент (Front): " << deque.Front() << "\n";
    std::cout << "Последний элемент (Back): " << deque.Back() << "\n\n";

    // 3. Извлекаем элементы с обоих концов
    std::cout << "Извлекаем с начала (PopFront): " << deque.PopFront() << "\n"; // Вернет 5
    std::cout << "Извлекаем с конца (PopBack): " << deque.PopBack() << "\n";   // Вернет 20

    // Остался только элемент [10]
    std::cout << "Остаток в очереди: " << deque.Front() << "\n";
    std::cout << "Новый размер: " << deque.Size() << "\n\n";

    // 4. Очистка очереди
    std::cout << "Очищаем очередь (Clear)...\n";
    deque.Clear();
    std::cout << "Размер после очистки: " << deque.Size() << "\n";
    std::cout << "Очередь пуста? " << (deque.IsEmpty() ? "Да" : "Нет") << "\n\n";

    // 5. Демонстрация обработки исключения при извлечении из пустой очереди
    std::cout << "Пытаемся извлечь элемент из пустой очереди...\n";
    try {
        deque.PopFront();
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Перехвачено исключение: " << e.what() << "\n";
    }

    std::cout << "\n=== Завершение работы ===\n";
    return 0;
}