/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:34:31 by yer-raki          #+#    #+#             */
/*   Updated: 2022/04/29 06:38:31 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"

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
			
			typedef ft::bidirectional_iterator<value_type, tree, node_type>   		iterator;
			// typedef ft::const_bidirectional_iterator< node_type,  value_type>	const_iterator;
			// typedef ft::reverse_iterator<iterator>          					reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>    					const_reverse_iterator;
			typedef ptrdiff_t                               					difference_type;
			typedef size_t                                  					size_type;
			
		public:
			//////////////////////// MEMBER FUNCTIONS ////////////////////////
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				_comp = comp;
				_alloc = alloc;
			}
			
			// template <class InputIterator>
			// map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			// 		const allocator_type& alloc = allocator_type())
			// {
				
			// }	
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

			map& operator= (const map& x);
			/////////////////////// ITERATORS ////////////////////////////////
			// iterator begin();
			// const_iterator begin() const;

			// iterator end();
			// const_iterator end() const;
			
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;
			////////////////////////// CAPACITY //////////////////////////////

			// bool empty() const;
			// size_type size() const;
			// size_type max_size() const;

			////////////////////////// ELEMENT ACCESS ////////////////////////
			
			// mapped_type& operator[] (const key_type& k);

			////////////////////////// MODIFIERS /////////////////////////////
			
				// pair<iterator,bool> insert (const value_type& val);
				// iterator insert (iterator position, const value_type& val);
				// template <class InputIterator>
				// void insert (InputIterator first, InputIterator last);
				
				// void erase (iterator position);
				// size_type erase (const key_type& k)
				// void erase (iterator first, iterator last);

				// void swap (map& x);

				// void clear();
			
			////////////////////////// OBSERVERS /////////////////////////////
			
			// key_compare key_comp() const;
			// value_compare value_comp() const;

			////////////////////////// OPERATIONS ////////////////////////////
			
			// iterator find (const key_type& k);
			// const_iterator find (const key_type& k) const;

			// size_type count (const key_type& k) const;
			
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
