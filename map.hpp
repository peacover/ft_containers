/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:34:31 by yer-raki          #+#    #+#             */
/*   Updated: 2022/05/13 12:03:36 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "avl.hpp"
#include "vector.hpp"
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
			typedef typename ft::pair<const key_type, mapped_type>       		value_type;
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
			typedef ft::reverse_iterator<const_iterator>          					const_reverse_iterator;
			typedef ptrdiff_t                               					difference_type;
			typedef size_t                                  					size_type;

			typedef class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					key_compare _comp;
					value_compare (key_compare c) : _comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return _comp(x.first, y.first);
					}
			} value_compare;

		public:
			//////////////////////// MEMBER FUNCTIONS ////////////////////////
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc)
			{

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
				_alloc = x._alloc;
				_comp = x._comp;
				_tree = x._tree;
			}
			~map()
			{
			}

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					_alloc = x._alloc;
					_comp = x._comp;
					_tree.delete_tree();
					insert(x.begin(), x.end());
				}
				
				return *this;
			}
			/////////////////////// ITERATORS ////////////////////////////////
			iterator begin()
			{
				node_pointer min = _tree.findMin(_tree.get_root());
				return (iterator(min, &_tree));
			}
			const_iterator begin() const
			{
				node_pointer min = _tree.findMin(_tree.get_root());
				return (const_iterator(min, &_tree));
			}
			iterator end()
			{
				return (_tree.end());
			}
			const_iterator end() const
			{
				return (_tree.end());
			}
			
			reverse_iterator rbegin()
			{
				return (_tree.rbegin());
			}
			const_reverse_iterator rbegin() const
			{
				return (_tree.rbegin());
			}
			reverse_iterator rend()
			{
				return (_tree.rend());
			}
			
			const_reverse_iterator rend() const
			{
				return (_tree.rend());
			}
			////////////////////////// CAPACITY //////////////////////////////

			bool empty() const
			{
				return (_tree.empty());
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
				if (_tree.find(_tree.get_root(), k) == NULL)
					insert(ft::make_pair(k,mapped_type()));
				node_pointer tmp = _tree.find(_tree.get_root(), k);
				return (tmp->data->second);
			}
			////////////////////////// MODIFIERS /////////////////////////////
			
				pair<iterator,bool> insert (const value_type& pair)
				{
					ft::pair<node_pointer, bool> p = _tree.insert(pair);
					return (ft::make_pair(iterator(p.first, &_tree), p.second));
				}
				iterator insert (iterator position, const value_type& val)
				{
					(void)position;
					return (insert(val).first);
				}
				template <class InputIterator>
				void insert (InputIterator first, InputIterator last)
				{
					while (first != last)
					{
						_tree.insert(*first);
						++first;
					}
					return;
				}
				
				void erase (iterator position)
				{
					key_type pos = position->first;
					_tree.remove(pos);
					return;
				}
				size_type erase (const key_type& k)
				{
					return _tree.remove(k);
				}
				void erase (iterator first, iterator last)
				{
					std::vector<key_type> v;
					while (first != last)
					{
						v.push_back(first->first);
						first++;
					}
					typename std::vector<key_type>::iterator it = v.begin();
					while (it != v.end())
					{
						erase(*it);
						it++;
					}
					v.clear();
				}

				void swap (map& x)
				{
					// tree tmp;

					// tmp = x._tree;
					// x._tree = _tree;
					// _tree = tmp;
					_tree.swap(x._tree);
					std::swap(_comp, x._comp);
            		std::swap(_alloc, x._alloc);
					// std::swap(_tree, x._tree);
				}

				void clear()
				{
					_tree.delete_tree();
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
				node_pointer tmp = _tree.find(k);
				if (tmp)
					return iterator(tmp, &_tree);
				else
					return (end());
			}
			const_iterator find (const key_type& k) const
			{
				node_pointer tmp = _tree.find(_tree.get_root(), k);
				if (tmp)
					return const_iterator(tmp, &_tree);
				else
					return (end());
			}

			size_type count (const key_type& k) const
			{
				return _tree.contains(k);
			}
			
			iterator lower_bound (const key_type& k)
			{
				// return iterator(_tree.lower_bound(k), &_tree);
				// iterator it;
				// key_type tmp;
				// for (it = _tree.begin(); it != _tree.end(); it++)
				// {
				// 	tmp = it->first;
				// 	if (tmp >= k)
				// 		return (it);
				// }
				// return (it);
				node_pointer tmp = _tree.lower_bound(_tree.get_root(), k);
				if (tmp != NULL)
					return iterator(tmp, &_tree);
				return (end());
			}
			const_iterator lower_bound (const key_type& k) const
			{
				// const_iterator it;
				// key_type tmp;
				// for (it = _tree.begin(); it != _tree.end(); it++)
				// {
				// 	tmp = it->first;
				// 	if (tmp >= k)
				// 		return (it);
				// }
				// return (it);
				node_pointer tmp = _tree.lower_bound(_tree.get_root(), k);
				if (tmp != NULL)
					return const_iterator(tmp, &_tree);
				return (end());
			}
			
			iterator upper_bound (const key_type& k)
			{
				// iterator it;
				// key_type tmp;
				// if (_tree.size() == 0)
				// 	return (end());
				// for (it = _tree.begin(); it != _tree.end(); it++)
				// {
				// 	tmp = it->first;
				// 	if (tmp > k)
				// 		return (it);
				// }
				// return (it);
				node_pointer tmp = _tree.upper_bound(_tree.get_root(), k);
				if (tmp != NULL)
					return iterator(tmp, &_tree);
				return (end());
			}
			const_iterator upper_bound (const key_type& k) const
			{
				// const_iterator it;
				// key_type tmp;
				// if (_tree.size() == 0)
				// 	return (end());
				// for (it = _tree.begin(); it != _tree.end(); it++)
				// {
				// 	tmp = it->first;
				// 	if (tmp > k)
				// 		return (it);
				// }
				// return (it);
				node_pointer tmp = _tree.upper_bound(_tree.get_root(), k);
				if (tmp != NULL)
					return const_iterator(tmp, &_tree);
				return (end());
			}

			pair<iterator,iterator> equal_range (const key_type& k)
			{
				ft::pair<iterator,iterator> ret =  ft::make_pair(lower_bound(k), upper_bound(k));
				return (ret);
			}
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				ft::pair<const_iterator,const_iterator> ret =  ft::make_pair(lower_bound(k), upper_bound(k));
				return (ret);
			}

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
	// template <class Key, class T, class Compare, class Alloc>
    // bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    // {
    //     if (lhs.size() != rhs.size())
    //         return (lhs.size() == rhs.size());
    //     return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    // }
	template <class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return rhs < lhs;
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
}
