/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:28:55 by rsung             #+#    #+#             */
/*   Updated: 2022/12/23 15:26:29 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <functional>
#include <memory>
#include "utils.hpp"
#include "vector_iterator.hpp"
#include "map_iterator.hpp"

namespace	ft
{
	template <typename T>
	struct	mapNode
	{
		typedef T						value_type;
		typedef mapNode					Node;

		value_type						_pair;
		Node*							parent;
		Node*							left;
		Node*							right;
		//other??

		mapNode() : _pair(), parent(NULL), left(NULL), right(NULL) {};
		mapNode(const value_type& val) : _pair(val), parent(NULL), left(NULL), right(NULL) {};
		mapNode(const Node& rhs) : _pair(rhs._pair), parent(rhs.parent), left(rhs.left), right(rhs.right) {};
		virtual ~mapNode(void) {};
	};

	template<typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class	map
	{
		/*
		/	MEMBER TYPES
		*/
		public:

			typedef Key															key_type;
			typedef T															mapped_type;
			typedef Compare														key_compare;
			typedef Allocator													allocator_type;

			typedef ft::pair<const Key, T>										value_type;
			typedef ft::mapNode<value_type>										Node;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;

			typedef typename Allocator::template rebind<Node>::other			node_allocator_type;
			typedef typename Allocator::reference								reference;
			typedef typename Allocator::const_reference							const_reference;
			typedef typename Allocator::pointer									pointer;
			typedef typename Allocator::const_pointer							const_pointer;

			typedef bidirectional_iterator<value_type, Node*>					iterator;
			typedef bidirectional_iterator<const value_type, Node*>				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		private:

		//	Node*					_root;
		//	Node*					_leaf;
			Node*					_s_root;

			allocator_type			_pairAlloc;
			node_allocator_type		_nodeAlloc;

			size_type				_size;
			Compare					_comp;

		public:

			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class	ft::map<Key, T, Compare, Allocator>;

				protected:

					Compare	comp;

					value_compare(Compare c) : comp(c) {}

				public:

					typedef bool			result_type;
					typedef value_type		first_argument_type;
					typedef value_type		second_argument_type;

					bool operator()(const value_type& lhs, const value_type& rhs) const {return (comp(lhs.first, rhs.first));}
			};

			/*
			/ CONSTRUCTOR/DESTRUCTOR
			*/
			explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _s_root(NULL), _pairAlloc(alloc), _nodeAlloc(), _size(0), _comp(comp)
			{
				_s_root = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_s_root, Node());
				
			}

			template <typename InputIt>
			map(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _s_root(NULL), _nodeAlloc(alloc), _size(0), _comp(comp)
			{
				_s_root = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_s_root, Node());
				insert(first, last);
			}
			private:
			void	copyTree(Node* node)
			{
				if (node != NULL)
				{
					insert(node->_pair);
					copyTree(node->left);
					copyTree(node->right);
				}
			}
			public:
			map(const map& other) : _pairAlloc(other._pairAlloc), _nodeAlloc(other._nodeAlloc), _size(0), _comp(other._comp)
			{
				_s_root = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_s_root, Node());
				copyTree(other._s_root->right);
			}

			map	&operator=(const map& other)
			{
				this->clear();
				this->_comp = other._comp;
				this->_pairAlloc = other._pairAlloc;
				this->_nodeAlloc = other._nodeAlloc;
				copyTree(other._s_root->right);
				this->_size = other._size;
				return (*this);
			}

			~map()
			{
				clear();
				if (_s_root != NULL)
				{
					_nodeAlloc.destroy(_s_root);
					_nodeAlloc.deallocate(_s_root, 1);
				}
			}

			allocator_type	get_allocator() const {return (this->_nodeAlloc);}
			/*
			/	ELEMENT ACCESS
			*/
			T& operator[](const Key& key) {return (insert(ft::make_pair(key, mapped_type())).first->second);}
			T& at(const Key& key)
			{
				iterator	it = lower_bound(key);

				if (it == end() || _comp(key, (*it).first))
					throw (std::out_of_range("map: out of range"));
				return ((*it).second);
			}
			const T& at(const Key& key) const
			{
				const_iterator	it = lower_bound(key);

				if (it == end() || _comp(key, (*it).first))
					throw (std::out_of_range("map: out of range"));
				return ((*it).second);
			}

			/*
			/ ITERATORS
			*/
			iterator	begin(void)
			{
				if (_size == 0)
					return (iterator(end()));
				Node*	min = _s_root->right;
				if (min == NULL)
					return (iterator(_s_root));
				while (min->left != NULL)
					min = min->left;
				return (iterator(min));
			}
			const_iterator	begin(void) const
			{
				if (_size == 0)
					return (const_iterator(end()));
				Node*	min = _s_root->right;
				if (min == NULL)
					return (const_iterator(_s_root));
				while (min->left != NULL)
					min = min->left;
				return (const_iterator(min));

			}
			iterator	end(void) {return (iterator(_s_root));}
			const_iterator	end(void) const {return (const_iterator(_s_root));}
			reverse_iterator	rbegin(void) {return (reverse_iterator(end()));}
			const_reverse_iterator	rbegin(void) const {return (const_reverse_iterator(end()));}
			reverse_iterator	rend(void) {return (reverse_iterator(begin()));}
			const_reverse_iterator	rend(void) const {return (const_reverse_iterator(begin()));}

			/*
			/ CAPACITY
			*/
			bool	empty() const {return (this->_size == 0);}
			size_type	size() const {return (this->_size);}
			size_type	max_size() const {return (this->_nodeAlloc.max_size());}

			/*
			/	MODIFIERS
			*/
			private:
			void	clearNodes(Node* tmp)
			{
				if (tmp != NULL)
				{	
					if (tmp->left)
						clearNodes(tmp->left);
					if (tmp->right)
						clearNodes(tmp->right);
					if (tmp)
					{
						_nodeAlloc.destroy(tmp);
						_nodeAlloc.deallocate(tmp, 1);
					}
				}
			}

			public:
			void	clear()
			{
				clearNodes(_s_root->right);
				_s_root->left = NULL;
				_s_root->right = NULL;
				_size = 0;
			}
			private:
			ft::pair<iterator, bool>	insertNode(Node*	node)
			{
				Node*	tmp = _s_root->right;
				Node*	parent;

				if (this->empty())
				{
					_s_root->right = node;
					_s_root->left = node;
					if (node != NULL)
						node->parent = _s_root;
					return (ft::make_pair(iterator(node), true));
				}
				while (tmp)
				{
					if (_comp(tmp->_pair.first, node->_pair.first))
					{
						parent = tmp;
						tmp = tmp->right;
					}
					else if (_comp(node->_pair.first, tmp->_pair.first))
					{
						parent = tmp;
						tmp = tmp->left;
					}
					else
						return (ft::make_pair(iterator(tmp), false));
				}
				if (_comp(parent->_pair.first, node->_pair.first))
				{
					parent->right = node;
					node->parent = parent;
				}
				else
				{
					parent->left = node;
					node->parent = parent;
				}
				return (ft::make_pair(iterator(node), true));
			}
			public:
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				Node*	node = _nodeAlloc.allocate(1);

				_nodeAlloc.construct(node, Node(value));
				pair<iterator, bool>	tmp = insertNode(node);

				if (tmp.second == false)
				{
					_nodeAlloc.destroy(node);
					_nodeAlloc.deallocate(node, 1);
				}
				else
					this->_size++;
				return (tmp);
			}
			iterator	insert(iterator pos, const value_type& value)
			{
				(void)pos;
				return (insert(value).first);
			}
			template<typename InputIt>
			void	insert(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
			{
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			}
			void	erase(iterator position)
			{
				if (position == this->end() || position == NULL)
					return ;
				Node* tmp = NULL;
				Node* pos = position.getNode();
				if (_s_root->right == pos && _size == 1)
				{
					_nodeAlloc.destroy(pos);
					_nodeAlloc.deallocate(pos, 1);
					_s_root->left = NULL;
					_s_root->right = NULL;
					_size = 0;
					pos = NULL;
					return ;
				}
				if (pos->left == NULL && pos->right == NULL)
				{
					if (pos->parent->left == pos)
					{
						pos->parent->left = NULL;
						_nodeAlloc.destroy(pos);
						_nodeAlloc.deallocate(pos, 1);
						_size--;
						pos = NULL;
					}
					else if (pos->parent->right == pos)
					{
						pos->parent->right = NULL;
						_nodeAlloc.destroy(pos);
						_nodeAlloc.deallocate(pos, 1);
						_size--;
						pos = NULL;
					}
				}
				else if (pos->left == NULL && pos->right != NULL)
				{
					tmp = pos->right;
					pos->right->parent = pos->parent;
					if (pos->parent->left == pos)
						pos->parent->left = pos->right;
					else if (pos->parent->right == pos)
						pos->parent->right = pos->right;
					_nodeAlloc.destroy(pos);
					_nodeAlloc.deallocate(pos, 1);
					_size--;
					pos = NULL;
				}
				else if (pos->left != NULL && pos->right == NULL)
				{
					tmp = pos->left;
					pos->left->parent = pos->parent;
					if (pos->parent->left == pos)
						pos->parent->left = pos->left;
					else if (pos->parent->right == pos)
						pos->parent->right = pos->left;
					_nodeAlloc.destroy(pos);
					_nodeAlloc.deallocate(pos, 1);
					_size--;
					pos = NULL;
				}
				else if(pos->left != NULL && pos->right != NULL)
				{
					tmp = pos->right;
					while (tmp->left != NULL)
						tmp = tmp->left;
					if (tmp->parent == pos)
					{
						tmp->parent = tmp->parent->parent;
						if (pos->parent->right == pos)
							pos->parent->right = tmp;
						else if (pos->parent->left == pos)
							pos->parent->left = tmp;
						if (pos->left != NULL)
							pos->left->parent = tmp;
						tmp->left = pos->left;
						_nodeAlloc.destroy(pos);
						_nodeAlloc.deallocate(pos, 1);
						_size--;
						pos = NULL; //
					}
					else
					{
						if (tmp->right != NULL)
						{
							Node*	tmp_r = tmp->right;
							tmp_r->parent = tmp->parent;
							if (tmp->parent->left == tmp)
								tmp->parent->left = tmp_r;
							else if (tmp->parent->right == tmp)
								tmp->parent->right = tmp_r;
						}
						else
							tmp->parent->left = NULL;
						tmp->parent = pos->parent;
						if (pos->parent->left == pos)
							pos->parent->left = tmp;
						else if (pos->parent->right == pos)
							pos->parent->right = tmp;
						tmp->left = pos->left;
						tmp->right = pos->right;
						if (pos->left != NULL)
							tmp->left->parent = tmp;
						if (pos->right != NULL)
							tmp->right->parent = tmp;
						_nodeAlloc.destroy(pos);
						_nodeAlloc.deallocate(pos, 1);
						pos = NULL; //
						_size--;
					}
				}
				if (tmp != NULL && tmp->parent == _s_root)
				{
					_s_root->right = tmp;
					_s_root->left = tmp;
				}
			}
			void	erase(iterator first, iterator last)
			{
				iterator	it = first;
				iterator	tempo;
				while (it != last)
				{
					tempo = it;
					it++;
					erase(tempo);
				}
			}
			size_type	erase(const Key& key)
			{
				size_type	size = this->size();
				iterator	occurence = find(key);
				if (occurence == this->end())
					return (0);
				erase(occurence);
				size_type	size_tmp = this->size();
				return (size - size_tmp);
			}

			void	swap(map& other)
			{
				node_allocator_type		n_tmp;
				Compare					c_tmp;
				size_type				s_tmp;
				Node*					tmp;

				n_tmp = other._nodeAlloc;
				c_tmp = other._comp;
				s_tmp = other._size;
				tmp = other._s_root;

				other._nodeAlloc = this->_nodeAlloc;
				other._comp = this->_comp;
				other._size = this->_size;
				other._s_root = this->_s_root;

				this->_nodeAlloc = n_tmp;
				this->_comp = c_tmp;
				this->_size = s_tmp;
				this->_s_root = tmp;
			}

			/*
			/	LOOKUP
			*/
			size_type	count(const Key& key) const
			{
				const_iterator	tmp = this->find(key);
				if (tmp == this->end())
					return (0);
				return (1);
			}

			iterator	find(const Key& key)
			{
				Node*	tmp = _s_root->right;

				while (tmp != NULL)
				{
					if (!_comp(tmp->_pair.first, key) && !_comp(key, tmp->_pair.first))
						break;
					else if (_comp(tmp->_pair.first, key))
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				if (tmp == NULL)
					return (iterator(_s_root));
				return (iterator(tmp));
			}
			const_iterator	find(const Key& key) const
			{
				Node*	tmp = _s_root->right;

				while (tmp != NULL)
				{
					if (!_comp(tmp->_pair.first, key) && !_comp(key, tmp->_pair.first))
						break;
					else if (_comp(tmp->_pair.first, key))
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				if (tmp == NULL)
					return (const_iterator(_s_root));
				return (const_iterator(tmp));

			}

			ft::pair<iterator, iterator>	equal_range(const Key& key)
			{
				return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));	
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const
			{
				return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));	
			}

			iterator	lower_bound(const Key& key)
			{
				iterator	it;
				for (it = this->begin(); it != this->end(); it++)
				{
					if (!_comp(it->first, key))
					{
						return (it);
					}
				}
				return (it);
			}
			const_iterator	lower_bound(const Key& key) const
			{
				const_iterator	it;
				for (it = this->begin(); it != this->end(); it++)
				{
					if (!_comp(it->first, key))
					{
						return (it);
					}
				}
				return (it);

			}

			iterator	upper_bound(const Key& key)
			{
				iterator	it;
				for (it = this->begin(); it != this->end(); it++)
				{
					if (_comp(key, it->first))
					{
						return (it);
					}
				}
				return (it);
			}
			const_iterator	upper_bound(const Key& key) const
			{
				const_iterator	it;
				for (it = this->begin(); it != this->end(); it++)
				{
					if (_comp(key, it->first))
					{
						return (it);
					}
				}
				return (it);

			}

			/*
			/	OBSERVERS
			*/
			key_compare	key_comp() const {return (_comp);}
			value_compare value_comp() const {return (value_compare(key_compare()));}
	};

	template<typename Key, typename T, typename Compare, typename Alloc>
	void	swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	it = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	it2 = rhs.begin();
		while (it != lhs.end())
		{
			if (it->first != it2->first || it->second != it2->second)
				return (false);
			it++;
			it2++;
		}
		return (true);
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return (!(lhs == rhs));}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return (!(lhs < rhs) && !(lhs == rhs));}

template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return (!(lhs > rhs));}

template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return (!(lhs < rhs));}

}

#endif
