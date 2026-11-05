#ifndef TDOUBLY_LIST_H
#define TDOUBLY_LIST_H

#include <stdexcept>
#include <utility>
#include <vector>
template<typename T>
class TDoublyList {
    struct TNode {
        T value;
        TNode* pNext;
        TNode* pPrev;
    };

    TNode* pFirst;
    TNode* pLast;
    size_t sz;

public:
    TDoublyList() : pFirst(nullptr), pLast(nullptr), sz(0) {}

    TDoublyList(const std::vector<T>& v) : pFirst(nullptr), pLast(nullptr), sz(0) {
        for (size_t i = 0; i < v.size(); ++i) {
            PushBack(v[i]);
        }
    }

    TDoublyList(const TDoublyList& list) : pFirst(nullptr), pLast(nullptr), sz(list.sz) {
        if (list.pFirst == nullptr) return;

        pFirst = new TNode{ list.pFirst->value, nullptr, nullptr };
        TNode* pCurrent = pFirst;
        TNode* pOther = list.pFirst->pNext;

        while (pOther != nullptr) {
            pCurrent->pNext = new TNode{ pOther->value, nullptr, pCurrent };
            pCurrent = pCurrent->pNext;
            pOther = pOther->pNext;
        }
        pLast = pCurrent;
    }

    TDoublyList(TDoublyList&& list) noexcept
        : pFirst(list.pFirst), pLast(list.pLast), sz(list.sz) {
        list.pFirst = nullptr;
        list.pLast = nullptr;
        list.sz = 0;
    }

    TDoublyList& operator=(const TDoublyList& list) {
        if (this != &list) {
            TDoublyList tmp(list);
            Swap(tmp);
        }
        return *this;
    }

    TDoublyList& operator=(TDoublyList&& list) noexcept {
        if (this != &list) {
            Clear();
            pFirst = list.pFirst;
            pLast = list.pLast;
            sz = list.sz;

            list.pFirst = nullptr;
            list.pLast = nullptr;
            list.sz = 0;
        }
        return *this;
    }

    ~TDoublyList() {
        Clear();
    }

    void Clear() {
        TNode* p = pFirst;
        while (p != nullptr) {
            TNode* pNext = p->pNext;
            delete p;
            p = pNext;
        }
        pFirst = nullptr;
        pLast = nullptr;
        sz = 0;
    }

    void Swap(TDoublyList& other) noexcept {
        std::swap(pFirst, other.pFirst);
        std::swap(pLast, other.pLast);
        std::swap(sz, other.sz);
    }

    void PushFront(const T& value) {
        TNode* pNew = new TNode{ value, pFirst, nullptr };
        if (pFirst != nullptr) {
            pFirst->pPrev = pNew;
        }
        else {
            pLast = pNew;
        }
        pFirst = pNew;
        sz++;
    }

    void PushBack(const T& value) {
        TNode* pNew = new TNode{ value, nullptr, pLast };
        if (pLast != nullptr) {
            pLast->pNext = pNew;
        }
        else {
            pFirst = pNew;
        }
        pLast = pNew;
        sz++;
    }

    // ==========================================
    // НОВЫЕ МЕТОДЫ УДАЛЕНИЯ
    // ==========================================

    // Удаление первого элемента
    void PopFront() {
        if (sz == 0) {
            throw std::out_of_range("List is empty");
        }

        TNode* pToDelete = pFirst;
        pFirst = pFirst->pNext; // Сдвигаем указатель на первый

        if (pFirst != nullptr) {
            pFirst->pPrev = nullptr; // Обнуляем ссылку на удаленный узел
        }
        else {
            pLast = nullptr; // Если список стал пустым, обнуляем и последний
        }

        delete pToDelete;
        sz--;
    }

    // Удаление последнего элемента
    void PopBack() {
        if (sz == 0) {
            throw std::out_of_range("List is empty");
        }

        TNode* pToDelete = pLast;
        pLast = pLast->pPrev; // Сдвигаем указатель на последний назад

        if (pLast != nullptr) {
            pLast->pNext = nullptr; // Обнуляем ссылку на удаленный узел
        }
        else {
            pFirst = nullptr; // Если список стал пустым
        }

        delete pToDelete;
        sz--;
    }

    // Удаление первого элемента по значению
    bool Remove(const T& value) {
        TNode* pCurrent = pFirst;

        // Ищем нужный узел
        while (pCurrent != nullptr && pCurrent->value != value) {
            pCurrent = pCurrent->pNext;
        }

        // Если не нашли
        if (pCurrent == nullptr) {
            return false;
        }

        // Если нашли, перестраиваем связи
        if (pCurrent->pPrev != nullptr) {
            pCurrent->pPrev->pNext = pCurrent->pNext;
        }
        else {
            pFirst = pCurrent->pNext; // Если удаляем самый первый
        }

        if (pCurrent->pNext != nullptr) {
            pCurrent->pNext->pPrev = pCurrent->pPrev;
        }
        else {
            pLast = pCurrent->pPrev; // Если удаляем самый последний
        }

        delete pCurrent;
        sz--;
        return true;
    }

    // Удаление по индексу
    void Erase(size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }

        // Оптимизация: если индекс во второй половине, идем с конца
        TNode* pCurrent = nullptr;
        if (index < sz / 2) {
            pCurrent = pFirst;
            for (size_t i = 0; i < index; ++i) {
                pCurrent = pCurrent->pNext;
            }
        }
        else {
            pCurrent = pLast;
            for (size_t i = sz - 1; i > index; --i) {
                pCurrent = pCurrent->pPrev;
            }
        }

        // Перестраиваем связи (та же логика, что и в Remove)
        if (pCurrent->pPrev != nullptr) {
            pCurrent->pPrev->pNext = pCurrent->pNext;
        }
        else {
            pFirst = pCurrent->pNext;
        }

        if (pCurrent->pNext != nullptr) {
            pCurrent->pNext->pPrev = pCurrent->pPrev;
        }
        else {
            pLast = pCurrent->pPrev;
        }

        delete pCurrent;
        sz--;
    }

    // Для удобства проверки (вывод списка)
    void Print() const {
        TNode* p = pFirst;
        while (p != nullptr) {
            std::cout << p->value << " <-> ";
            p = p->pNext;
        }
        std::cout << "nullptr\n";
    }
};