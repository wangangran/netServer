#pragma once

#include <iostream>
#include <atomic>
#include "../base/Random.h"

namespace saran {

template<typename Key, class Compare>
class SkipList {
private:
    struct Node;
public:
    explicit SkipList(Compare cmp) : maxHeight_(kMaxHeight), compate_(cmp) {
        head_ = newNode(0, maxHeight_);
    }
    SkipList(const SkipList &) = delete;
    SkipList& operator=(const SkipList &) = delete;

    void push(const Key &k) {
        int level = maxHeight_ - 1;
        Node *prev[maxHeight_.load()];
        while (nullptr != head_) {
            prev[level] = findNextNode(head_, level, k);

            if (level == 0) {
                break;
            }

            level--;
        }

        Node *newNodePtr = newNode(k, maxHeight_);

        int index = 0;
        static const int probability = 2;
        while (index < maxHeight_ && (index == 0 || rdm_.oneIn(probability))) {
            newNodePtr->setNext(index, prev[index]->next(index));
            prev[index]->setNext(index, newNodePtr);
            index++;
        }
    }

    void traverse(int height) {
        Node *cur = head_->next(height);
        while (nullptr != cur) {
            std::cout << cur->key_ << std::endl;
            cur = cur->next(height);
        }
    }

private:
    Node* newNode(const Key &k, int height) {
        char * const ptr = reinterpret_cast<char *>(malloc(sizeof(Node) * height));
        Node *result =  new (ptr) Node(k);
        for (int index = 0; index < maxHeight_; ++index) {
            result->setNext(index, nullptr);
        }
        return result;
    }

    Node *findNextNode(Node *nod, int level, const Key &k) {
        Node *cur = nod;
        while (true) {
            // 当前层的next节点为空
            if (nullptr == cur->next(level)) {
                break;
            }   

            if (compate_(k, cur->next(level)->key_) <= 0) {
                break;
            }

            cur = cur->next(level);
        }

        return cur;
    }
private:
    enum { kMaxHeight = 12 };

    std::atomic<int> maxHeight_;
    Node *head_ = nullptr;
    Compare const compate_;
    Random rdm_;
};

template<typename Key, typename Compare>
struct SkipList<Key, Compare>::Node {
public:
    explicit Node(const Key &k) : key_(k) {}

    Key const key_;

    Node* next(int n) {
        assert(n >= 0);
        
        return next_[n].load();
    }

    void setNext(int n, Node *node) {
        assert(n >= 0);

        next_[n].store(node);
    }
private:
    std::atomic<Node*> next_[1];
};

}