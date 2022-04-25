/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 09:47:40 by yer-raki          #+#    #+#             */
/*   Updated: 2022/04/25 04:55:40 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <unistd.h>
#include <iostream>
#define COUNT 10;
namespace ft
{
	typedef struct	Node
	{
		// pair key value
		int		value;
		Node	*left;
		Node	*right;
		Node	*parent;
		int		bf;
		int		height;
	}				Node;
	// template <typename T>
	class avl
	{
		public:
			avl()
			{
				this->_root = NULL;
			}

			int		height(Node *head)
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
			// int height(Node *N)
			// {
			// 	if (N == NULL)
			// 		return 0;
			// 	return N->height;
			// }
			Node	*ll_rotation(Node *head)
			{
				Node *tmp = head->left;
				head->left = tmp->right;
				tmp->right = head;
				head->height = std::max(height(head->left), height(head->right)) + 1;
				tmp->height = std::max(height(tmp->left), height(tmp->right)) + 1;
				return (tmp);
			}
			Node	*rr_rotation(Node *head)
			{
				Node *tmp = head->right;
				head->right = tmp->left;
				tmp->left = head;
				head->height = std::max(height(head->left), height(head->right)) + 1;
				tmp->height = std::max(height(tmp->left), height(tmp->right)) + 1;
				return (tmp);
			}
			Node	*lr_rotation(Node *head)
			{
				head->left = rr_rotation(head->left);
				return (ll_rotation(head));
			}
			Node	*rl_rotation(Node *head)
			{
				head->right = ll_rotation(head->right);
				return (rr_rotation(head));
			}
			Node *new_node(int value)
			{
				Node *tmp = new Node;
				tmp->value = value;
				tmp->left = NULL;
				tmp->right = NULL;
				tmp->parent = NULL;
				tmp->height = 1;
				return (tmp);
			}
			Node	*insert_in_my_tree(int value)
			{
				Node *tmp = new_node(value);
				if (this->_root == NULL)
				{
					this->_root = tmp;
					std::cout << "inserted root : " << value << std::endl;
					return(tmp);
				}
				Node *tmp_parent = this->_root;
				while (tmp_parent)
				{
					if (tmp_parent->value > value)
					{
						if (tmp_parent->left == NULL)
						{
							tmp_parent->left = tmp;
							tmp->parent = tmp_parent;
							std::cout << "----------------------------" << std::endl;
							std::cout << "inserted left : " << value << std::endl;
							std::cout << "my parent : " << tmp_parent->value << std::endl;
							std::cout << "----------------------------" << std::endl;
							return (tmp);
							break ;
						}
						tmp_parent = tmp_parent->left;
					}
					else
					{
						if (tmp_parent->right == NULL)
						{
							tmp_parent->right = tmp;
							tmp->parent = tmp_parent;
							std::cout << "----------------------------" << std::endl;
							std::cout << "inserted right : " << value << std::endl;
							std::cout << "my parent : " << tmp_parent->value << std::endl;
							std::cout << "----------------------------" << std::endl;
							return (tmp);
							break ;
						}
						tmp_parent = tmp_parent->right;
					}
				}
				return (tmp);
			}
			int		balance_factor(Node *head)
			{
				int  left_height = height(head->left);
				int  right_height = height(head->right);
				return (left_height - right_height);
			}
			void 	balance_my_tree(Node *tmp)
			{
				// Node *tmp = this->_root;
				while (tmp)
				{
					if (balance_factor(tmp) == 2)
					{
						if (balance_factor(tmp->left) == 1)
							tmp = ll_rotation(tmp);
						else
							tmp = lr_rotation(tmp);
						// std::cout << "balance factor : " << balance_factor(tmp)  << " | tmp_value : " << tmp->value << " | parent_value : " << tmp->parent->value << std::endl;
						_root = tmp;
						// std::cout << "tmp_right : " << tmp->right->value << " | tmp_left : " << tmp->left->value  << " | current_value : " << tmp->value << std::endl;
						// break;
					}
					else if (balance_factor(tmp) == -2)
					{
						if (balance_factor(tmp->right) == -1)
							tmp = rr_rotation(tmp);
						else
							tmp = rl_rotation(tmp);
						_root = tmp;
						// break;
					}
					tmp = tmp->parent;
				}
			}
			void print2DUtil(Node *root, int space)
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
			std::cout<<root->value<<"\n";
		
			// Process left child
			print2DUtil(root->left, space);
		}	
		// Wrapper over print2DUtil()
		
		void print2D()
		{
			// Pass initial space count as 0
			Node *root = this->_root;
			print2DUtil(root, 0);
		}
			void	avl_insert(int value)
			{
				Node *tmp;
				tmp = insert_in_my_tree(value);
				balance_my_tree(tmp);
			}
		private:
			Node *_root;
	};
};
