#ifndef NETSERVER_REACTOR_DATASTRUCT_SMALLHEAP_H
#define NETSERVER_REACTOR_DATASTRUCT_SMALLHEAP_H

#include <vector>
#include <functional>
#include <iostream>

#define PARENT_INDEX(i)             ((i - 1) / 2)
#define LEFT_CHILD_INDEX(i)         (2 * i + 1)
#define RIGHT_CHILD_INDEX(i)        (2 * i + 2)


using TimeFun = std::function<void()>;

template<typename K, typename V>
struct SmallHeapNode {
    SmallHeapNode(K k, V v) : key(k), value(v) {}
    K key;
    V value;
    bool operator==(const K &k) {
        return (this->key == k);
    };
};


template<typename K, typename V>
class SmallHeap {
public:
    explicit SmallHeap() { };

    SmallHeapNode<K, V> tackFirst() {
        if (nodes_.empty()) return SmallHeapNode<K, V>(0, std::string());
        int index = 0;
        SmallHeapNode<K, V> node = nodes_[0];
        std::swap(nodes_[0], nodes_[nodes_.size() - 1]);      
        nodes_.pop_back();    
        downBalance(0);
        return node;
    }

    void addNode(const K &key, const V &value) {
        nodes_.push_back(std::move(SmallHeapNode<K, V>(key, value)));
    }

    void addNodeAndBalance(const K &key, const V &value) {
        addNode(key, value);
        upBalance(nodes_.size() - 1);   
    }

    bool heapSort() {
        if (nodes_.empty()) {
            return false;
        }

        auto sort = [this] (int start, int end) {
            int son = LEFT_CHILD_INDEX(start);
            while (son < end) {                
                if (son + 1 < end && nodes_[son].key < nodes_[son + 1].key) {
                    son += 1;
                }

                if (nodes_[start].key > nodes_[son].key) {
                    break;
                } else {
                    std::swap(nodes_[start], nodes_[son]);
                    start = son;
                    son = LEFT_CHILD_INDEX(start);
                }
            }
        };

        int size = nodes_.size();
        for (int j = PARENT_INDEX(size - 1); j >= 0; --j) {
            sort(j, size);
        }
            

        for (int i = nodes_.size() - 1; i > 0; --i) {
            std::swap(nodes_[0], nodes_[i]);
            sort(0, i);
        }

        return true;
    }

    void removeNode(const K &key) {
        if (nodes_.empty()) return;
        
        int index = 0;
        do {
            if (nodes_[nodes_.size() -1] == key) {
                nodes_.pop_back(); 
                return;
            }


            for (index = 0; index < nodes_.size(); ++index) {
                if (nodes_[index] == key) {
                    std::swap(nodes_[index], nodes_[nodes_.size() - 1]);      
                    nodes_.pop_back();    
                    break;
                }
            }
            return;
        } while(false);

        upBalance(index);
        downBalance(index);
    }
    void traverse() {
        for (auto ite = nodes_.begin(); ite != nodes_.end(); ++ite) {
            std::cout << "key: " << ite->key << "  " << "value: " <<ite->value << std::endl;
        }
    }
private:
    void upBalance(int index) {
        if (index <= 0 || index >= nodes_.size()) {
            return;
        }

        int parentIndex = PARENT_INDEX(index);
        if (nodes_[index].key < nodes_[parentIndex].key) {
            std::swap(nodes_[index], nodes_[parentIndex]);
        }

        upBalance(parentIndex);
    }

    void downBalance(int index) {
        // LEFT_CHILD_INDEX(index) >= nodes_.size() 即当前平衡的节点为最后一个节点
        if (index < 0 || LEFT_CHILD_INDEX(index) >= nodes_.size()) {
            return;
        }

        int nextIndex = nodes_.size();
        int leftIndex = LEFT_CHILD_INDEX(index);
        int rightIndex = RIGHT_CHILD_INDEX(index);
        if (rightIndex > nodes_.size() - 1) {
            if (nodes_[index].key > nodes_[leftIndex].key) {
                std::swap(nodes_[index], nodes_[leftIndex]);
                nextIndex = leftIndex;
            }
        } else {
            if (nodes_[leftIndex].key <= nodes_[rightIndex].key) {
                if (nodes_[index].key > nodes_[leftIndex].key) {
                    std::swap(nodes_[index], nodes_[leftIndex]);
                    nextIndex = leftIndex;
                }
            } else {
                if (nodes_[index].key > nodes_[rightIndex].key) {
                    std::swap(nodes_[index], nodes_[rightIndex]);
                    nextIndex = rightIndex;
                }
            }
        }

        downBalance(nextIndex);
    }
private:
    std::vector<SmallHeapNode<K, V>> nodes_;   
};

#endif // NETSERVER_REACTOR_DATASTRUCT_SMALLHEAP_H