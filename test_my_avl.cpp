
#include "avl.hpp"
#include "map.hpp"
#include <map>

int main()
{
    // ft::avl<int, int> tree;

    // tree.insert(ft::make_pair(10, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();

    // tree.insert(ft::make_pair(30, 4));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();

    // tree.insert(ft::make_pair(40, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();

    // tree.insert(ft::make_pair(5, 4));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();

    // tree.insert(ft::make_pair(20, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    
    // tree.insert(ft::make_pair(50, 5));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    
    // tree.insert(ft::make_pair(18, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    // tree.insert(ft::make_pair(0, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    // tree.insert(ft::make_pair(55, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    // tree.insert(ft::make_pair(1, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    // tree.insert(ft::make_pair(4, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    // tree.insert(ft::make_pair(190, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    // tree.insert(ft::make_pair(9, 3));
    // std::cout << "------------------------------------" << std::endl;
    // std::cout << tree.get_root()->data->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;
    // tree.print2D();
    // tree.remove(20);
    // tree.print2D();

    // std::cout << "------------------------------------" << std::endl;

    // std::map<int, int> map;
    // map.insert(std::make_pair(10, 3));
    // map.insert(std::make_pair(30, 4));
    // map.insert(std::make_pair(5, 4));
    // map.insert(std::make_pair(20, 3));
    // map.insert(std::make_pair(40, 5));

    // map.erase(5);
    // std::map<int, int>::iterator it;
    // for (it = map.begin(); it != map.end(); it++)
    // {
    //     std::cout << it->first << std::endl;
    // }
    // it = map.lower_bound(50);
    // std::cout << it->first << " | " << it->second << std::endl;
    // m.insert(std::make_pair(10, 3));
    // m.insert(std::make_pair(30, 4));
    // m.insert(std::make_pair(5, 4));
    // m.insert(std::make_pair(20, 3));
    // m.insert(std::make_pair(40, 5));
    // map = m;
    // std::map<int, int>::iterator it = m.begin();
    // std::cout << (it)->first << std::endl;
    // std::cout << "------------------------------------" << std::endl;

        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m1;
        ft::map<int, std::string> ft_m2;
        m1[0] = "stringsrtring";
        ft_m1[0] = "stringsrtring";
        std::map<int, std::string>::iterator it1;
        ft::map<int, std::string>::iterator it2;
        m1.empty();
        ft_m1.empty();

        m2.empty();
        ft_m2.empty();
        

        std::cout << "------------------------------------" << std::endl;
        for (it1 = m2.begin(); it1 != m2.end(); it1++)
        {
            std::cout << it1->first << " | " << it1->second << std::endl;
        }

        std::cout << "------------------------------------" << std::endl;
        for (it2 = ft_m2.begin(); it2 != ft_m2.end(); it2++)
        {
            std::cout << it2->first << " | " << it2->second << std::endl;
        }
    // ft::map<int, int> map2;
    // map2.insert(ft::make_pair(10, 3));
    // map2.insert(ft::make_pair(30, 4));
    // map2.insert(ft::make_pair(5, 4));
    // map2.insert(ft::make_pair(20, 3));
    // map2.insert(ft::make_pair(10, 5));
    // map2.insert(ft::make_pair(40, 5));
    // map2.insert(ft::make_pair(10, 5));

    // // // it2 = map2.lower_bound(6);
    // // std::cout << it2->first << " | " << it2->second << std::endl;
    // map2.erase(30);
    // for (it2 = map2.begin(); it2 != map2.end(); it2++)
    // {
    //     std::cout << it2->first  << " | " << it2->second << std::endl;
    // }
    // // std::cout << "------------------------------------" << std::endl;
    // std::cout << (--it2)->first << std::endl;
    // std::cout << (--it2)->first << std::endl;
    // // std::cout << "------------------------------------" << std::endl;
    // std::cout << (++it2)->first << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // {
        // std::map<int, std::string> m;
        // ft::map<int, std::string> ft_m;
        // for (size_t i = 0; i < 1e6; ++i)
        // {
        //     // m.insert(std::make_pair(i, "value"));
        //     ft_m.insert(ft::make_pair(i, "value"));
        //     std::cout << i << '\n';
        // }
    // // }


}