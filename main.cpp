// #include <iterator>
#include <vector>
#include <iostream>  
#include "random_access_iterator.hpp"

using namespace ft;

int main()  
{  
    std::vector<int> v={1,2,3,4,5};  
    ft::random_access_iterator<int> itr;  
    itr = v.begin();
    for(int i=0;i<5;i++)           // Traversal without using an iterator.  
    {  
        std::cout<<v[i]<<" ";  
    }  
    std::cout<<'\n';  
    // for(itr=v.begin();itr!=v.end();itr++)  // Traversal by using an iterator.  
    // {  
    //     std::cout<<*itr<<" ";  
    // }  
    // v.push_back(10);  
    // std::cout<<'\n';  
    //  for(int i=0;i<6;i++)  
    // {  
    //     std::cout<<v[i]<<" ";  
    // }  
    // std::cout<<'\n';  
    //  for(itr=v.begin();itr!=v.end();itr++)  
    // {  
    //     std::cout<<*itr<<" ";  
    // }  
     return 0;  
}  