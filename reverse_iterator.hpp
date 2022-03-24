/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:04:47 by yer-raki          #+#    #+#             */
/*   Updated: 2022/03/16 15:34:30 by yer-raki         ###   ########.fr       */
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
			reverse_iterator() : _it(iterator_type()) {}
			reverse_iterator(reverse_iterator const & src) : _it(src._it){}
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
				_it--;
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
				_it++;
				return (tmp);
			}
			reference operator*()
			{
				return (*_it);
			}
			pointer operator->()
			{
				return (_it);
			}
			reverse_iterator operator-(difference_type n)
			{
				return (reverse_iterator(_it - (n - 1)));
			}
			reverse_iterator operator+(difference_type n)
			{
				return (reverse_iterator(_it + (n + 1)));
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
		private:
			iterator_type	_it;
	};
}