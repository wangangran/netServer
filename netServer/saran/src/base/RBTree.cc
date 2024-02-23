#include "RBTree.h"
#include <iostream>

template<typename KEY, typename VALUE>
RBTree<KEY, VALUE>::RBTree(KEY k, VALUE v)
{
    if (nullptr == rootNode_) {
        rootNode_ = new RB_Node<KEY, VALUE>(k, v);
    }
}

template<typename KEY, typename VALUE>
RBTree<KEY, VALUE>::~RBTree()
{
}

template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::Insert(KEY k, VALUE v)
{
    if (nullptr == rootNode_) {
        rootNode_ = new RB_Node<KEY, VALUE>(k, v);
        return;
    }

    RB_Node<KEY, VALUE> *currentNode = rootNode_;
    do{
        if (currentNode->key == k) {
            currentNode->value = v;
            return;
        }

        if (k < currentNode->key) {
            if (nullptr == currentNode->leftChild) {
                currentNode->leftChild = new RB_Node<KEY, VALUE>(k, v);
                currentNode->leftChild->parent = currentNode;
                currentNode->leftChild->color = Node_Red;
                currentNode = currentNode->leftChild;
                break;
            } else {
               currentNode = currentNode->leftChild;
               continue;
            }
        }

        if (k > currentNode->key) {
            if (nullptr == currentNode->rightChild) {
                currentNode->rightChild = new RB_Node<KEY, VALUE>(k, v);
                currentNode->rightChild->parent = currentNode;
                currentNode->rightChild->color = Node_Red;
                currentNode = currentNode->rightChild;
                break;
            } else {
               currentNode = currentNode->rightChild;
               continue;
            }
        }
    } while(true);
    InsertBalance(currentNode);
}

template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::Remove(KEY k)
{
    RB_Node<KEY, VALUE> *rmNode = findNode(k);
    if (nullptr == rmNode) {
        return;
    }

    if (nullptr == rmNode->leftChild && nullptr == rmNode->rightChild) {
        if (Node_Red == rmNode->color) {
            if (Pos_Left == findPositionUnderParent(rmNode)) {
                rmNode->parent->leftChild = nullptr;
            }  else {
                rmNode->parent->rightChild = nullptr;
            }
            delete(rmNode);
            return;
        }
    }
}

template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::traverse()
{
    frontTraverse(rootNode_);
}

template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::frontTraverse(RB_Node<KEY, VALUE>* currentNode)
{
    if (currentNode == nullptr) return;

    std::string color = currentNode->color == 0 ? "Red" : "Black";
    std::cout << "Key: " <<currentNode->key << "Value: "<< currentNode->value << "Color: " << color << std::endl;
    frontTraverse(currentNode->leftChild);
    frontTraverse(currentNode->rightChild);
}

template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::InsertBalance(RB_Node<KEY, VALUE> *currentNode)
{
    if (currentNode == rootNode_) {
        currentNode->color = Node_Black;
        return;
    }

    if (currentNode->parent->color == Node_Black) {
        return;
    }

    RB_Node<KEY, VALUE>* uncleNode = findUncleNode(currentNode);
    if (uncleNode != nullptr && uncleNode->color == Node_Red) {
        currentNode->parent->color = Node_Black;
        uncleNode->color = Node_Black;
        currentNode->parent->parent->color = Node_Red;
        InsertBalance(currentNode->parent->parent);
    } else {
        if (findPositionUnderParent(currentNode->parent) == Pos_Left) {
            if (findPositionUnderParent(currentNode) == Pos_Left) {
                currentNode->parent->color = Node_Black;
                currentNode->parent->parent->color = Node_Red;
                rightRotate(currentNode->parent->parent);
            } else {
                leftRotate(currentNode->parent);
                InsertBalance(currentNode->leftChild);
            }
        } else {
            if (findPositionUnderParent(currentNode) == Pos_Right) {
                currentNode->parent->color = Node_Black;
                currentNode->parent->parent->color = Node_Red;
                leftRotate(currentNode->parent->parent);
            } else {
                rightRotate(currentNode->parent);
                InsertBalance(currentNode->rightChild);
            }
        }
    }
}

template<typename KEY, typename VALUE>
RB_Node<KEY, VALUE>* RBTree<KEY, VALUE>::findNode(KEY k)
{
    RB_Node<KEY, VALUE> *currentNode = rootNode_;
    while (currentNode != nullptr) {
        if (k == currentNode->key) {
            break;
        } else if (k < currentNode->key){
            currentNode = currentNode->leftChild;
        } else if (k > currentNode->key) {
            currentNode = currentNode->rightChild;
        }
    }

    return currentNode;
}

template<typename KEY, typename VALUE>
RB_Node<KEY, VALUE>* RBTree<KEY, VALUE>::findUncleNode(RB_Node<KEY, VALUE> *currentNode)
{
    if (nullptr == currentNode) return nullptr;
    RB_Node<KEY, VALUE>* grandParentNode = currentNode->parent->parent;
    RB_Node<KEY, VALUE>* parentNode = currentNode->parent;
    if (grandParentNode->leftChild == parentNode) {
        return grandParentNode->rightChild;
    } else {
        return grandParentNode->leftChild;
    }
}

template<typename KEY, typename VALUE>
NodePosition RBTree<KEY, VALUE>::findPositionUnderParent(RB_Node<KEY, VALUE> *currentNode)
{
    RB_Node<KEY, VALUE>* parent =  currentNode->parent;
    if (parent->leftChild == currentNode) {
        return Pos_Left;
    } else {
        return Pos_Right;
    }
}

template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::leftRotate(RB_Node<KEY, VALUE>* currentNode)
{
    RB_Node<KEY, VALUE>* parent = currentNode->parent;
    RB_Node<KEY, VALUE>* rightChild = currentNode->rightChild;

    rightChild->parent = parent;

    if (parent != nullptr) {
        if (findPositionUnderParent(currentNode) == Pos_Left) {
            parent->leftChild = rightChild;
        }
        else {
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
void RBTree<KEY, VALUE>::rightRotate(RB_Node<KEY, VALUE> *currentNode)
{
    RB_Node<KEY, VALUE>* parent = currentNode->parent;
    RB_Node<KEY, VALUE>* leftChild = currentNode->leftChild;

    leftChild->parent = parent;

    if (parent != nullptr) {
        if (findPositionUnderParent(currentNode) == Pos_Left) {
            parent->leftChild = leftChild;
        }
        else {
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


