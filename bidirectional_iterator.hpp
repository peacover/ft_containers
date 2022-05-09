/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 03:37:50 by yer-raki          #+#    #+#             */
/*   Updated: 2022/05/09 17:17:32 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include "random_access_iterator.hpp"

namespace ft
{
	template <class Pair, class Tree, class Node>
	class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, Pair>
	{
		public:

			typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::iterator_category		iterator_category;
        	typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::difference_type		difference_type;
        	typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::value_type			value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::pointer				pointer;
			typedef	typename ft::iterator<std::bidirectional_iterator_tag, Pair>::reference				reference;
			typedef Tree const *																		tree;
			typedef Node 																				*node_pointer;
		
        private:
			tree 	_tree;
			node_pointer	_node;

        public:
            bidirectional_iterator() : _tree(), _node() {}
			// bidirectional_iterator(node_pointer node) : _node(node) {}
			bidirectional_iterator(node_pointer node, tree tree) : _tree(tree), _node(node) {}
			bidirectional_iterator(bidirectional_iterator const &other) { *this = other; }
			virtual ~bidirectional_iterator() {}
			bidirectional_iterator & operator=(bidirectional_iterator const & src)
			{
				if (this != &src)
				{
					_tree = src._tree;
					_node = src._node;
				}
				return (*this);
			}
			operator bidirectional_iterator<const Pair, Tree, const Node>() const
			{
				return bidirectional_iterator<const Pair, Tree, const Node>(_node, _tree);
			}
			pointer operator->() const
            {
                return (_node->data);
            }
            reference operator*() const
            {
                return (*_node->data);
            }
			bidirectional_iterator & operator++()
			{
				if (!_node)
					_node = _tree->findMin(_tree->get_root());
				else
				{
					if (_node->right)
						_node = _tree->findMin(_node->right);
					else
					{
						while (_node->parent && _node->parent->right == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				return (*this);
			}
			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp(*this);
				++(*this);
				return (tmp);
			}
			bidirectional_iterator & operator--()
			{
				if (!_node)
					_node = _tree->findMax(_tree->get_root());
				else
				{	
					if (_node->left)
						_node = _tree->findMax(_node->left);
					else
					{
						while (_node->parent && _node->parent->left == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				return (*this);
			}
			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
			friend bool operator== (const bidirectional_iterator& lhs, const bidirectional_iterator& rhs)
			{
				return (lhs._node == rhs._node);
			}
			friend bool operator!= (const bidirectional_iterator& lhs, const bidirectional_iterator& rhs)
			{
				return (lhs._node != rhs._node);
			}
    };
}