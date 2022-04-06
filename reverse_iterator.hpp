/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:04:47 by yer-raki          #+#    #+#             */
/*   Updated: 2022/04/02 13:15:09 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once 

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "random_access_iterator.hpp"
namespace ft
{
	template <typename T>
	class reverse_iterator
	{
		public:
			typedef	T														iterator_type;
			typedef typename ft::iterator_traits<T>::value_type				value_type;
			typedef typename ft::iterator_traits<T>::iterator_category		iterator_category;
			typedef typename ft::iterator_traits<T>::difference_type		difference_type;
			typedef typename ft::iterator_traits<T>::reference				reference;
			typedef typename ft::iterator_traits<T>::pointer				pointer;
		public:
			reverse_iterator() : _it() {};
			explicit reverse_iterator(iterator_type x)
			{
				iterator_type tmp;
				tmp = x;
				_it = --tmp;
			}
			template <class U>
			reverse_iterator(const reverse_iterator<U>& u)
			{
				_it = --(u.base());
			}

			// rbegin.base() = end | rend.base() = begin
			iterator_type base() const
			{
				iterator_type tmp = _it;
				++tmp;
				return (tmp);
			}
			reverse_iterator & operator++()
			{
				_it--;
				return (*this);
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				// call operator++()
				++(*this);
				return (tmp);
			}
			reverse_iterator & operator--()
			{
				_it++;
				return (*this);
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}
			reference operator*()
			{
				return (*_it);
			}
			pointer operator->()
			{
				return &(operator*());
			}
			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(_it + (n + 1)));
			}
			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(_it - (n - 1)));
			}
			reverse_iterator & operator+=(difference_type n)
			{
				_it -= n;
				return (*this);
			}
			reverse_iterator & operator-=(difference_type n)
			{
				_it += n;
				return (*this);
			}
			reference operator[](difference_type n)
			{
				return (_it[-n]);
			}
		protected:
			iterator_type	_it;
	};
	template <class T>
    reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T>& x)
    {
        return (x + n);
    }
    template <class T>
    typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs)
    {
        return (rhs.base() - lhs.base());
    }

	template <class T>
    bool operator== (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class T>
    bool operator!= (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class T>
    bool operator<  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class T>
    bool operator<=  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template <class T>
    bool operator>  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <class T>
    bool operator>=  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
}