#include "avl.hpp"
#include <iostream>
#include <string>

int main()
{
    ft::avl avl;
    avl.avl_insert(10);
    // avl.avl_insert(11);
    // avl.avl_insert(5);
    // avl.avl_insert(7);
    avl.avl_insert(20);
    avl.avl_insert(30);
    avl.avl_insert(40);
    avl.avl_insert(50);
    avl.print2D();
}