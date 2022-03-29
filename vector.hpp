/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:33:02 by yer-raki          #+#    #+#             */
/*   Updated: 2022/03/29 18:27:47 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <unistd.h>
#include <iostream>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T                                           value_type;
			typedef Allocator                                   allocator_type;
			typedef std::size_t                                 size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		public:
			/////////////////// MEMBER FUNCTIONS //////////////////
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				_size = 0;
				_capacity = 0;
				_data = nullptr;
				_alloc = alloc;
			}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				size_t i;

				_alloc = alloc;	
				_capacity = n;
				_data = _alloc.allocate(n);
				for (i = 0; i < n; i++)
					_alloc.construct(_data + i, val);
				if (!i)
					_data = nullptr;
				_size = i;
			}
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			 		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				size_t n = 0;
				_alloc = alloc;
				for (InputIterator it = first; it != last; it++)
					n++;
				if (!n)
				{
					_data = nullptr;
					_size = 0;
					_capacity = 0;
				}
				else
				{
					_capacity = n + 1;
					_data = _alloc.allocate(n + 1);
					for (size_t i = 0; i < n; i++)
					{
						_alloc.construct(_data + i, *first);
						_size = i;
						first++;
					}
					_size++;
				}
			}
			vector(const vector& x)
			{
				// _size = 0;
				// _capacity = 0;
				// _data = nullptr;
				*this = x;
			}
			~vector()
			{
				_alloc.deallocate(_data, _capacity);
			}
			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					_alloc.deallocate(_data, _capacity);
					_size = x._size;
					_capacity = x._capacity;
					_data = _alloc.allocate(x._size);
					for (size_t i = 0; i < x._size; i++)
					{
						_alloc.construct(_data + i, x._data + i);
					}
					// for (size_t i = 0; i < x._size; i++)
					// 	_data[i] = x._data[i];
				}
				return (*this);
			}
			// //////////////////////////////////////////////////////////////
			// ///////////////// ITERATORS ////////////////
			iterator begin()
			{
				return (iterator(_data));
			}
			const_iterator begin() const
			{
				return (iterator(_data));
			}
			iterator end()
			{
				return (iterator(_data + _size));
			}
			const_iterator end() const
			{
				return (iterator(_data + _size));
			}
			reverse_iterator rbegin()
			{
				// return (reverse_iterator(iterator(_data + _size)));
				return (reverse_iterator(end()));
			}
			const_reverse_iterator rbegin() const
			{
				return (reverse_iterator(end()));
			}
      		reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const
			{
				return (reverse_iterator(begin()));
			}
			
			///////////////////////////////////////////////////
			///////////// CAPACITY ////////////
			size_type size() const
			{
				return (_size);
			}
			size_type max_size() const
			{
				return (_alloc.maxsize());
			}
			size_type capacity() const
			{
				return (_capacity);
			}
			bool empty() const
			{
				if (!_size)
					return (true);
				return (false);
			}
			void reserve (size_type n)
			{
				if (n <= _capacity)
					return;
				_capacity = n;
				value_type *tmp = _alloc.allocate(n);
				for (size_t i = 0; i < size(); i++)
					tmp[i] = _data[i];
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			void resize (size_type n, value_type val = value_type())
			{
				if (n > _size)
				{
					if (n > _capacity)
						reserve(n);
					while (_size < n)
						_data[_size++] = val;
				}
				else
				{
					value_type *tmp = _alloc.allocate(n);
					for (size_t i = 0; i < n; i++)
						tmp[i] = _data[i];
					_alloc.deallocate(_data, _capacity);
					_data = tmp;
				}
			}
			///////////////////////////////////////////////////
			///////////////// ELEMENT ACCESS /////////////////
			reference operator[] (size_type n)
			{
				return (_data[n]);
			}
			const_reference operator[] (size_type n) const
			{
				return (_data[n]);
			}
			reference at (size_type n)
			{
				if (n > _size)
					throw ("Out of Range error");
				else
					return (_data[n]);
			}
			const_reference at (size_type n) const
			{
				if (n > _size)
					throw ("Out of Range error");
				else
					return (_data[n]);
			}
			reference front()
			{
				return (*_data);
			}
			const_reference front() const
			{
				return (*_data);
			}
			reference back()
			{
				return (*(_data + _size - 1));
			}
			const_reference back() const
			{
				return (*(_data + _size - 1));
			}
			//////////////////////////////////////////////////

			////////////////// MODIFIERS /////////////////////
			
			// template <class InputIterator>
  			// void assign (InputIterator first, InputIterator last,
			//   			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			// {
								  
			// }
			// void assign (size_type n, const value_type& val)
			// {
				
			// }
			
			void push_back (const value_type& val)
			{
				resize(_size + 1);
				_data[_size - 1] = val;
			}
			void pop_back()
			{
				resize(_size - 1);
			}

			// iterator insert (iterator position, const value_type& val)
			// {
			// 	size_type dist = position - begin();
			// 	if ()
				
			// }
			// void insert (iterator position, size_type n, const value_type& val)
			// {
				
			// }
			// template <class InputIterator>
    		// void insert (iterator position, InputIterator first, InputIterator last,
			// 			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			// {
				
			// }

			// iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);

			void swap (vector& x)
			{
				value_type	tmp_data;
				size_type	tmp_size;
				size_type	tmp_capacity;
				allocator_type tmp_allocator_type;

				tmp_data = _data;
				_data = x._data;
				x._data = tmp_data;
				
				tmp_size = _size;
				_size = x._size;
				x._size = tmp_size;

				tmp_capacity = _capacity;
				_capacity = x._capacity;
				x._capacity = tmp_capacity;

				tmp_allocator_type = _alloc;
				_alloc = x._alloc;
				x._alloc = tmp_allocator_type;
				
				
			}
			void clear()
			{
				_alloc.deallocate(_data, _capacity);
			}

			//////////////////////////////////////////////////
			///////////////// ALLOCATOR //////////////////////
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
			////////////////////////////////////////////////////
		private:
			size_type		_size;
			size_type		_capacity;
			value_type		*_data;
			allocator_type	_alloc;
	};
	///////////////// RELATIONAL OPERATORS //////////////////
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}
	
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs || lhs < rhs)
			return (true);
		return (false);
	}


	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs || lhs > rhs)
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
	////////////////////////////////////////////////////////
}
