/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:14:00 by yer-raki          #+#    #+#             */
/*   Updated: 2022/03/29 18:17:29 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <unistd.h>
#include <iostream>
#include "iterators_traits.hpp"

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t,
        	class Pointer = T*, class Reference = T&>
	class iterator {
		public:
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
	};
	
	template <typename T>
	class random_access_iterator : public ft::iterator<std::random_access_iterator_tag, T>
	{
		public:
        	typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
        	typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
        	typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef	T*																				pointer;
			typedef	T&																				reference;

			// typedef	T														iterator_type;
			// typedef typename ft::iterator_traits<T>::value_type				value_type;
			// typedef typename ft::iterator_traits<T>::iterator_category		iterator_category;
			// typedef typename ft::iterator_traits<T>::difference_type		difference_type;
			// typedef typename ft::iterator_traits<T>::reference				reference;
			// typedef typename ft::iterator_traits<T>::pointer				pointer;
		
		public:
			random_access_iterator() : _ptr(nullptr) {};
			virtual ~random_access_iterator() {};
			random_access_iterator(pointer ptr) : _ptr(ptr) { };
			random_access_iterator(random_access_iterator const & src) : _ptr(src._ptr){};
			pointer	base() const
			{
				return (_ptr);
			}
			operator random_access_iterator<const value_type>() const
            {
                return random_access_iterator<const value_type>(_ptr);
            }
			random_access_iterator & operator=(random_access_iterator const & src)
			{
				if (this != &src)
					_ptr = src._ptr;
				return (*this);
			}
			random_access_iterator & operator++()
			{
				_ptr++;
				return (*this);
			}
			random_access_iterator operator++(int)
			{
				random_access_iterator tmp = *this;
				operator++();
				return (tmp);
			}
			random_access_iterator & operator--()
			{
				_ptr--;
				return (*this);
			}
			random_access_iterator operator--(int)
			{
				random_access_iterator tmp = *this;
				operator--();
				return (tmp);
			}
			reference operator*()
			{
				return (*_ptr);
			}
			pointer operator->()
			{
				return (_ptr);
			}
			random_access_iterator operator-(difference_type n)
			{
				return (random_access_iterator(_ptr - n));
			}
			random_access_iterator operator+(difference_type n)
			{
				return (random_access_iterator(_ptr + n));
			}
			random_access_iterator & operator+=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}
			random_access_iterator & operator-=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}
			reference operator[](difference_type n)
			{
				return (_ptr[n]);
			}
		protected:
			pointer _ptr;
	};
	
    template <class T>
    random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& x)
    {
        return (x + n);
    }
    template <class T>
    typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() - rhs.base());
    }

	template <class T>
    bool operator== (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class T>
    bool operator!= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class T>
    bool operator<  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <class T>
    bool operator<=  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <class T>
    bool operator>  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class T>
    bool operator>=  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
	
}