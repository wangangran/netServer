#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "RBNode.h"
#include "RBNode.cc"

typedef enum{
    Pos_Left = 0,
    Pos_Right,
} NodePosition;

template<typename KEY, typename VALUE>
struct RB_Node;

template<typename KEY, typename VALUE>
class RBTree
{
public:
    explicit RBTree(KEY k, VALUE v);
    ~RBTree();

    void Insert(KEY k, VALUE v);
    void Remove(KEY k);
    void traverse();

private:
    void frontTraverse(RB_Node<KEY, VALUE>* currentNode);
    void InsertBalance(RB_Node<KEY, VALUE>* currentNode);
    RB_Node<KEY, VALUE>* findNode(KEY k);
    RB_Node<KEY, VALUE>* findUncleNode(RB_Node<KEY, VALUE>* currentNode);
    NodePosition findPositionUnderParent(RB_Node<KEY, VALUE>* currentNode);
    void leftRotate(RB_Node<KEY, VALUE>* currentNode);
    void rightRotate(RB_Node<KEY, VALUE>* currentNode);
private:
    RB_Node<KEY, VALUE>* rootNode_ = nullptr;
};

#endif
