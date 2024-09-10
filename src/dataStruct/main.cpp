#include "SmallHeap.h"
#include <iostream>


int main(int argc, char *argv[]) 
{
    SmallHeap<int, std::string> heap;
    heap.addNode(7, "li");
    heap.addNode(22, "war");
    heap.addNode(18, "liu");
    heap.addNode(35, "zhang");
    heap.addNode(46, "zhao");
    heap.addNode(8, "qian");
    heap.addNode(99, "huang");
    heap.addNode(65, "lu");
    heap.addNode(64, "hai");
    heap.addNode(15, "wang");
    heap.addNode(14, "sui");
    heap.addNode(17, "kui");
    heap.addNode(48, "ai");
    heap.addNode(26, "chen");
    heap.addNode(1, "peng");

    heap.heapSort();
    heap.traverse();

    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;
    // std::cout << heap.tackFirst().value << std::endl;    
    // std::cout << heap.tackFirst().value << std::endl;

    return 0;
}