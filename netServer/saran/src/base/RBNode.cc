#include "RBNode.h"

template<typename KEY, typename VALUE>
RB_Node<KEY, VALUE>::RB_Node(KEY k, VALUE v) : key(k),
    value(v),
    leftChild(nullptr),
    rightChild(nullptr),
    parent(nullptr),
    color(Node_Black)
{

}

template<typename KEY, typename VALUE>
RB_Node<KEY, VALUE>::~RB_Node()
{

}
