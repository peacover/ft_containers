/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 09:47:40 by yer-raki          #+#    #+#             */
/*   Updated: 2022/05/09 18:41:39 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <unistd.h>
#include <iostream>
#include "pair.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"

#define COUNT 10;
namespace ft
{
	template<class T>
	class Node
	{
		public :
			T				*data;
			Node<T>        	*left;
			Node<T>        	*right;
			Node<T>        	*parent;
			int				bf;
			int             height;

		public :
			Node() : data(NULL), left(NULL), right(NULL), parent(NULL), height(0) {};
			~Node(){};
			Node(const Node &other)
			{
				*this = other;
			}
			Node &operator=(const Node &other)
			{
				data = other.data;
				left = other.left;
				right = other.right;
				parent = other.parent;
				height = other.height;
				return (*this);
			}
			Node(T *data) : data(data), left(NULL), right(NULL), parent(NULL), height(0) {};
	}; 
	template < class Key,                                  			// map::key_type
		class T,                                       				// map::mapped_type
		class Compare = std::less<Key>,                     		// map::key_compare
		class Alloc = std::allocator<ft::pair<const Key,T> >		// map::allocator_type
		>
	class avl
	{
		typedef T 															mapped_type;
		typedef Key															key_type;
		typedef ft::pair<const key_type, mapped_type>						value_type;
		typedef Alloc 														pair_alloc;
        typedef typename Alloc::template rebind<Node<value_type> >::other	node_alloc;
		typedef Node<value_type>											node_type;
		typedef Node<value_type>											*node_pointer;
		typedef ft::bidirectional_iterator<value_type, avl, node_type >   					iterator;
		typedef ft::bidirectional_iterator<const value_type, avl, const node_type >   	const_iterator;
		typedef ft::reverse_iterator<iterator>          					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>    					const_reverse_iterator;
		public:
			avl()
			{
				_root = NULL;
				_node_size = 0;
			}
			avl(const avl &other) : _root(NULL) { *this = assign(other); }
			// avl &operator=(const avl &other)
			// {
			// 	if (this != &other)
			// 	{
			// 		*this = assign(other);
			// 	}
			// 	return *this;
			// }
			~avl()
			{
				// clear();
			}
			avl&    assign (avl const& x)
			{
				delete_tree();
				_pair_alloc = x._pair_alloc;
				_node_alloc = x._node_alloc;
				_comp = x._comp;
				for (const_iterator it = x.begin(); it != x.end(); it++)
					insert(*it);
				_node_size = x._node_size;
				return *this;
			}
			size_t size() const
			{
				return (_node_size);
			}
			size_t max_size() const
			{
				return (_node_alloc.max_size());
			}
			bool empty() const
			{
				if (_node_size == 0)
					return true;
				return false;
			}
			void delete_tree()
			{
				_root = delete_tree(_root);
				_node_size = 0;
			}
			node_pointer delete_tree(node_pointer node)
			{
				if (node != NULL)
				{
					delete_tree(node->left);
					delete_tree(node->right);
					delete_node(node);
				}
				return NULL;
			}
			void delete_node(node_pointer node)
			{
				_pair_alloc.destroy(node->data);
				_pair_alloc.deallocate(node->data, 1);
				node->data = NULL;
				_node_alloc.deallocate(node, 1);
				node = NULL;
			}
			node_pointer ll_rotation(node_pointer node)
			{
				node_pointer tmp = node->left;
				node->left = tmp->right;
				if (tmp->right)
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (!node->parent)
					_root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->right = node;
				node->parent = tmp;
				update(node);
				update(tmp);
				return tmp;
			}
			node_pointer rr_rotation(node_pointer node)
			{
				node_pointer tmp = node->right;
				node->right = tmp->left;
				if (tmp->left)
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (!node->parent)
					_root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->left = node;
				node->parent = tmp;
				update(node);
				update(tmp);
				return tmp;
			}
			node_pointer lr_rotation(node_pointer node)
			{
				node->left = rr_rotation(node->left);
				return (ll_rotation(node));
			}
			node_pointer rl_rotation(node_pointer node)
			{
				node->right = ll_rotation(node->right);
				return (rr_rotation(node));
			}
			node_pointer new_node(value_type value)
			{
				node_pointer tmp = _node_alloc.allocate(1);
				tmp->data = _pair_alloc.allocate(1);
				_pair_alloc.construct(tmp->data, value);
				tmp->left = NULL;
				tmp->parent = NULL;
				tmp->right = NULL;
				tmp->height = 0;
				tmp->bf = 0;

				// _node_size++;
				return (tmp);
			}
			node_pointer balance(node_pointer node)
			{
				if (node->bf == 2)
				{
					if (node->left->bf == 1)
						return (ll_rotation(node));
					else
						return (lr_rotation(node));
				}
				else if (node->bf == -2)
				{
					if (node->right->bf == -1)
						return (rr_rotation(node));
					else
						return (rl_rotation(node));
				}
				return node;
			}
			void update(node_pointer node)
			{
				int hl = -1;
				int hr = -1;
				if (node->left)
					hl = node->left->height;
				if (node->right)
					hr = node->right->height;
				node->height = 1 + std::max(hl, hr);
				node->bf = hl - hr;
			}
			bool contains(key_type elem) const
			{
				return (contains(_root, elem));
			}
			
			pair<node_pointer, bool> insert(value_type pair)
			{
				// if (contains(pair.first))
				// 	return false;
				// else
				// {
					ft::pair<node_pointer, bool> tmp = insert(_root, pair);
					if (tmp.second)
					{
						if (!_root)
							_root = tmp.first;
						_node_size++;
					}
					return (tmp);
					// return true;
				// }
			}
			pair<node_pointer, bool> insert(node_pointer node, value_type value)
			{
				if (!node){
					return (ft::make_pair(new_node(value), true));
					
				}
				if (_comp(value.first, node->data->first))
				{
					node->left = insert(node->left, value).first;
					node->left->parent = node;
					
				}
				else if (_comp(node->data->first, value.first))
				{
					node->right = insert(node->right, value).first;
					node->right->parent = node;
				}
				else
					return (ft::make_pair(node, false));
				update(node);
				return (ft::make_pair(balance(node), true));
			}

			bool contains(node_pointer node, key_type pair_key)
			{
				if (node == NULL)
					return false;
				bool cmp = _comp(node->data->first, pair_key);
				bool cmp1 = _comp(pair_key, node->data->first);
				if (!cmp1 && !cmp)
					return true;
				if (!cmp)
					return (contains(node->left, pair_key));
				if (cmp)
					return (contains(node->right, pair_key));
				return true;
			}
			
			bool contains(node_pointer node, key_type pair_key) const
			{
				if (node == NULL)
					return false;
				bool cmp = _comp(node->data->first, pair_key);
				bool cmp1 = _comp(pair_key, node->data->first);
				if (!cmp1 && !cmp)
					return true;
				if (!cmp)
					return (contains(node->left, pair_key));
				if (cmp)
					return (contains(node->right, pair_key));
				return true;
			}

			node_pointer findMin(node_pointer node)
			{
				while (node && node->left)
					node = node->left;
				return node;
			}
			node_pointer findMax(node_pointer node)
			{
				while (node && node->right)
					node = node->right;
				return node;
			}
			
			node_pointer findMin(node_pointer node) const
			{
				while (node && node->left)
					node = node->left;
				return node;
			}
			node_pointer findMax(node_pointer node) const
			{
				while (node && node->right)
					node = node->right;
				return node;
			}

			node_pointer find(key_type val)
			{
				if (contains(_root, val))
					return (find(_root, val));
				return NULL;
			}
			node_pointer find(key_type val) const
			{
				if (contains(_root, val))
					return (find(_root, val));
				return NULL;
			}
			node_pointer find(node_pointer node, key_type key)
			{
				if (node == NULL)
					return NULL;
				if (key < node->data->first)
					return find(node->left, key);
				else if (key > node->data->first)
					return find(node->right, key);
				else
					return node;
			}

			node_pointer find(node_pointer node, key_type key) const
			{
				if (node == NULL)
					return NULL;
				if (key < node->data->first)
					return find(node->left, key);
				else if (key > node->data->first)
					return find(node->right, key);
				else
					return node;
			}
			
			bool remove(key_type pair)
			{
				if (contains(pair))
				{
					_root = remove(_root, pair);
					_node_size--;
					return true;
				}
				return false;
			}

			void clear()
			{
				_root = NULL;
				_node_size = 0;
			}
			iterator begin()
			{
				key_type min = findMin(_root)->data->first;
				node_pointer first = find(min);
				return (iterator(first, this));
			}
			const_iterator begin() const
			{
				key_type min = findMin(_root)->data->first;
				node_pointer first = find(min);
            	return (iterator(first, this));
			}
			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}
			iterator end()
			{
				return (iterator(NULL, this)); 
			}
			const_iterator end() const
			{
				return (const_iterator(NULL, this)); 
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}
			node_pointer get_root() const
			{
				return _root;
			}
			pair_alloc get_pair_allocator() const
			{
				return _pair_alloc;
			}
			void print2DUtil(node_pointer root, int space)
			{
				// Base case
				if (root == NULL)
					return;
			
				// Increase distance between levels
				space += COUNT;
			
				// Process right child first
				print2DUtil(root->right, space);
			
				// Print current node after space
				// count
				std::cout<< std::endl;
				int i = COUNT;
				while (i < space)
				{
					std::cout<< " ";
					i++;	
				}
				// for (int i = COUNT; i < space; i++)
				// {
				// 	std::cout<< " ";
				// }
				std::cout<<root->data->first<<"\n";
			
				// Process left child
				print2DUtil(root->left, space);
			}	
			// Wrapper over print2DUtil()
		
			void print2D()
			{
				// Pass initial space count as 0
				node_pointer root = this->_root;
				print2DUtil(root, 0);
			}
		private:
			node_pointer	_root;
			Compare			_comp;
			pair_alloc 		_pair_alloc;
			node_alloc		_node_alloc;
			size_t			_node_size;
		
			node_pointer remove(node_pointer node, key_type pair_key)
			{
				if (!node)
					return NULL;
				if (_comp(pair_key, node->data->first))
					node->left = remove(node->left, pair_key);

				else if (_comp(node->data->first, pair_key))
					node->right = remove(node->right, pair_key);
				else
				{
					if (!node->left && !node->right)
					{
						_pair_alloc.destroy(node->data);
						_pair_alloc.deallocate(node->data, 1);
						_node_alloc.deallocate(node, 1);
						return NULL;
					}
					else if (!node->left)
					{
						node_pointer tmp = node->right;
						std::swap(node->data, tmp->data);
						node->right = remove(node->right, pair_key);
						return node;
					}
					else if (!node->right)
					{
						node_pointer tmp = node->left;
						std::swap(node->data, tmp->data);
						node->left = remove(node->left, pair_key);
						return node;
					}
					else
					{
						node_pointer tmp = findMin(node->right);
						std::swap(node->data, tmp->data);
						node->right = remove(node->right, pair_key);
					}
				}
				update(node);
				return balance(node);
			}
			
			
			
};
}
