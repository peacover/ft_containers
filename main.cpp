// // #include <iterator>
// #include <vector>
// #include <iostream>  
// #include "random_access_iterator.hpp"
// #include "reverse_iterator.hpp"

// int main()  
// {  
//     // std::vector<int> v={1,2,3,4,5};

//     ft::random_access_iterator<int> *rt;
//     ft::reverse_iterator<ft::random_access_iterator<int> > *it;
//      return 0;  
// }  


// #include <cmath>
// #include <iostream>
// #include "enable_if.hpp"
// using namespace std;
 
// class Complex {
// private:
//     double real;
//     double imag;
 
// public:
//     // Default constructor
//     Complex(double r = 0.0, double i = 0.0)
//         : real(r)
//         , imag(i)
//     {
//     }
 
//     // magnitude : usual function style
//     double mag() { return getMag(); }
 
//     // magnitude : conversion operator
//     operator double() { return getMag(); }
//     // operator string() { return raqi(); }
 
// private:
//     // class helper to get magnitude
//     double getMag()
//     {
//         return sqrt(real * real + imag * imag);
//     }   
//     string raqi()
//     {
//         return "RAQI RAQI";
//     }
// };
 
// template<class T>
// void print(T a, typename ft::enable_if<!std::is_integral<T>::value, T>::type = T()){

//     cout << "I AM STRING ";
// }

// template<class T>
// void print(T a, typename ft::enable_if<std::is_integral<T>::value, T>::type = T()){
//     cout << "I AM number";
// }
// int main()
// {
//     // a Complex object
//     Complex com(3.0, 4.0);
 
//     // print magnitude
//     cout << com.mag() << endl;
//     // same can be done like this
//     // com = "fjkhd";
//     cout << com << endl;
//     print("25");
// }


// equal algorithm example
#include <algorithm> 
#include <vector>       
#include <iterator>
#include <iostream>
#include "vector.hpp"
#include "avl.hpp"
#include "pair.hpp"

// bool mypredicate (int i, int j) {
//   return (i==j);
// }

// int main () {
//   int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
//   std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

//   // using default comparison:
//   if ( std::equal (myvector.begin(), myvector.end(), myints) )
//     std::cout << "The contents of both sequences are equal.\n";
//   else
//     std::cout << "The contents of both sequences differ.\n";

//   myvector[3]=81;                                 // myvector: 20 40 60 81 100

//   // using predicate comparison:
//   if ( std::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
//     std::cout << "The contents of both sequences are equal.\n";
//   else
//     std::cout << "The contents of both sequences differ.\n";

//   return 0;
// }

int main()
{
	// int myints[] = {20,40,60,80,100};

	// ft::vector<int>::iterator it;
	// v.insert(v.end() + 2, 77);
	// ft::vector<int>v (5, 88);
	// ft::vector<int>v2;
	// std::vector<int>v2 (5, 88);
	// ft::vector<int>v3;
	// ft::vector<int>v2 (5, 88);
	// ft::vector<int>::iterator it;
	// for (it = v.begin(); it != v.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// 	// break;
	// }
	
	// std::cout << "-------------------------------------" << std::endl;
	
	// for (int i = 0; i < v.size(); ++i)
    //   std::cout << v[i] << std::endl;

	// std::cout << "-------------------------------------" << std::endl;
	// ft::vector<int> v2(v.begin(), v.end());
	// v.insert(v.begin() + 2, v2.begin() + 3, v2.end());
	
	// v.push_back(88);
	// v.push_back(88);
	// v.erase(v.begin() + 2, v.end() - 2 );
	
	// v2.insert(v2.end(), 4, 5555);
	// for (int i = 0; i < v2.size(); ++i)
	// 	std::cout << v2[i] << std::endl;
	// std::cout << "-------------------------------------" << std::endl;
	// v.insert(v.end(), 4, 5555);
	// for (int i = 0; i < v.size(); ++i)
	// 	std::cout << v[i] << std::endl;

	 /*------------------ std::vectors ---------------------*/
        // std::vector<std::string> v1(10, "string2");          // fill constructor
        // std::vector<std::string> v2;                         // empty constructor
        // std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        // std::vector<std::string> v4(v3);                     // copy constructor
        // std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        // /*-----------------------------------------------------*/
        // /*------------------ ft::vectors ---------------------*/
        // ft::vector<std::string> ft_v1(10, "string2");
        // ft::vector<std::string> ft_v2;
        // ft::vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        // ft::vector<std::string> ft_v4(ft_v1);
        // ft::vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        // /*----------------------------------------------------*/
        // if (v1.capacity() == ft_v1.capacity() && v2.capacity() == ft_v2.capacity()
		// 	&& v3.capacity() == ft_v3.capacity() && v4.capacity() == ft_v4.capacity() && v5.capacity() == ft_v5.capacity())
		// 	printf("SUCCESS!\n");
		// else
		// {
		// 	printf ("v1 %ld | %ld \n", v1.capacity(), ft_v1.capacity());
		// 	printf ("v2 %ld | %ld \n", v2.capacity(), ft_v2.capacity());
		// 	printf ("v3 %ld | %ld \n", v3.capacity(), ft_v3.capacity());
		// 	printf ("v4 %ld | %ld \n", v4.capacity(), ft_v4.capacity());
		// 	printf ("v5 %ld | %ld \n", v5.capacity(), ft_v5.capacity());
		// 	printf("FAILED\n");
		// }
		// std::cout << "-------------------------------------------------------------------------------" << std::endl;
		// ft::pair<int, int> p;
		// std::cout << p.first << " | " << p.second << std::endl;
		// std::cout << "-------------------------------------" << std::endl;
		// ft::pair<int, int> p1(12, 88);
		// std::cout << p1.first << " | " << p1.second << std::endl;
		// std::cout << "-------------------------------------" << std::endl;
		// ft::pair<int, int> p2(p1);
		// std::cout << p2.first << " | " << p2.second << std::endl;
		// std::cout << "-------------------------------------------------------------------------------" << std::endl;
		// for (int i = 0; i < v.size(); ++i)
		// 	std::cout << v[i] << std::endl;
		// std::cout << "-------------------------------------" << std::endl;
		// for (int i = 0; i < v2.size(); ++i)
		// 	std::cout << v2[i] << std::endl;
		
}