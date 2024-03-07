#pragma once

namespace saran {

    template<typename KEY, typename VALUE>
    class RBTree {
    private:
        struct Node;

        enum NodePosition {
            kPosLeft = 0,
            kPosRight,
        };
    public:
        explicit RBTree(KEY k, VALUE v);
        RBTree() = default;
        ~RBTree() = default;

        bool insert(KEY k, VALUE v);

        void remove(KEY k);

        void traverse();

    private:
        void frontTraverse(Node *currentNode);

        void insertBalance(Node *currentNode);

        Node *findNode(KEY k);

        Node *findUncleNode(Node *currentNode);

        NodePosition findPositionUnderParent(Node *currentNode);

        void leftRotate(Node *currentNode);

        void rightRotate(Node *currentNode);

    private:
        Node *rootNode_ = nullptr;
    };

// 红黑树节点
    template<typename KEY, typename VALUE>
    struct RBTree<KEY, VALUE>::Node {
        enum NodeColor {
            kNodeRed = 0,
            kNodeBlack = 1,
        };

        explicit Node(KEY k, VALUE v) : key(k),
                                        value(v),
                                        leftChild(nullptr),
                                        rightChild(nullptr),
                                        parent(nullptr),
                                        color(kNodeBlack) {}

        KEY key;
        VALUE value;
        Node *leftChild;
        Node *rightChild;
        Node *parent;
        NodeColor color;
    };

    template<typename KEY, typename VALUE>
    RBTree<KEY, VALUE>::RBTree(KEY k, VALUE v) {
        if (nullptr == rootNode_) {
            rootNode_ = new Node(k, v);
        }
    }

    template<typename KEY, typename VALUE>
    bool RBTree<KEY, VALUE>::insert(KEY k, VALUE v) {
        // 当插入的为第一个元素时
        if (nullptr == rootNode_) {
            rootNode_ = new Node(k, v);
            return true;
        }

        Node *currentNode = rootNode_;
        do {
            if (currentNode->key == k) {
                currentNode->value = v;
                return true;
            }

            if (k < currentNode->key) {
                if (nullptr == currentNode->leftChild) {
                    currentNode->leftChild = new Node(k, v);
                    currentNode->leftChild->parent = currentNode;
                    currentNode->leftChild->color = Node::kNodeRed;
                    currentNode = currentNode->leftChild;
                    break;
                } else {
                    currentNode = currentNode->leftChild;
                    continue;
                }
            }

            if (k > currentNode->key) {
                if (nullptr == currentNode->rightChild) {
                    currentNode->rightChild = new Node(k, v);
                    currentNode->rightChild->parent = currentNode;
                    currentNode->rightChild->color = Node::kNodeRed;
                    currentNode = currentNode->rightChild;
                    break;
                } else {
                    currentNode = currentNode->rightChild;
                    continue;
                }
            }
        } while (true);
        insertBalance(currentNode);
        return true;
    }

    template<typename KEY, typename VALUE>
    void RBTree<KEY, VALUE>::remove(KEY k) {
        Node *rmNode = findNode(k);
        if (nullptr == rmNode) {
            return;
        }

        if (nullptr == rmNode->leftChild && nullptr == rmNode->rightChild) {
            if (Node::kNodeRed == rmNode->color) {
                if (kPosLeft == findPositionUnderParent(rmNode)) {
                    rmNode->parent->leftChild = nullptr;
                } else {
                    rmNode->parent->rightChild = nullptr;
                }
                delete (rmNode);
                return;
            }
        }
    }

    template<typename KEY, typename VALUE>
    void RBTree<KEY, VALUE>::traverse() {
        frontTraverse(rootNode_);
    }

    template<typename KEY, typename VALUE>
    void RBTree<KEY, VALUE>::frontTraverse(Node *currentNode) {
        if (currentNode == nullptr) return;

        std::string color = currentNode->color == 0 ? "Red" : "Black";
        std::cout << "Key: " << currentNode->key << "Value: " << currentNode->value << "Color: " << color << std::endl;
        frontTraverse(currentNode->leftChild);
        frontTraverse(currentNode->rightChild);
    }

    template<typename KEY, typename VALUE>
    void RBTree<KEY, VALUE>::insertBalance(Node *currentNode) {
        if (currentNode == rootNode_) {
            currentNode->color = Node::kNodeBlack;
            return;
        }

        if (currentNode->parent->color == Node::kNodeBlack) {
            return;
        }

        Node *uncleNode = findUncleNode(currentNode);
        if (uncleNode != nullptr && uncleNode->color == Node::kNodeRed) {
            currentNode->parent->color = Node::kNodeBlack;
            uncleNode->color = Node::kNodeBlack;
            currentNode->parent->parent->color = Node::kNodeRed;
            insertBalance(currentNode->parent->parent);
        } else {
            if (findPositionUnderParent(currentNode->parent) == kPosLeft) {
                if (findPositionUnderParent(currentNode) == kPosLeft) {
                    currentNode->parent->color = Node::kNodeBlack;
                    currentNode->parent->parent->color = Node::kNodeRed;
                    rightRotate(currentNode->parent->parent);
                } else {
                    leftRotate(currentNode->parent);
                    insertBalance(currentNode->leftChild);
                }
            } else {
                if (findPositionUnderParent(currentNode) == kPosRight) {
                    currentNode->parent->color = Node::kNodeBlack;
                    currentNode->parent->parent->color = Node::kNodeRed;
                    leftRotate(currentNode->parent->parent);
                } else {
                    rightRotate(currentNode->parent);
                    insertBalance(currentNode->rightChild);
                }
            }
        }
    }

    template<typename KEY, typename VALUE>
    RBTree<KEY, VALUE>::Node *RBTree<KEY, VALUE>::findNode(KEY k) {
        Node *currentNode = rootNode_;
        while (currentNode != nullptr) {
            if (k == currentNode->key) {
                break;
            } else if (k < currentNode->key) {
                currentNode = currentNode->leftChild;
            } else if (k > currentNode->key) {
                currentNode = currentNode->rightChild;
            }
        }

        return currentNode;
    }

    template<typename KEY, typename VALUE>
    RBTree<KEY, VALUE>::Node *RBTree<KEY, VALUE>::findUncleNode(Node *currentNode) {
        if (nullptr == currentNode) return nullptr;
        Node *grandParentNode = currentNode->parent->parent;
        Node *parentNode = currentNode->parent;
        if (grandParentNode->leftChild == parentNode) {
            return grandParentNode->rightChild;
        } else {
            return grandParentNode->leftChild;
        }
    }

    template<typename KEY, typename VALUE>
    typename RBTree<KEY, VALUE>::NodePosition RBTree<KEY, VALUE>::findPositionUnderParent(Node *currentNode) {
        Node *parent = currentNode->parent;
        if (parent->leftChild == currentNode) {
            return kPosLeft;
        } else {
            return kPosRight;
        }
    }

    template<typename KEY, typename VALUE>
    void RBTree<KEY, VALUE>::leftRotate(Node *currentNode) {
        Node *parent = currentNode->parent;
        Node *rightChild = currentNode->rightChild;

        rightChild->parent = parent;

        if (parent != nullptr) {
            if (findPositionUnderParent(currentNode) == kPosLeft) {
                parent->leftChild = rightChild;
            } else {
                parent->rightChild = rightChild;
            }
        } else {
            rootNode_ = rightChild;
        }

        currentNode->rightChild = rightChild->leftChild;
        if (rightChild->leftChild) {
            rightChild->leftChild->parent = currentNode;
        }

        rightChild->leftChild = currentNode;
        currentNode->parent = rightChild;
    }

    template<typename KEY, typename VALUE>
    void RBTree<KEY, VALUE>::rightRotate(Node *currentNode) {
        Node *parent = currentNode->parent;
        Node *leftChild = currentNode->leftChild;

        leftChild->parent = parent;

        if (parent != nullptr) {
            if (findPositionUnderParent(currentNode) == kPosLeft) {
                parent->leftChild = leftChild;
            } else {
                parent->rightChild = leftChild;
            }
        } else {
            rootNode_ = leftChild;
        }


        currentNode->leftChild = leftChild->rightChild;
        if (leftChild->rightChild) {
            leftChild->rightChild->parent = currentNode;

        }

        leftChild->rightChild = currentNode;
        currentNode->parent = leftChild;
    }

}