/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 09:47:40 by yer-raki          #+#    #+#             */
/*   Updated: 2022/04/19 20:51:19 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <unistd.h>
#include <iostream>

namespace ft
{
	typedef struct	Node
	{
		// pair key value
		int		value;
		Node	*left;
		Node	*right;
		Node	*parent;
		int		height;
	}				Node;
	template< class T, class Allocator = std::allocator<T> >
	class avl
	{
		public:
			bool	balance_factor(Node *head);
			Node	*balanced_tree(Node *head);
			int		height(Node *head);
			
			Node	*ll_rotation(Node *head)
			{
				Node *tmp1 = head->left;
				Node *tmp2 = 
				
			}
			Node	*rr_rotation(Node *head);
			Node	*lr_rotation(Node *head);
			Node	*rl_rotation(Node *head);

			void	BST_insert(int value);
			
		private:
			Node *_root;
			Node *_node;
	};
}
