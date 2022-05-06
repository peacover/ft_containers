/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 03:37:50 by yer-raki          #+#    #+#             */
/*   Updated: 2022/05/06 17:19:49 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"

namespace ft
{
	template <class Pair, class Tree, class Node>
	class bidirectional_iterator
	{
		public:

			typedef typename std::iterator<std::bidirectional_iterator_tag, Pair>::iterator_category		iterator_category;
        	typedef typename std::iterator<std::bidirectional_iterator_tag, Pair>::difference_type		difference_type;
        	typedef typename std::iterator<std::bidirectional_iterator_tag, Pair>::value_type			value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Pair>::pointer				pointer;
			typedef	typename std::iterator<std::bidirectional_iterator_tag, Pair>::reference				reference;
			typedef Tree 																				*tree;
			typedef Node 																				*node_pointer;
		
        private:
			tree 			_tree;
			node_pointer	_node;

        public:
            bidirectional_iterator() : _tree(NULL), _node(NULL) {}
			bidirectional_iterator(node_pointer node) : _node(node) {}
			bidirectional_iterator(node_pointer node, tree tree) : _node(node), _tree(tree) {}
			bidirectional_iterator(const bidirectional_iterator &other) : _tree(other._tree), _node(other._node) {}
			virtual ~bidirectional_iterator() {}
			operator bidirectional_iterator<const Pair, Tree, const Node>() const
			{
				return bidirectional_iterator<const Pair, Tree, const Node>(_node, _tree);
			}
			bidirectional_iterator & operator=(bidirectional_iterator const & src)
			{
				if (this != &src)
				{
					_node = src._node;
					_tree = src._tree;
				}
				return (*this);
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
				if (_node->right != NULL)
					_node = _tree->findMin(_node->right);
				else
				{
					while (_node->parent != NULL && _node->parent->right == _node)
						_node = _node->parent;
					_node = _node->parent;
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
				if (_node->left != NULL)
					_node = _tree->findMax(_node->left);
				else
				{
					while (_node->parent != NULL && _node->parent->left == _node)
						_node = _node->parent;
					_node = _node->parent;
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