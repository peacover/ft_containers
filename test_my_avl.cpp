#include "avl.hpp"
#include "map.hpp"
int main()
{
    ft::avl<int, int> tree;

    tree.insert(ft::pair<int, int>(10, 3)); 
    tree.insert(ft::make_pair(30, 4));
    tree.insert(ft::make_pair(5, 4));
    tree.insert(ft::make_pair(20, 3));
    tree.insert(ft::make_pair(40, 5));
    tree.insert(ft::make_pair(18, 3));

    tree.remove(20);
    tree.print2D();

    std::cout << "------------------------------------" << std::endl;

    ft::map<int, int> map;
    // map['a'] = 1;
    // map['b'] = 2;
    // map['c'] = 3;

}