/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 05:16:53 by yer-raki          #+#    #+#             */
/*   Updated: 2022/05/13 07:00:24 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.hpp"
namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef typename Container::size_type size_type;
            
            explicit stack (const container_type& ctnr = container_type())
            {
                _container = ctnr;
            }
            bool empty() const
            {
                return _container.empty();
            }
            size_type size() const
            {
                return _container.size();
            }
            value_type& top()
            {
                return _container.back();
            }
            const value_type& top() const
            {
                return _container.back();
            }
            void push (const value_type& val)
            {
                _container.push_back(val);
            }
            void pop()
            {
                _container.pop_back();
            }

            container_type get_container() const
            {
                return _container;
            }
        protected:
            container_type _container;
    };
    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs.get_container() == rhs.get_container();
    }
    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs.get_container() != rhs.get_container();
    }
    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs.get_container() < rhs.get_container();
    }
    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs.get_container() <= rhs.get_container();
    }
    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs.get_container() > rhs.get_container();
    }
    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs.get_container() >= rhs.get_container();
    }  
}