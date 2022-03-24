/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:49:02 by yer-raki          #+#    #+#             */
/*   Updated: 2022/03/19 17:16:19 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

namespace ft
{
    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };
}


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
//     print("25");
// }