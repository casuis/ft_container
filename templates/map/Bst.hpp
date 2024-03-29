/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:38:49 by asimon            #+#    #+#             */
/*   Updated: 2023/02/20 20:29:42 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BST_HPP__
# define __BST_HPP__
# include "../../private/header.hpp"

namespace ft{


	template <typename Key, typename Value>
	class Node
	{
		friend 	class ft::_Rb_tree<Key, Value>;
		friend	class ft::map<Key, Value>;


		public:
			typedef typename ft::pair<Key, Value>		pair_type;
			typedef Key									key_type;
			typedef Value								mapped_type;
			typedef ft::Node<Key, Value>				node_type;
		////////////////////////////////////////////////////////////////////////////////
		/*                              Attributs                                     */
		////////////////////////////////////////////////////////////////////////////////
			Node*						left;
			Node*						right;
			Node*						parent;
			
			ft::pair<Key, Value>		pair;
			bool						black;
			bool						isLeftChild;

			bool						sentinel;
		
		////////////////////////////////////////////////////////////////////////////////
		/*                              Functions                                     */
		////////////////////////////////////////////////////////////////////////////////
		
			Node(ft::pair<Key, Value>& param) {
				this->parent = 0x0;
				this->left = 0x0;
				this->right = 0x0;
				this->pair = param;
				this->black = false;
				this->isLeftChild = false;
				this->sentinel = false;
			}
		
			Node(Key key, Value value){
				ft::pair<Key, Value>		tmp(key, value);		
				
				this->parent = 0x0;
				this->left = 0x0;
				this->right = 0x0;
				this->pair = tmp;
				this->black = false;
				this->isLeftChild = false;
				this->sentinel = false;
				return ;
			};
			
			Node(){
				ft::pair<Key, Value>		tmp;
				this->parent = 0x0;
				this->pair = tmp;
				this->left = 0x0;
				this->right = 0x0;
				this->black = true;
				this->isLeftChild = false;
				this->sentinel = true;
			};
			
			~Node() {};

			bool		operator<(node_type const & rhs) const {
				if (this->pair.first == rhs.pair.first)
					return (this->pair.second < rhs.pair.second);
				return (this->pair.first < rhs.pair.first);
			}

			bool		operator<=(node_type const & rhs) const {
				return (this->pair.first <= rhs.pair.first);
			}

			bool		operator>(node_type const & rhs) const {
				return (rhs < this);
			}
			
			bool		operator>=(node_type const & rhs) const {
				return (rhs <= this);
			}

			bool		operator==(node_type const & rhs) const {
				return (this->pair.first == rhs.pair.first && this->pair.second == rhs.pair.second);
			}

			bool		operator!=(node_type const & rhs) const {
				if (this->sentinel || rhs.sentinel)
					return (this->sentinel && rhs.sentinel && (this->parent == rhs.parent));
				return (this->pair.first != rhs.pair.first || this->pair.second != rhs.pair.second);
			}
	};
	
	
////////////////////////////////////////////////////////////////////////////////
	
	
	template <typename Key, typename Value, typename Compare, typename NodeType, class Allocator>
	class _Rb_tree {
		friend			class ft::map<Key, Value, Compare>;
		friend			class ft::_Rb_tree_iterator<ft::pair<Key, Value>, ft::Node<Key, Value> >;
		
			
		public:
		////////////////////////////////////////////////////////////////////////////////
		/*                              Member Type                                   */
		////////////////////////////////////////////////////////////////////////////////
		
			typedef Allocator					allocator_type;
			typedef Key							key_type;
			typedef Value						value_type;
			typedef Key*						key_pointer;
			typedef Value*						value_pointer;
			typedef ft::Node<Key, Value>		node;
			typedef Compare						key_compare;	
			
		////////////////////////////////////////////////////////////////////////////////
		/*                              Constructors                                  */
		////////////////////////////////////////////////////////////////////////////////
		
			_Rb_tree(const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(key_compare()), root(0x0), size(0) {
				sentinel = this->_alloc.allocate(1);;
				_alloc.construct(sentinel, Node<Key, Value>());
				return ;
			};
			
			~_Rb_tree() {
				freeRb_tree(root);
				_alloc.destroy(sentinel);
				_alloc.deallocate(sentinel, 1);
			};

		////////////////////////////////////////////////////////////////////////////////
		/*                              Methodes                                      */
		////////////////////////////////////////////////////////////////////////////////
		/* free section */

			void		freeRb_tree() {
				freeRb_tree(root);
				return ;
			}
			
			void		freeRb_tree(node* pos) {
				if (pos == sentinel || pos == 0x0)
					return;
				freeRb_tree(pos->left);
				freeRb_tree(pos->right);
				_alloc.destroy(pos);
				_alloc.deallocate(pos, 1);
				size = 0;
				root = 0x0;
				return ;
			}
		
		////////////////////////////////////////////////////////////////////////////////
		
		/* Add section */
		public:
			
			void	addNode(node*newNode) {
				addNode(newNode, this->root);
				return ;
			}

			void	addNode(node *newNode, node *pos) {
				if (root == 0x0){
					root = newNode;
					this->sentinel->left = root;
					this->size += 1;
					this->root->parent = this->sentinel;
					this->root->left = sentinel;
					this->root->right = sentinel;
					this->root->black = true;
					updateSentinel();
					return ;
				}
				else{
					if (newNode->pair.first == pos->pair.first)
						return ;
					if (_comp(newNode->pair.first, pos->pair.first) && pos->left->sentinel){
						pos->left = newNode;
						newNode->parent = pos;
						newNode->isLeftChild = true;
						newNode->left = sentinel;
						newNode->right = sentinel;
						this->size += 1;
					}
					else if (_comp(newNode->pair.first, pos->pair.first) && !pos->left->sentinel){
						addNode(newNode, pos->left);
					}
					else if (_comp(pos->pair.first, newNode->pair.first) && pos->right->sentinel){
						pos->right = newNode;
						newNode->parent = pos;
						newNode->isLeftChild = false;
						newNode->left = sentinel;
						newNode->right = sentinel;
						this->size += 1;
					}
					else {
						addNode(newNode, pos->right);
					}
					checkColor(newNode);
					updateSentinel();
				}
				return ;
			};

			void		updateSentinel() {
				this->sentinel->right = getLast();
				this->sentinel->left = getLast();
			}

			void		updateNode(node* pos, value_type value) {
				pos->pair.second = value;
				this->_alloc.destroy(pos);
			}

			node*		createNode(key_type key, value_type value) {
				node	*newNode;

				newNode = this->_alloc.allocate(1);
				this->_alloc.construct(newNode, node(key, value));
				return (newNode);
			}

			node*		createNode(ft::pair<Key, Value>& param) {
				node	*newNode;

				newNode = this->_alloc.allocate(1);
				this->_alloc.construct(newNode, node(param));
				return (newNode);
			}

			////////////////////////////////////////////////////////////////////////////////
			/* Search section */
	

			node*		searchNode(const key_type value) const {
				return (searchNode(value, this->root));
			}

			node*		searchNode(const key_type& value, node* pos) const {
				if (root == 0x0)
					return (0x0);
				if (pos->sentinel == true)
					return (0x0);
				if (_comp(value, pos->pair.first))
					return (searchNode(value, pos->left));
				if (_comp(pos->pair.first, value))
					return (searchNode(value, pos->right));
				if (!_comp(value, pos->pair.first) && !_comp(pos->pair.first, value))
					return (pos);
				return (0x0);
			}

			////////////////////////////////////////////////////////////////////////////////
			/* Delete section */			
			
			void		deleteNode(const key_type& value) {
				deleteNode(value, this->root);
				return ;
			}
			
			/* find the node to delete*/
			void		deleteNode(const key_type& value, node *pos){
				if (_comp(value, pos->pair.first) && !pos->left->sentinel ) {
					deleteNode(value, pos->left);
					return ;
				}
				else if (_comp(pos->pair.first, value) && !pos->right->sentinel) {
					deleteNode(value, pos->right);
					return ;
				}
				else if (!_comp(pos->pair.first, value) && !_comp(value, pos->pair.first))
					deleteNode(pos);
				return ;
			}

			/* delete node */
			void		deleteNode(node* pos) {
				bool								need_to_fix = pos->black;
				bool								is_left = pos->isLeftChild;
				node								*fixNode = pos->parent;
				node								*swap_node;
				
				if (pos->right->sentinel && pos->left->sentinel){
					if (pos->isLeftChild)
						pos->parent->left = sentinel;
					else
						pos->parent->right = sentinel;
					deleteLeaf(pos);
					if (fixNode != sentinel)
						fixDelete(fixNode, is_left, need_to_fix);
					updateSentinel();
					return ;
				}
				
				swap_node = returnSuccessor(pos);
				if (swap_node->sentinel)
					swap_node = returnPredecessor(pos);
				is_left = swap_node->isLeftChild;
				need_to_fix = swap_node->black;
				swapLeaf(swap_node, pos);
				fixNode = pos->parent;
				deleteLeaf(pos);
				fixDelete(fixNode, is_left, need_to_fix);
				updateSentinel();
				return ;
			}
			
			/* NEED TO SWAP ALL NODE AND NOT JUST PAIR */
			void		swapLeaf(node* swap_node, node* pos) {
				node*								parent_tmp = pos->parent;
				node*								Lchild_tmp = pos->left;
				node*								Rchild_tmp = pos->right;
				bool								is_left = pos->isLeftChild;
				bool								black_tmp = pos->black;

				if (pos == this->root)
					this->root = swap_node;
				pos->left = swap_node->left; 
				if (!swap_node->left->sentinel)
					pos->left->parent = pos;
				pos->right = swap_node->right;
				if (!swap_node->right->sentinel)
					pos->right->parent = pos;
				if (pos != swap_node->parent) {
					pos->parent = swap_node->parent;
					if (swap_node->isLeftChild)
						pos->parent->left = pos;
					else
						pos->parent->right = pos;
					swap_node->left = Lchild_tmp;
					swap_node->left->parent = swap_node;
					swap_node->right = Rchild_tmp;
					swap_node->right->parent = swap_node;
				}
				else {
					pos->parent = swap_node;
					if (swap_node->isLeftChild) {
						swap_node->left = pos;
						swap_node->right = Rchild_tmp;
						swap_node->right->parent = swap_node;
					}
					else {
						swap_node->right = pos;
						swap_node->left = Lchild_tmp;
						swap_node->left->parent = swap_node;
					}
				}
				swap_node->parent = parent_tmp;
				if (pos->isLeftChild)
					parent_tmp->left = swap_node;
				else
					parent_tmp->right = swap_node;
				pos->black = swap_node->black;
				pos->isLeftChild = swap_node->isLeftChild;
				swap_node->black = black_tmp;
				swap_node->isLeftChild = is_left;
				return;	
			}
				
			void		deleteLeaf(node *pos) {
				if (pos == root)
					this->root = 0x0;
				if (pos->isLeftChild) {
					if (!pos->left->sentinel) {
						pos->parent->left = pos->left;
						pos->left->parent = pos->parent;
						pos->left->isLeftChild = true;
					}
					else if (!pos->right->sentinel) {
						pos->parent->left = pos->right;
						pos->right->parent = pos->parent;
						pos->right->isLeftChild = true;
					}
					else
						pos->parent->left = sentinel;
				}
				else if (!pos->isLeftChild) {
					if (!pos->left->sentinel) {
						pos->parent->right = pos->left;
						pos->left->parent = pos->parent;
						pos->left->isLeftChild = false;
					}
					else if (!pos->right->sentinel) {
						pos->parent->right = pos->right;
						pos->right->parent = pos->parent;
						pos->right->isLeftChild = false;
					}
					else
						pos->parent->right = sentinel;
				}
				this->_alloc.destroy(pos);
				this->_alloc.deallocate(pos, 1);
				this->size -= 1;
			}

			void		fixDelete(node* pos, bool lft, bool need_to_fix = true) {
				if (!need_to_fix || pos == sentinel)
					return;
				if (lft && !pos->left->black)
					pos->left->black = true;
				else if (!lft && !pos->right->black)
					pos->right->black = true;
				else if (is_M_RED_sib(pos, lft))
					M_RED_sib(pos, lft);
				else if (is_black_sibling_M_RED_child(pos, lft))
					black_sibling_M_RED_child(pos, lft);
				else if (is_black_sibling_black_child(pos, lft))
					black_sibling_black_child(pos, lft);
					
				return ;
			}
			
			/////////////////////////////////////////////////////////////////////////
				/* Fix deletion comparaisons */
				
				bool		is_black_sibling_black_child(node *pos, bool lft) {
					/* check if pos sibling have only black child */
					return ((lft && !pos->right->sentinel 
						&& (pos->right->left->black && pos->right->right->black))
						|| (!lft && !pos->left->sentinel 
						&& (pos->left->left->black && pos->left->right->black)));
				}
				
				bool		is_black_sibling_M_RED_child(node *pos, bool lft) {
					/* check if pos sibling have a M_RED child */
					return ((lft && !pos->right->sentinel 
						&& (!pos->right->left->black || !pos->right->right->black))
						|| (!lft && !pos->left->sentinel 
						&& (!pos->left->left->black || !pos->left->right->black))); 
				}

				bool		is_M_RED_sib(node* pos, bool lft) {
					/* Check if sibling is M_RED */
					return ((lft && !pos->right->black) || (!lft && !pos->left->black));
				}
			
				/////////////////////////////////////////////////////////////////////////
				/* Fix deletion operations */
			
				void		black_sibling_M_RED_child(node *pos, bool lft) {
					/* Check what rotation need to be done */
					bool		color_swap;
					
					if (lft && !pos->right->sentinel && !pos->right->right->black) {
						pos->right->black = pos->black;
						pos->black = true;
						pos->right->right->black = true;
						leftRotation(pos); 	
					}
					else if (!lft && !pos->left->sentinel && !pos->left->left->black) {
						pos->left->black = pos->black;
						pos->black = true;
						pos->left->left->black = true;
						rightRotation(pos); 	
					}
					else if (lft && !pos->right->sentinel && !pos->right->left->black) {
						color_swap = pos->right->left->black;
						pos->right->left->black = pos->right->black;
						pos->right->black = color_swap;
						rightRotation(pos->right);
						black_sibling_M_RED_child(pos, lft);
					}
					else if (!lft && !pos->left->sentinel && !pos->left->right->black) {
						color_swap = pos->left->right->black;
						pos->left->right->black = pos->left->black;
						pos->left->black = color_swap;
						leftRotation(pos->left);
						black_sibling_M_RED_child(pos, lft);
					}
				}

				void		black_sibling_black_child(node *pos, bool lft) {
					if (lft) {
						pos->right->black = false;
						if (!pos->black)
							pos->black = true;
						else
							fixDelete(pos->parent, pos->isLeftChild);
					}
					else {
						pos->left->black = false;
						if (!pos->black)
							pos->black = true;
						else
							fixDelete(pos->parent, pos->isLeftChild);
					}
					return ;
				}
			
				void	M_RED_sib(node* pos, bool lft) {
					bool	color_swap;
					if (lft) {
						color_swap = pos->right->black;
						pos->right->black = pos->black;
						pos->black = color_swap;
						leftRotation(pos);
						fixDelete(pos, lft);
					}
					else {
						color_swap = pos->left->black;
						pos->left->black = pos->black;
						pos->black = color_swap;
						rightRotation(pos);
						fixDelete(pos, lft);
					}
					return ;
				}
				
			////////////////////////////////////////////////////////////////////////////////

			/* the biggest of the smallest */
			static node*		returnSuccessor(node *pos) {
				node		*ret;
				
				if (pos == 0x0 || !pos->left || !pos->right)
					return (0x0);
				if (pos->left->sentinel)
					return (pos->left);
				else {
					ret = pos->left;
					while (!ret->right->sentinel) // look for the largest node less than pos
						ret = ret->right;
					return (ret);
				}
				return (0x0);
			}

			/* the smallest of the biggest */
			static node*		returnPredecessor(node *pos) {
				node		*ret;
				
				if (pos == 0x0 || !pos->left || !pos->right)
					return (0x0);
				if (pos->right->sentinel)
					return (pos->right);
				else {
					ret = pos->right;
					while (!ret->left->sentinel) // look for the smalest node greater than pos
						ret = ret->left;
					return (ret);
				}
				return (0x0);
			}

			////////////////////////////////////////////////////////////////////////////////
			/* Rotations */

			node*		leftRotation(node *pos) {
				node		*ret = pos->right;
				node		*tmp = pos->parent;
				
				/* Rotate */
				pos->right = ret->left;
				ret->left = pos;
				
				/* Update parents */
				if (!pos->right->sentinel)
					pos->right->parent = pos;
				ret->isLeftChild = pos->isLeftChild;
				pos->isLeftChild = true;
				pos->parent = ret;
				ret->parent = tmp;
				pos->right->isLeftChild = false;

				if (ret->isLeftChild)
					tmp->left = ret;
				else
					tmp->right = ret;
					
				/* Update root */
				if (this->root == pos)
					this->root = ret;
					
				return (ret);
			}

			node*		rightRotation(node *pos) {
				node	*ret = pos->left;
				node	*tmp = pos->parent;
				
				/* Rotate */
				pos->left = ret->right;
				ret->right = pos;
				
				/* Update parents */
				if (!pos->left->sentinel)
					pos->left->parent = pos;
				ret->isLeftChild = pos->isLeftChild;
				pos->isLeftChild = false;
				pos->parent = ret;
				ret->parent = tmp;
				pos->left->isLeftChild = true;
				
				if (ret->isLeftChild)
					tmp->left = ret;
				else
					tmp->right = ret;
				
				/* Update root */
				if (this->root == pos)
					this->root = ret;
				
				/* Update colors */
				return (ret);
			}

			node*		leftRightRotation(node *pos) {
				node 	*leftNode = leftRotation(pos->left);
				node	*ret = rightRotation(leftNode->parent);
				return (ret);
			}

			node*		rightLeftRotation(node *pos) {
				node	*rightNode = rightRotation(pos->right);
				node	*ret = leftRotation(rightNode->parent); 				
				return (ret);
			}

			////////////////////////////////////////////////////////////////////////////////
			/* Check / Updates */
			
			void		checkColor(node *pos) {
				if (root == 0x0 || pos == root || pos->sentinel)
					return ;
				if (!pos->black && !pos->parent->black) {
					pos = correctTree(pos);
				}
				return (checkColor(pos->parent));
			}

			node*		correctTree(node *pos) {
				if (pos == sentinel)
					return (pos);
				if (pos->parent->isLeftChild) {
					if (pos->parent->parent->right->black) {
						pos = rotateNode(pos);
					}
					else {
						pos->parent->parent->right->black = true;
						pos->parent->parent->black = false;
						pos->parent->black = true;
						this->root->black = true;
						this->sentinel->black = true;
						return (pos);
					}
				}
				else {
					if (pos->parent->parent->left->black) {
						pos = rotateNode(pos);
					}
					else {
						pos->parent->parent->left->black = true;
						pos->parent->parent->black = false;
						pos->parent->black = true;
						this->root->black = true;
						this->sentinel->black = true;
						return (pos) ;
					}
				}
				return (pos);
			}

			node*		rotateNode(node *pos) {
				if (pos->isLeftChild) {
					if (pos->parent->isLeftChild) {
						pos = rightRotation(pos->parent->parent);
						pos->black = true;
						pos->right->black = false;
						pos->left->black = false;
						this->root->black = true;
						this->sentinel->black = true;
					}
					else { 
						pos = rightLeftRotation(pos->parent->parent);
						pos->black = true;
						pos->right->black = false;
						pos->left->black = false;
						this->root->black = true;
						this->sentinel->black = true;
					}
				}
				else {
					if (!pos->parent->isLeftChild) {
						pos = leftRotation(pos->parent->parent);
						pos->black = true;
						pos->right->black = false;
						pos->left->black = false;
						this->root->black = true;
						this->sentinel->black = true;
					}
					else {
						pos = leftRightRotation(pos->parent->parent);
						pos->black = true;
						pos->right->black = false;
						pos->left->black = false;
						this->root->black = true;
						this->sentinel->black = true;
					}
				}
				return (pos);
			}
			////////////////////////////////////////////////////////////////////////////////
			/* Height section */

			size_t		returnHeight() const {
				if (root == 0x0)
					return (0);
				return (returnHeight(root));
			}

			size_t		returnHeight(node *pos) const {
				if (pos->sentinel || root == 0x0)
					return (0);
				int		leftHeight = returnHeight(pos->left) + 1;
				int		rightHeight = returnHeight(pos->right) + 1;
				if (leftHeight > rightHeight)
					return (leftHeight);
				return (rightHeight);
			}

			size_t		returnBlackNodes() {
				return (returnBlackNodes(this->root));
			}

			size_t		returnBlackNodes(node* pos) {
				if (root == 0x0)
					return (0);
				if (pos->sentinel)
					return (1);
					
				size_t	leftBnodes = returnBlackNodes(pos->left);
				size_t	rightBnodes = returnBlackNodes(pos->right);
				if (rightBnodes != leftBnodes) {
					std::cerr << "unbalanced on pos: [" << pos->pair.first << "]" << std::endl;
					exit(1);
				}

				if (pos->black)
					leftBnodes++;
				return (leftBnodes);
			}

			////////////////////////////////////////////////////////////////////////////////
			/* Geter section */

			node*		getFirst() const {
				node*	tmp = this->root;
				if (!size)
					return (sentinel);
				while (!tmp->left->sentinel)
					tmp = tmp->left;
				return (tmp);
			}

			node*		getLast() const {
				node*	tmp = this->root;
				if (!size)
					return (sentinel);
				while (!tmp->right->sentinel)
					tmp = tmp->right;
				return (tmp);
			}
				
			////////////////////////////////////////////////////////////////////////////////
			/* + */
			
			void		printRb_treeSorted(node* pos) const {
				if (pos->left != sentinel)
					printRb_treeSorted(pos->left);
				std::cout << "value : [" << pos->pair.first  << "]" << std::endl;
				if (pos->right != sentinel)
					printRb_treeSorted(pos->right);
				return ;
			}

			void		printRb_treeFormat(int level, int k, node *pos) const { 
				if (pos->sentinel || this->root == 0x0)
					return ;
				printRb_treeFormat(level + 1, k, pos->left);
				printRb_treeFormat(level + 1, k, pos->right);

				if (k == level) {
					std::cout << ((pos->isLeftChild) ? M_CYAN : M_YELLOW) << " |" << M_RESET 
					<< ((pos->black) ? M_BLACK : M_RED) << "value : [" << pos->pair.first  
					<< "] | p: [" << pos->parent->pair.first << "]" << M_RESET << ((pos->isLeftChild) ? M_CYAN : M_YELLOW) << "| " << M_RESET;
				}
				return ;
			}


			void		printAllRb_tree() const {
				size_t		size = this->returnHeight();
				std::cout << "size : " << size << std::endl;
				
				std::cout << 
				M_CYAN << "left child" << M_RESET << " | " <<
				M_YELLOW << "right child" << M_RESET << std::endl  << std::endl;
				for (size_t i = 0; i < size; i++) {
					printRb_treeFormat(0, i, this->root);
					std::cout << std::endl << M_GREEN << "\t++++++++++++++++" << M_RESET << std::endl;
				}
				std::cout  << std::endl << M_YELLOW << "-------------END OF Rb_tree PRINT-------------" << M_RESET << std::endl << std::endl;
			}

			void		print(int choice = 0) const {
				switch (choice) {
					case 0:
						printAllRb_tree();
						break;
					case 1:
						printRb_treeSorted(this->root);
						break;
					default:
						printAllRb_tree();
				}
				return ;
			}

			ft::_Rb_tree<Key, Value, Compare>	operator=(typename ft::_Rb_tree<Key, Value, Compare>& tree) {
				this->root = tree.root;
				this->sentinel = tree.sentinel;
				this->_alloc = tree._alloc;
				this->_comp = tree._comp;
				return (*this);
			}

			size_t			max_size() const {
				return (this->_alloc.max_size());
			}
			
		private:
		////////////////////////////////////////////////////////////////////////////////
		/*                              Attributs                                     */
		////////////////////////////////////////////////////////////////////////////////
		
			Allocator							_alloc;
			key_compare							_comp;
			Node<Key, Value>					*root;
			Node<Key, Value>					*sentinel;
			size_t								size;

			
	};

}

#endif