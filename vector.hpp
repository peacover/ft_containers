/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:33:02 by yer-raki          #+#    #+#             */
/*   Updated: 2022/04/06 02:22:19 by yer-raki         ###   ########.fr       */
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
					_capacity = n;
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
						_data[i] = x._data[i];
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
				return (reverse_iterator(iterator(_data + _size)));
				// return (reverse_iterator(end()));
			}
			const_reverse_iterator rbegin() const
			{
				// return (reverse_iterator(end()));
				return (reverse_iterator(iterator(_data + _size)));
			}
	  		reverse_iterator rend()
			{
				// return (reverse_iterator(begin()));
				return (reverse_iterator(iterator(_data)));
			}
			const_reverse_iterator rend() const
			{
				// return (reverse_iterator(begin()));
				return (reverse_iterator(iterator(_data)));
			}
			
			///////////////////////////////////////////////////
			///////////// CAPACITY ////////////
			size_type size() const
			{
				return (_size);
			}
			size_type max_size() const
			{
				return (_alloc.max_size());
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
				value_type *tmp = _alloc.allocate(n);
				for (size_t i = 0; i < _size; i++)
					tmp[i] = _data[i];
				_capacity = n;
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			void resize (size_type n, value_type val = value_type())
			{
				if (n > _size)
				{
					if (n > _capacity * 2)
						reserve(n);
					else if (n >= _capacity)
						reserve(_capacity * 2);
					while (_size < n)
						_data[_size++] = val;
				}
				else 
				{
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_data + i);
					_size = n;
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
					throw std::out_of_range("Out of Range error");
				else
					return (_data[n]);
			}
			const_reference at (size_type n) const
			{
				if (n > _size)
					throw std::out_of_range("Out of Range error");
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
			
			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last,
			  			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				difference_type n = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				if ((unsigned long)n > _capacity)
					reserve(n);
				_size = n;
				for (size_t i = 0; i < _size; i++)
				{
					_alloc.construct(_data + i, *first);
					first++;
				}
			}
			void assign (size_type n, const value_type& val)
			{
				if (n > _capacity)
					reserve(n);
				_size = n;
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(_data + i, val);
			}
			
			void push_back (const value_type& val)
			{
				if (!_size)
					reserve (1);
				else if (_size + 1 > _capacity)
					reserve (_capacity * 2);
				_data[_size] = val;
				_size++;
			}
			void pop_back()
			{
				_size--;
			}

			iterator insert (iterator position, const value_type& val)
			{
				difference_type dist = position - begin();

				if (!_size)
				{
					resize(1);
					_alloc.construct(_data, val);
					return (begin());
				}
				else if (_size + 1 > _capacity)
					reserve(_capacity * 2);
				_size++;
				for (long i = _size; i > dist; i--)
					_data[i] = _data[i - 1];
				_alloc.construct(_data + dist, val);
				return (begin() + dist);
			}
			void insert (iterator position, size_type n, const value_type& val)
			{
				difference_type dist = position - begin();

				if (!_size)
					reserve(n);
				else if (_size + n > _capacity)
				{
					if (n + _size > _capacity * 2)
						reserve(_size + n);
					else
						reserve(_capacity * 2);
				}
				for (long i = _size - 1; i >= dist; i--)
					_data[i + n] = _data[i];
				for (size_t i = 0; i < n; i++)
					_data[dist + i] = val;
				_size += n;
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				difference_type dist = position - begin();
				// difference_type n = last - first;
				difference_type n = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				if (!_size)
					reserve(n);
				else if (_size + n > _capacity)
				{
					if (n + _size >= _capacity * 2)
						reserve(_size + n);
					else
						reserve(_capacity * 2);
				}
				for (long i = _size - 1; i >= dist; i--)
					_data[i + n] = _data[i];
				for (long i = 0; i < n; i++)
				{
					_data[dist + i] = *first;
					first++;
				}
				_size += n;
			}

			iterator erase (iterator position)
			{
				difference_type dist = position - begin();
				if (_size)
					_size--;
				for (size_t i = dist; i < _size; i++)
					_data[i] = _data[i + 1];
				return (begin() + dist);
			}
			iterator erase (iterator first, iterator last)
			{
				difference_type n = 0;
				size_t i = 0;
				while (last != end())
				{
					*first = *last;
					first++;
					last++;
					i++;
				}
				for (iterator it = first; it != last; it++)
					n++;
				_size -= n;
				return (first - i);
			}

			void swap (vector& x)
			{
				value_type	*tmp_data;
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
				_size = 0;
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
