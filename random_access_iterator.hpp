/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:14:00 by yer-raki          #+#    #+#             */
/*   Updated: 2022/03/09 21:20:21 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <iostream>
#include <algorithm>

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
		
		public:
			random_access_iterator() : _ptr(nullptr) {}
			~random_access_iterator() {}
			random_access_iterator(pointer ptr) : _ptr(ptr) { }
			random_access_iterator(random_access_iterator const & src) : _ptr(src._ptr){}
			random_access_iterator & operator=(random_access_iterator const & src)
			{
				if (this != &src)
					_ptr = src._ptr;
				return (*this);
			}
			bool operator==(random_access_iterator const & src) const { return (_ptr == src._ptr); }
			bool operator!=(random_access_iterator const & src) const { return (_ptr != src._ptr); }
			bool operator>(random_access_iterator const & src) const { return (_ptr > src._ptr); }
			bool operator>=(random_access_iterator const & src) const { return (_ptr >= src._ptr); }
			bool operator<(random_access_iterator const & src) const { return (_ptr < src._ptr); }
			bool operator<=(random_access_iterator const & src) const { return (_ptr <= src._ptr); }
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
		private:
			pointer _ptr;
	};
	
}