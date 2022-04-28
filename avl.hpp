/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 09:47:40 by yer-raki          #+#    #+#             */
/*   Updated: 2022/04/28 01:39:13 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <unistd.h>
#include <iostream>
#include "pair.hpp"

#define COUNT 10;
namespace ft
{
	// template <typename T>
	// struct	Node
	// {
	// 	T		value;
	// 	Node<T>	*left;
	// 	Node<T>	*right;
	// 	Node<T>	*parent;
	// 	int		bf;
	// 	int		height;
	// };
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
			Node() : data(nullptr), left(nullptr), right(nullptr), parent(nullptr), height(0) {};
			~Node(){};
	};
	template < class Key,                                  			// map::key_type
           class T,                                       			// map::mapped_type
           class Compare = std::less<Key>,                     		// map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >		// map::allocator_type
           >
	class avl
	{
		typedef T 													mapped_type;
		typedef Key													key_type;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		typedef Alloc 												pair_alloc;
        typedef typename Alloc::template rebind<Node<value_type> >::other	node_alloc;
		typedef Node<value_type>									*node_pointer ;
		public:
			avl()
			{
				_root = nullptr;
				_node_size = 0;
			}
			int		height(node_pointer head)
			{
				int h = 0;
				if (head != NULL)
				{
					int l_height = height(head->left);
					int r_height = height(head->right);
					int max_height = std::max(l_height, r_height);
					h = max_height + 1;
				}
				return h;
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
				if (node == NULL)
					return;
				node->height = 1 + std::max(height(node->left), height(node->right));
				node->bf = height(node->left) - height(node->right);
				update(node->left);
				update(node->right);
			}
			bool _contains(node_pointer node, mapped_type pair) const
			{
				if (node == nullptr)
                	return false;
				bool cmp = _comp(node->data->first, pair);
				bool cmp1 = _comp(pair, node->data->first);
				if (!cmp1 && !cmp)
					return true;
				if (!cmp)
					return (_contains(node->left, pair));
				if (cmp)
					return (_contains(node->right, pair));
				return true;
			}
			bool contains(mapped_type elem)
			{
				return (_contains(_root, elem));
			}
			bool insert(value_type pair)
			{
				if (contains(pair.first))
					return false;
				else
				{
					_root = _insert(_root, pair);
					_node_size++;
					return true;
				}
			}
			node_pointer _insert(node_pointer node, value_type value)
			{
				if (!node)
					return (new_node(value));
				else if (value.first < node->data->first)
				{
					node->left = _insert(node->left, value);
					node->left->parent = node;
				}
				else if (value.first > node->data->first)
				{
					node->right = _insert(node->right, value);
					node->right->parent = node;
				}
				else
					node->data->second = value.second;
				update(node);
				return balance(node);
			}
			// bool remove(mapped_type pair)
			// {
			// 	if (!contains(pair))
			// 		return false;
			// 	else
			// 	{
			// 		_root = _remove(_root, pair);
			// 		_node_size--;
			// 		return true;
			// 	}
			// }
			// node_pointer _remove(node_pointer node, mapped_type pair)
			// {
			// 	if (!node)
			// 		return (NULL);
			// 	if (pair < node->data->first)
			// 	{
			// 		node->left = _remove(node->left, pair);
			// 		node->left->parent = node;
			// 	}
			// 	else if (pair > node->data->first)
			// 	{
			// 		node->right = _remove(node->right, pair);
			// 		node->right->parent = node;
			// 	}
			// 	else
			// 	{
			// 		if (!node->left && !node->right)
			// 		{
			// 			_pair_alloc.destroy(node->data);
			// 			_pair_alloc.deallocate(node->data, 1);
			// 			_node_alloc.deallocate(node, 1);
			// 			return (NULL);
			// 		}
			// 		else if (!node->left)
			// 		{
			// 			node_pointer tmp = node->right;
			// 			_pair_alloc.destroy(node->data);
			// 			_pair_alloc.deallocate(node->data, 1);
			// 			_node_alloc.deallocate(node, 1);
			// 			return (tmp);
			// 		}
			// 		else if (!node->right)
			// 		{
			// 			node_pointer tmp = node->left;
			// 			_pair_alloc.destroy(node->data);
			// 			_pair_alloc.deallocate(node->data, 1);
			// 			_node_alloc.deallocate(node, 1);
			// 			return (tmp);
			// 		}
			// 		else
			// 		{
			// 			node_pointer tmp = node->right;
			// 			while (tmp->left)
			// 				tmp = tmp->left;
			// 			node->data->first = tmp->data->first;
			// 			node->data->second = tmp->data->second;
			// 			node->right = _remove(node->right, tmp->data->first);
			// 			node->right->parent = node;
			// 		}
			// 	}
			// 	update(node);
			// 	return (balance(node));
			// }
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
	};
};
