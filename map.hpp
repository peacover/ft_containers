/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:34:31 by yer-raki          #+#    #+#             */
/*   Updated: 2022/05/06 18:31:01 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "avl.hpp"

namespace ft
{
	template < class Key,                                  			// map::key_type
		class T,                                       			// map::mapped_type
		class Compare = std::less<Key>,                     		// map::key_compare
		class Alloc = std::allocator<ft::pair<const Key,T> >		// map::allocator_type
		>
	class map
	{
		public:
			typedef Key                                     					key_type;
			typedef T                                       					mapped_type;
			typedef typename ft::pair<const key_type,mapped_type>       		value_type;
			typedef Compare                                 					key_compare;
			typedef Alloc                                   					allocator_type;
			typedef value_type                             						&reference;
			typedef const value_type                       						&const_reference;
			typedef value_type  		                       					*pointer;
			typedef const value_type											*const_pointer;
			
			typedef typename ft::avl<Key, T, Compare, Alloc> 					tree;
			typedef ft::Node<value_type>                                		node_type;
			typedef node_type                                					*node_pointer;
			
			typedef ft::bidirectional_iterator<value_type, tree, node_type>   			iterator;
			typedef ft::bidirectional_iterator<const value_type, tree, const node_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>          					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>    					const_reverse_iterator;
			typedef ptrdiff_t                               					difference_type;
			typedef size_t                                  					size_type;

			typedef class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			} value_compare;

		public:
			//////////////////////// MEMBER FUNCTIONS ////////////////////////
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				_comp = comp;
				_alloc = alloc;
			}
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
			{
				_comp = comp;
				_alloc = alloc;
				insert(first, last);
			}
			map (const map& x)
			{
				_comp = x._comp;
				_alloc = x._alloc;
				_tree = x._tree;
			}
			~map()
			{
				_tree.~avl();
			}

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					_comp = x._comp;
					_alloc = x._alloc;
					_tree = x._tree;
				}
				return *this;
			}
			/////////////////////// ITERATORS ////////////////////////////////
			iterator begin()
			{
				return iterator(_tree.begin());
			}
			const_iterator begin() const
			{
				return const_iterator(_tree.begin());
			}

			iterator end()
			{
				return iterator(_tree.end());
			}
			const_iterator end() const
			{
				return const_iterator(_tree.end());
			}
			
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
			
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}
			////////////////////////// CAPACITY //////////////////////////////

			bool empty() const
			{
				return _tree.empty();
			}
			size_type size() const
			{
				return _tree.size();
			}
			size_type max_size() const
			{
				return _tree.max_size();
			}

			////////////////////////// ELEMENT ACCESS ////////////////////////
			
			mapped_type& operator[] (const key_type& k)
			{
				node_pointer sec = _tree.find(k);
				return (sec->second);
			}

			////////////////////////// MODIFIERS /////////////////////////////
			
				pair<iterator,bool> insert (const value_type& pair)
				{
					bool sec = _tree.insert(pair);
					iterator first = iterator(_tree.find(pair.first));
					return (ft::make_pair(first, sec));
				}
				iterator insert (iterator position, const value_type& val)
				{
					(void)position,
					insert(val);
					return iterator(_tree.find(val.first));
				}
				template <class InputIterator>
				void insert (InputIterator first, InputIterator last)
				{
					while (first != last)
					{
						insert(*first);
						++first;
					}
					return;
				}
				
				void erase (iterator position)
				{
					_tree.remove(position._node->_data);
				}
				size_type erase (const key_type& k)
				{
					return _tree.remove(k);
				}
				void erase (iterator first, iterator last)
				{
					while (first != last)
					{
						remove(*first);
						++first;
					}
					return;
				}

				void swap (map& x)
				{
					map tmp;

					tmp = x._tree;
					x._tree = _tree;
					_tree = tmp;
					return;
				}

				void clear()
				{
					_tree.clear();
				}
			
			////////////////////////// OBSERVERS /////////////////////////////
			
			key_compare key_comp() const
			{
				return (_comp);
			}
			value_compare value_comp() const
			{
				return (value_compare(_comp));
			}

			////////////////////////// OPERATIONS ////////////////////////////
			
			iterator find (const key_type& k)
			{
				return iterator(_tree.find(k));
			}
			const_iterator find (const key_type& k) const
			{
				return const_iterator(_tree.find(k));
			}

			size_type count (const key_type& k) const
			{
				return _tree.contains(k);
			}
			
			// iterator lower_bound (const key_type& k);
			// const_iterator lower_bound (const key_type& k) const;
			
			// iterator upper_bound (const key_type& k);
			// const_iterator upper_bound (const key_type& k) const;

			// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			// pair<iterator,iterator>             equal_range (const key_type& k);

			////////////////////////// ALLOCATOR //////////////////////////////////

			allocator_type get_allocator() const
			{
				return _tree.get_pair_allocator();
			}

		private:
			tree		_tree;
			Compare		_comp;
			Alloc		_alloc;
	};
}
