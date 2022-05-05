#include "avl.hpp"
#include "map.hpp"
#include <map>

int main()
{
    // ft::avl<int, int> tree;

    // tree.insert(ft::pair<int, int>(10, 3)); 
    // tree.insert(ft::make_pair(30, 4));
    // tree.insert(ft::make_pair(5, 4));
    // tree.insert(ft::make_pair(20, 3));
    // tree.insert(ft::make_pair(40, 5));
    // tree.insert(ft::make_pair(18, 3));

    // tree.remove(20);
    // tree.print2D();

    std::cout << "------------------------------------" << std::endl;

    std::map<int, int> m;
    // m.insert(std::make_pair(10, 3));
    // m.insert(std::make_pair(30, 4));
    // m.insert(std::make_pair(5, 4));
    // m.insert(std::make_pair(20, 3));
    // m.insert(std::make_pair(40, 5));
    // map = m;
    // std::map<int, int>::iterator it = m.begin();
    // std::cout << (it)->first << std::endl;
    std::cout << "------------------------------------" << std::endl;
    ft::map<int, int> map;
    // map.begin();
    map.insert(ft::make_pair(10, 3));
    map.insert(ft::make_pair(30, 4));
    map.insert(ft::make_pair(5, 4));
    map.insert(ft::make_pair(20, 3));
    map.insert(ft::make_pair(40, 5));

    ft::map<int, int> map2(map);
    ft::map<int, int>::iterator it2 = map2.end();
    // for (int i = 0; i < 5; i++)
    // {
    //     std::cout << (it2++)->first << std::endl;
    // }
    std::cout << (it2)->first << std::endl;
    // map.insert(ft::make_pair(10, 3));
}