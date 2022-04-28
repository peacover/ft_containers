#include "avl.hpp"
#include <iostream>
#include <string>

int main()
{
    ft::avl<int, int> tree;

    tree.insert(ft::make_pair(10, 3)); 
    tree.insert(ft::make_pair(30, 4));
    tree.insert(ft::make_pair(20, 3));
    tree.insert(ft::make_pair(40, 5));

    // tree.remove(20);
    tree.print2D();

}