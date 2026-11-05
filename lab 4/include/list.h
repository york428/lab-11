#define __TSinglyList_H__
#include <iostream>

template<typename T> class TSinglyList {
	struct TNode {
		T value;
		TNode* pNext;
	};
	TNode* pFirst;
	size_t sz;
public:
	TSinglyList(): pFirst(nullptr),sz(0){ }
	TSinglyList(const vector<T>& v) {
		for (size_t i = v.size(); i > 0; i--)
			PushFront(v[i - 1]);
	}
	TSinglyList(const TSinglyList& list) :
		pFirst(nullptr), sz(list.sz) {
		if (list.pFirst == nullptr)
			return;
		TNode* pNew = pFirst = new TNode{ *list.pFirst };
		for (; pNew->pNext != nullptr; pNew = pNew->pNext)
			pNew->pNext = new TNode{ *pNew->pNext };
		TSinglyList(TSinglyList && list)noexcept {
			pFirst = nullptr;
			swap(*this, list);
		}
		TSinglyList& operator=(const TSinglyList& list) {
			if (this != &list) {
				TSinglyList tmp(list);
				swap(*this, tmp);
			}
			return *this;
		}
		TSinglyList& operator =(TSinglyList&& list)noexcept {
			swap(*this, list);
			return *this;
		}
		~TSinglyList() {
			TNode* p;
			while (pFirst != nullptr) {
				p = pFirst;
				pFirst = pFirst->pNext;
				delete p;
			}
		}
	}
};