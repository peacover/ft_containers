/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 09:47:40 by yer-raki          #+#    #+#             */
/*   Updated: 2022/05/13 06:25:34 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <unistd.h>
#include <iostream>
#include "pair.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"

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
			// Node(const Node &other)
			// {
			// 	*this = other;
			// }
			// Node &operator=(const Node &other)
			// {
			// 	data = other.data;
			// 	left = other.left;
			// 	right = other.right;
			// 	parent = other.parent;
			// 	height = other.height;
			// 	return (*this);
			// }
			// Node(T *data) : data(data), left(NULL), right(NULL), parent(NULL), height(0) {};
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
			avl() : _root(NULL), _comp(), _pair_alloc(), _node_alloc(), _node_size(0) { }
			avl(const avl &other) { *this = other; }
			
			avl &operator=(const avl &other)
			{
				delete_tree();
				_pair_alloc = other._pair_alloc;
				_node_alloc = other._node_alloc;
				_comp = other._comp;
				// if (_root)
				// {
					for (const_iterator it = other.begin(); it != other.end(); it++)
						insert(*it);
				// }
				_node_size = other._node_size;
				return *this;
			}
			~avl()
			{
				clear();
			}
			avl&    assign (avl const& x)
			{
				delete_tree();
				_pair_alloc = x._pair_alloc;
				_node_alloc = x._node_alloc;
				_comp = x._comp;
				if (_root)
				{
					for (const_iterator it = x.begin(); it != x.end(); it++)
						insert(*it);
				}
				_node_size = x._node_size;
				return *this;
			}
			void swap(avl &other)
			{
				std::swap(_node_size, other._node_size);
				std::swap(_root, other._root);
				std::swap(_comp, other._comp);
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
			bool contains(key_type elem)
			{
				return (contains(_root, elem));
			}
			bool contains(key_type elem) const
			{
				return (contains(_root, elem));
			}
			
			pair<node_pointer, bool> insert(value_type pair)
			{
				if (contains(pair.first))
					return (ft::make_pair(_root, false));
				ft::pair<node_pointer, bool> tmp = insert(_root, pair);
				if (tmp.second)
				{
					if (!_root)
						_root = tmp.first;
					_node_size++;
				}
				else
					tmp.second = false;
				return (tmp);
			}
			pair<node_pointer, bool> insert(node_pointer node, value_type value)
			{
				if (!node)
					return (ft::make_pair(new_node(value), true));
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
				// else
				// 	return (ft::make_pair(node, false));
				update(node);
				return (ft::make_pair(balance(node), true));
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

			value_type findMin_t(node_pointer node) 
			{
				if (node == NULL)
					return (ft::make_pair(node->data->first, node->data->second));
				while (node->left != NULL)
					node = node->left;
				return (*(node->data));
			}
			value_type findMax_t(node_pointer node) 
			{
				if (node == NULL)
					return (ft::make_pair(node->data->first, node->data->second));
				while (node->right != NULL)
					node = node->right;
				return (*(node->data));
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
				if (!node)
					return NULL;
				if (key == node->data->first)
					return node;
				else
				{
					if (_comp(key, node->data->first))
						return find(node->left, key);
					else
						return find(node->right, key);
            	}
			}
			node_pointer find(node_pointer node, key_type key) const
			{
				if (!node)
					return NULL;
				if (key == node->data->first)
					return node;
				else
				{
					if (_comp(key, node->data->first))
						return find(node->left, key);
					else
						return find(node->right, key);
            	}
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
				space += 10;
			
				// Process right child first
				print2DUtil(root->right, space);
			
				// Print current node after space
				// count
				std::cout<< std::endl;
				int i = 10;
				while (i < space)
				{
					std::cout<< " ";
					i++;	
				}
				// for (int i = 10; i < space; i++)
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
			
			void		swap_nodes(node_pointer n1, node_pointer n2)
			{
				// std::cout << "Before swap: "  <<std::endl;
				// std::cout <<n1<<" "<<n1->data->first << " " << n1->data->second << " " << n1->parent << " " << n1->left << " " << n1->right <<" " << n1->bf << " " << n1->height << std::endl;
				// std::cout <<n2<<" "<<n2->data->first << " " << n2->data->second << " " << n2->parent << " " << n2->left << " " << n2->right <<" " << n2->bf << " " << n2->height << std::endl;
				bool n1_left_child_n2 = false;
				bool n2_left_child_n1 = false;
				bool n1_right_child_n2 = false;
				bool n2_right_child_n1 = false;
				
				if (n1->left == n2)
				{
					n1_left_child_n2 = true;
					n2->parent = NULL;
					n1->left = NULL;
				}
				else if (n1->right == n2)
				{
					n1_right_child_n2 = true;
					n2->parent = NULL;
					n1->right = NULL;
				}
				else if (n2->left == n1)
				{
					n2_left_child_n1 = true;
					n1->parent = NULL;
					n2->left = NULL;
				}
				else if (n2->right == n1)
				{
					n2_right_child_n1 = true;
					n1->parent = NULL;
					n2->right = NULL;
				}
				if (n1->parent)
				{
					if (n1->parent->left == n1)
						n1->parent->left = n2;
					else
						n1->parent->right = n2;
				}
				if (n2->parent)
				{
					if (n2->parent->left == n2)
						n2->parent->left = n1;
					else
						n2->parent->right = n1;
				}

				std::swap(n1->parent, n2->parent);
				if (n1->left)
					n1->left->parent = n2;
				if (n1->right)
					n1->right->parent = n2;
				if (n2->left)
					n2->left->parent = n1;
				if (n2->right)
					n2->right->parent = n1;
				std::swap(n1->left, n2->left);
				std::swap(n1->right, n2->right);
				std::swap(n1->bf, n2->bf);
				std::swap(n1->height, n2->height);
				if (n1_left_child_n2)
				{
					n2->left = n1;
					n1->parent = n2;					
				}
				else if (n1_right_child_n2)
				{
					n2->right = n1;
					n1->parent = n2;
				}
				else if (n2_left_child_n1)
				{
					n1->left = n2;
					n2->parent = n1;
				}
				else if (n2_right_child_n1)
				{
					n1->right = n2;
					n2->parent = n1;
				}

				// std::cout << "After swap: "  <<std::endl;
				// std::cout << n1<<" "<< n1->data->first << " " << n1->data->second << " " << n1->parent << " " << n1->left << " " << n1->right <<" " << n1->bf << " " << n1->height << std::endl;
				// std::cout << n2<<" "<< n2->data->first << " " << n2->data->second << " " << n2->parent << " " << n2->left << " " << n2->right <<" " << n2->bf << " " << n2->height << std::endl;
			}
			// node_pointer remove(node_pointer node, key_type pair_key)
			// {
			// 	// if (!node)
			// 	// 	return NULL;
			// 	// if (_comp(pair_key, node->data->first))
			// 	// 	node->left = remove(node->left, pair_key);

			// 	// else if (_comp(node->data->first, pair_key))
			// 	// 	node->right = remove(node->right, pair_key);
			// 	// else
			// 	// {
			// 	// 	if (!node->left && !node->right)
			// 	// 	{
			// 	// 		_pair_alloc.destroy(node->data);
			// 	// 		_pair_alloc.deallocate(node->data, 1);
			// 	// 		_node_alloc.deallocate(node, 1);
			// 	// 		return NULL;
			// 	// 	}
			// 	// 	else if (!node->left)
			// 	// 	{
			// 	// 		node_pointer tmp = node->right;
			// 	// 		// swap_nodes(node, tmp);
			// 	// 		std::swap(node, tmp);
			// 	// 		node->right = remove(node->right, pair_key);
			// 	// 		return (node);
			// 	// 	}
			// 	// 	else if (!node->right)
			// 	// 	{
			// 	// 		node_pointer tmp = node->left;
			// 	// 		// swap_nodes(node, tmp); // [5] // [7]
			// 	// 		std::swap(node, tmp);
			// 	// 		node->left = remove(node->left, pair_key);
			// 	// 		return (node);
			// 	// 	}
			// 	// 	else
			// 	// 	{
			// 	// 		node_pointer tmp = findMin(node->right);
			// 	// 		// swap_nodes(node, tmp);
			// 	// 		std::swap(node, tmp);
			// 	// 		node->right = remove(node, pair_key);
			// 	// 		return (node);
			// 	// 	}
			// 	// }
			// 	// update(node);
			// 	// return balance(node);

			// 	// if (!node)
			// 	// {
			// 	// 	// update(node);
			// 	// 	// return balance(node);
			// 	// 	return NULL;
			// 	// }
			// 	if (_comp(pair_key, node->data->first))
			// 		node->left = remove(node->left, pair_key);

			// 	else if (_comp(node->data->first, pair_key))
			// 		node->right = remove(node->right, pair_key);
			// 	else
			// 	{
			// 		// if (!node->left && !node->right)
			// 		// {
			// 		// 	// _pair_alloc.destroy(node->data);
			// 		// 	// _pair_alloc.deallocate(node->data, 1);
			// 		// 	// _node_alloc.deallocate(node, 1);
			// 		// 	delete_node(node);
			// 		// 	// node = NULL;
			// 		// 	return NULL;
			// 		// }
			// 		// else if (!node->left)
			// 		// {
			// 		// 	node_pointer tmp = node->right;
			// 		// 	std::swap(node->data, tmp->data);
			// 		// 	node->right = remove(node->right, pair_key);
			// 		// 	return node;
			// 		// }
			// 		// else if (!node->right)
			// 		// {
			// 		// 	node_pointer tmp = node->left;
			// 		// 	std::swap(node->data, tmp->data);
			// 		// 	node->left = remove(node->left, pair_key);
			// 		// 	return node;
			// 		// }
			// 		// else
			// 		// {
			// 		// 	node_pointer tmp = findMin(node->right);
			// 		// 	std::swap(node->data, tmp->data);
			// 		// 	node->right = remove(node->right, pair_key);
			// 		// }


					
			// 		// node_pointer t1 = findMin(node->right);
			// 		// node_pointer t2 = findMax(node->left);
			// 		// if (t1)
			// 		// {
			// 		// 	std::swap(node->data, t1->data);
			// 		// 	delete_node(find(node->data->first));
			// 		// 	// node->right = remove(node->right, pair_key);
			// 		// 	// return node;
			// 		// }
			// 		// else if (t2)
			// 		// {
			// 		// 	std::swap(node->data, t1->data);
			// 		// 	// node->left = remove(node->left, pair_key);
			// 		// 	delete_node(find(node->data->first));
			// 		// 	// return node;
			// 		// }
			// 		// else
			// 		// {
			// 		// 	delete_node(node);
			// 		// 	// update(node);
			// 		// 	return (NULL);
			// 		// }
			// 	}
			// 	update(node);
			// 	return (balance(node));
			// }

			node_pointer	remove(node_pointer node, key_type key)
			{
				if (node->left == NULL && node->right == NULL)
				{
					if (node == this->_root)
						this->_root = NULL;
					delete_node(node);
					node = NULL;
					return NULL;
				}
				node_pointer tmp;
				if (_comp(key, node->data->first))
					node->left = remove(node->left, key);
				else if (_comp(node->data->first, key))
					node->right = remove(node->right, key);
				else
				{
					if (node->left != NULL)
					{
						tmp = findMax(node->left);
						std::swap(node->data, tmp->data);
						node->left = remove(node->left, tmp->data->first);
					}
					else
					{
						tmp = findMin(node->right);
						std::swap(node->data, tmp->data);
						node->right = remove(node->right, tmp->data->first);
					}
				}
				return update_balance_remove(node);
			}
			
			node_pointer update_balance_remove(node_pointer node)
			{
				node->height = 1 + std::max(height(node->left), height(node->right));
				int bf = getBalanceFactor(node);

				if (bf > 1 && getBalanceFactor(node->left) >= 0)
					return ll_rotation(node);
				if (bf > 1 && getBalanceFactor(node->left) < 0)
					return rl_rotation(node);
				if (bf < -1 && getBalanceFactor(node->right) <= 0)
					return rr_rotation(node);
				if (bf < -1 && getBalanceFactor(node->right) > 0)
					return lr_rotation(node);
				return node;
			}
			int height(node_pointer node)
			{
				if (node == NULL)
					return 0;
				return node->height;
			}
			int getBalanceFactor(node_pointer node)
			{
				if (node == NULL)
					return 0;
				return (height(node->left) - height(node->right));
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
};
}