/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 03:37:50 by yer-raki          #+#    #+#             */
/*   Updated: 2022/04/29 06:43:47 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pair.hpp"

namespace ft
{
	template <class Pair, class Tree, class Node>
	class bidirectional_iterator
	{
		public:

			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
        	typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
        	typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef	typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;																				pointer;
			typedef	typename ft::iterator<std::bidirectional_iterator_tag, T>::reference			reference;
			typedef Tree 																			tree;
			typedef Node 																			*node_pointer;
		
        private:
			tree _tree;
			node_pointer _node;

        public:
            
            
    };
}