#ifndef _RBNODE_H_
#define _RBNODE_H_

typedef enum {
    Node_Red = 0,
    Node_Black,
} Node_Color;

template<typename KEY, typename VALUE>
struct RB_Node{
    RB_Node(KEY k, VALUE v);
    ~RB_Node();
    RB_Node*    leftChild;
    RB_Node*    rightChild;
    RB_Node*    parent;
    Node_Color  color;
    KEY         key;
    VALUE       value;
};

#endif
