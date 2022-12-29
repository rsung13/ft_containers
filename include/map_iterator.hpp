/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:07:16 by rsung             #+#    #+#             */
/*   Updated: 2022/12/23 15:15:43 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iostream>

namespace	ft
{
	template <typename T, typename node_pointer>
	class	bidirectional_iterator
	{
			public:

				typedef T									value_type;
				typedef T*									pointer;
				typedef T&									reference;
				typedef std::ptrdiff_t						difference_type;
				typedef std::bidirectional_iterator_tag		iterator_category;

			private:

				node_pointer								_ptr;

			public:

				bidirectional_iterator() : _ptr(NULL) {}
				bidirectional_iterator(node_pointer ptr) : _ptr(ptr) {}
				bidirectional_iterator(bidirectional_iterator const &rhs) : _ptr(rhs._ptr) {}
				bidirectional_iterator& operator=(const bidirectional_iterator& rhs)
				{
					this->_ptr = rhs._ptr;
					return (*this);
				}
				virtual ~bidirectional_iterator() {}

				operator bidirectional_iterator<const T, node_pointer>() const
				{
					return (bidirectional_iterator<const T, node_pointer>(this->_ptr));
				}

				bidirectional_iterator	get_node() const {return (this->_ptr);}

				template <typename T1, typename T2>
				friend class bidirectional_iterator;

				friend bool operator==(const bidirectional_iterator& lhs, const bidirectional_iterator& rhs) {return (lhs._ptr == rhs._ptr);}
				friend bool operator!=(const bidirectional_iterator& lhs, const bidirectional_iterator& rhs) {return (lhs._ptr != rhs._ptr);}
				bidirectional_iterator &operator++()
				{
					if (_ptr && _ptr->right != NULL)
					{
						_ptr = _ptr->right;
						while (_ptr->left != NULL)
							_ptr = _ptr->left;
						return (*this);
					}
					else
					{
						node_pointer	tmp = _ptr;
						_ptr = _ptr->parent;
						while (_ptr->left != tmp)
						{
							tmp = _ptr;
							_ptr = _ptr->parent;
						}
					}
					return (*this);
				}
				bidirectional_iterator operator++(int)
				{
					bidirectional_iterator	tmp;

					tmp = *this;
					++(*this);
					return (tmp);
				}

				bidirectional_iterator operator--()
				{
					if (_ptr->left != NULL)
					{
						_ptr = _ptr->left;
						while (this->_ptr->right)
							this->_ptr = this->_ptr->right;
						return (*this);
					}
					else
					{
						node_pointer	tmp = _ptr;
						_ptr = _ptr->parent;
						while (_ptr->right != tmp)
						{
							tmp = _ptr;
							_ptr = _ptr->parent;
						}
					}
					return (*this);
				}
				bidirectional_iterator operator--(int)
				{
					bidirectional_iterator	tmp;

					tmp = *this;
					--(*this);
					return (tmp);
				}

				reference operator*() {return (this->_ptr->_pair);}
				pointer operator->() {return (&_ptr->_pair);}
				reference operator*() const {return (this->_ptr->_pair);}
				pointer operator->() const {return (&_ptr->_pair);}

			node_pointer getNode() const {return _ptr;}
			/*bool	operator==(const bidirectional_iterator& other) const {return _ptr == other.getNode();}
			bool	operator!=(const bidirectional_iterator& other) const {return _ptr == other.getNode();}*/
	};

	template <typename T, typename node_pointer>
	class	const_bidirectional_iterator
	{
		public:

			typedef T											value_type;
			typedef const T*									pointer;
			typedef const T&									reference;
			typedef std::ptrdiff_t								difference_type;
			typedef std::bidirectional_iterator_tag				iterator_categor;

		private:

			node_pointer					_ptr;

		public:

			const_bidirectional_iterator() : _ptr(NULL) {}
			const_bidirectional_iterator(node_pointer ptr) : _ptr(ptr) {}
			const_bidirectional_iterator(const_bidirectional_iterator const& rhs) : _ptr(rhs._ptr) {}
			const_bidirectional_iterator &operator=(const const_bidirectional_iterator& rhs)
			{
				this->_ptr = rhs._ptr;
				return (*this);
			}
			virtual ~const_bidirectional_iterator() {}

			operator const_bidirectional_iterator<const T, node_pointer>() const
			{
				return (const_bidirectional_iterator<const T, node_pointer>(this->_ptr));
			}

			const_bidirectional_iterator	get_node() const {return (this->_ptr);}

			template<typename T1, typename T2>
			friend class bidirectional_iterator;

			friend bool	operator==(const const_bidirectional_iterator& lhs, const const_bidirectional_iterator& rhs) {return (lhs._ptr == rhs._ptr);}
			friend bool operator!=(const const_bidirectional_iterator& lhs, const const_bidirectional_iterator& rhs) {return (lhs._ptr != rhs._ptr);}
			const_bidirectional_iterator &operator++()
			{
				if (_ptr && _ptr->right != NULL)
				{
					_ptr = _ptr->right;
					while (_ptr->left != NULL)
						_ptr = _ptr->left;
					return (*this);
				}
				else
				{
					node_pointer	tmp = _ptr;
					_ptr = _ptr->parent;
					while (_ptr->left != tmp)
					{
						tmp = _ptr;
						_ptr = _ptr->parent;
					}
				}
				return (*this);
			}
			const_bidirectional_iterator operator++(int)
			{
				const_bidirectional_iterator	tmp;

				tmp = *this;
				++(*this);
				return (tmp);
			}

			const_bidirectional_iterator &operator--()
			{
				if (_ptr->left != NULL)
				{
					_ptr = _ptr->left;
					while (this->_ptr->right)
						this->_ptr = this->_ptr->right;
					retrun (*this);
				}
				else
				{
					node_pointer	tmp = _ptr;
					_ptr = _ptr->parent;
					while (_ptr->right != tmp)
					{
						tmp = _ptr;
						_ptr = _ptr->parent;
					}
				}
				return (*this);
			}
			const_bidirectional_iterator operator--(int)
			{
				const_bidirectional_iterator	tmp;

				tmp = *this;
				--(*this);
				return (tmp);
			}

			reference operator*() {return (this->_ptr->value);}
			reference operator*() const {return (this->_ptr->value);}
			pointer operator->() {return (&_ptr->value);}
			pointer operator->() const {return (&_ptr->value);}

			node_pointer getNode() const {return _ptr;}
			/*bool	operator==(const const_bidirectional_iterator& other) const {return _ptr == other.getNode();}
			bool	operator!=(const const_bidirectional_iterator& other) const {return _ptr == other.getNode();}*/
	};
}

#endif
