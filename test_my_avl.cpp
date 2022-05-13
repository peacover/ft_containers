#include "avl.hpp"
#include "map.hpp"
#include <map>
#include <vector>
#include <random>

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		std::cout << "------------------------------------" << std::endl;
		std::cout << first1->first << " | " << first2->first << std::endl;
		std::cout << first1->second << " | " << first2->second << std::endl;
		std::cout << "------------------------------------" << std::endl;
		if (first1->first != first2->first || first1->second != first2->second)
			return false;
	}
	return true;
}
struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};

bool fncomp(char lhs, char rhs) { return lhs < rhs; }
int main()
{
//     ft::avl<int, int> tree;

//     tree.insert(ft::make_pair(10, 3));
//     std::cout << "------------------------------------" << std::endl;
//     std::cout << tree.get_root()->data->first << std::endl;
//     std::cout << "------------------------------------" << std::endl;
//     tree.print2D();

//     tree.insert(ft::make_pair(30, 4));
//     std::cout << "------------------------------------" << std::endl;
//     std::cout << tree.get_root()->data->first << std::endl;
//     std::cout << "------------------------------------" << std::endl;
//     tree.print2D();

//     tree.insert(ft::make_pair(40, 3));
//     std::cout << "------------------------------------" << std::endl;
//     std::cout << tree.get_root()->data->first << std::endl;
//     std::cout << "------------------------------------" << std::endl;
//     tree.print2D();

//     tree.insert(ft::make_pair(5, 4));
//     std::cout << "------------------------------------" << std::endl;
//     std::cout << tree.get_root()->data->first << std::endl;
//     std::cout << "------------------------------------" << std::endl;
//     tree.print2D();
//     std::cout << "------------------------------------" << std::endl;
//     std::cout << "------------------------------------" << std::endl;
//     std::cout << "------------------------------------" << std::endl;

	// std::cout << tree.find(tree.get_root(), 0)->data->second << std::endl;
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

		// std::map<int, std::string> m1;
		// std::map<int, std::string> m2;
		// ft::map<int, std::string> ft_m1;
		// ft::map<int, std::string> ft_m2;
		// m1[0] = "stringsrtring";
		// ft_m1[0] = "stringsrtring";
		// std::map<int, std::string>::iterator it1;
		// ft::map<int, std::string>::iterator it2;
		// m1.empty();
		// ft_m1.empty();

		// m2.empty();
		// ft_m2.empty();
		

		// std::cout << "------------------------------------" << std::endl;
		// for (it1 = m2.begin(); it1 != m2.end(); it1++)
		// {
		//     std::cout << it1->first << " | " << it1->second << std::endl;
		// }

		// std::cout << "------------------------------------" << std::endl;
		// for (it2 = ft_m2.begin(); it2 != ft_m2.end(); it2++)
		// {
		//     std::cout << it2->first << " | " << it2->second << std::endl;
		// }
	// ft::map<int, int> map2;
	// map2.insert(ft::make_pair(10, 3));
	// map2.insert(ft::make_pair(30, 4));
	// map2.insert(ft::make_pair(5, 4));
	// map2.insert(ft::make_pair(20, 3));
	// map2.insert(ft::make_pair(10, 5));
	// map2.insert(ft::make_pair(40, 5));
	// ft::map<int, int>::iterator it2;

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
	// std::cout << "------------------------------------" << std::endl;

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

	// std::map<int, std::string> m1;
	// std::map<int, std::string> m2;
	// ft::map<int, std::string> ft_m2;
	// ft::map<int, std::string> ft_m1;
	// for (int i = 0; i < 10; ++i)
	// {
	//     m2.insert(std::make_pair(i, "string2"));
	//     ft_m2.insert(ft::make_pair(i, "string2"));
	// }
	// m1 = m2;
	// ft_m1 = ft_m2;
	
	// m2.begin()->second = "hello";
	// ft_m2.begin()->second = "hello";

	// std::cout << m1.begin()->second << std::endl;
	// std::cout << ft_m1.begin()->second << std::endl;
	// std::cout << m2.begin()->second << std::endl;
	// std::cout << ft_m2.begin()->second << std::endl;

	// bool cond(true);
	//     {
	//         /*------------------ std::maps ---------------------*/
	//         std::map<int, std::string> m1;
	//         ft::map<int, std::string> ft_m1;
	//         for (size_t i = 0; i < 16; i++)
	//         {
	//             m1.insert(std::make_pair(i, "string2"));
	//             ft_m1.insert(ft::make_pair(i, "string2"));
	//         }



	//         for (size_t i = 1e1; i < 15; i += 10)
	//             m1.find(i);

	//         /*-----------------------------------------------------*/
	//         /*------------------ ft::maps ---------------------*/
	//         for (size_t i = 1e1; i < 15; i += 10)
	//             ft_m1.find(i);
	//         /*----------------------------------------------------*/
	//     }

		bool cond = true;
	 	std::map<int, std::string> m3;
        ft::map<int, std::string> ft_m3;
        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);
		ft::map<int, std::string>::iterator it;

        for (size_t i = 0; i < 1e6; i++)
        {
            m3.insert(std::make_pair(i, "string1"));
            ft_m3.insert(ft::make_pair(i, "string1"));
        }

        for (size_t i = 0; i < 1e6; ++i)
        {
            int n = distr(generator);
			// std::cout << "------------------------------------" << std::endl;
			// std::cout << "erase : " << i << std::endl;
			// ft_m3._tree.print2D();
            int ret1 = m3.erase(n);
            int ret2 = ft_m3.erase(n);

            if (ret1 != ret2)
            {
                cond = false;
                break;
            }
        }
		// ft_m3._tree.print2D();
		// std::cout << "------------------------------------" << std::endl;
		// m3.erase(1);
		// ft_m3.erase(1);
		// if (!ft_m3.empty())
        // {
        //     ft_m3.erase(ft_m3.begin(), ft_m3.end());
        //     ft_m3.erase(ft_m3.begin(), ft_m3.end());
        // }
        if (!m3.empty())
        {
            m3.erase(m3.begin(), m3.end());
            m3.erase(m3.begin(), m3.end());
        }
		// ft_m3._tree.print2D();
		if (!ft_m3.empty())
        {
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
        }
        // if (!ft_m3.empty())
        // {
		// 	// int count = 0;
        //     // ft_m3.erase(ft_m3.begin(), ft_m3.end());
        //     // ft_m3.erase(ft_m3.begin(), ft_m3.end());
		// 	// for (it = ft_m3.begin(); it != ft_m3.end(); it++){
	    //     for (size_t i = 0; i < 1e6; i++){

		// 		// std::cout <<  count++ << std::endl;
		// 		// std::cout << "------------------------------------" << std::endl;
		// 		// std::cout << "erase : " << i << std::endl;
		// 		// ft_m3._tree.print2D();
		// 		ft_m3.erase(i);
		// 		m3.erase(i);
		// 		// std::cout << "------------------------------------" << std::endl;
		// 		// break;
		// 	}
        // }

		// for (size_t i = 0; i < 16; i++)
		// {
		// 	// std::cout <<  count++ << std::endl;
		// 	std::cout << "------------------------------------" << std::endl;
		// 	std::cout << "erase : " << i << std::endl;
		// 	if (i == 9)
		// 	{
		// 		ft_m3._tree.print2D();
		// 		ft_m3.erase(i);
		// 	}
		// 	else
		// 	{
		// 		ft_m3._tree.print2D();
		// 		ft_m3.erase(i);
		// 	}
		// 	std::cout << "------------------------------------" << std::endl;
		// }
		// std::cout << "RESULT  : " << std::endl;
		// for (it = ft_m3.begin(); it != ft_m3.end(); it++)
		// {
		// 	ft_m3.erase(it->first);
		// 	// std::cout << it->first << " | " << it->second << std::endl;
		// }
		std::cout << "SIZE  : " << m3.size() << " M_SIZE : " << ft_m3.size() << std::endl;
        // cond = cond && (m3.size() == ft_m3.size() && compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));
        std::cout << (cond);
}

