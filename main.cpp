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
#include <iostream>     // std::cout
#include <algorithm>    // std::equal
#include <vector>       // std::vector

bool mypredicate (int i, int j) {
  return (i==j);
}

int main () {
  int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
  std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

  // using default comparison:
  if ( std::equal (myvector.begin(), myvector.end(), myints) )
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  myvector[3]=81;                                 // myvector: 20 40 60 81 100

  // using predicate comparison:
  if ( std::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  return 0;
}