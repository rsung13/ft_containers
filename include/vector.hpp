/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:19:44 by rsung             #+#    #+#             */
/*   Updated: 2022/11/30 12:51:07 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <algorithm>
#include <memory>
#include <iostream>
#include "../include/utils.hpp"
#include "../include/vector_iterator.hpp"

namespace	ft
{
	template < typename T, class Alloc = std::allocator<T> >
	class	vector
	{
		public :

			/*
			/	MEMBER TYPES
			*/
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::difference_type		difference_type;
			typedef T*												iterator;
			typedef const T*										const_iterator;
			//typedef	ft::iterator_traits<T*>						iterator;
			//typedef ft::iterator_traits<const T*>					const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/*
			/	CONSTRUCTORS/DESTRUCTOR
			*/
			explicit	vector(const allocator_type &alloc = allocator_type())
			:
				_alloc(alloc),
				_start(NULL),
				_end(NULL),
				_endCapacity(NULL){}

			explicit	vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			{
				_alloc = alloc;

				if (n > this->max_size())
					throw (std::length_error("error: length error"));
				_start = _alloc.allocate(n, 0);
				_end = _start;
				for(size_type i = 0; i < n; i++)
				{
					_alloc.construct(_start + i, val);
					_end++;
				}
				_endCapacity = _end;
			}

			template <typename InputIterator>						
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				_alloc = alloc;
				ft::vector<value_type>	myArr;
				size_type n = 0;
				while (first != last)
				{
					myArr.push_back(*first);
					first++;
					n++;
				}
				_start = _alloc.allocate((n), 0);
				_end = _start;
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(_start + i, myArr[i]);
					_end++;
				}
				_endCapacity = _end;
			}

			vector(const vector &x) : _alloc(x._alloc), _start(NULL), _end(NULL), _endCapacity(NULL)
			{
				this->insert(this->begin(), x.begin(), x.end());
			}

			vector &operator=(const vector &x)
			{
				if (x != *this)
				{
					if (this->_alloc != x._alloc)
					{
						this->clear();
						_alloc.deallocate(_start, this->capacity());
						this->_start = this->_end = this->_endCapacity = NULL;
					}
					this->_alloc = x._alloc;
					assign(x.begin(), x.end());
				}
				return (*this);
			}

			~vector()
			{
				this->clear();
				if (this->_start != NULL)
					_alloc.deallocate(_start, this->capacity());
			}

			/*
			/	MEMBER FUNCTIONS
			*/

			//	ITERATORS
			iterator					begin(void) {return(_start);}
			const_iterator				begin(void) const {return(_start);}
			iterator					end(void)
			{
				if (empty())
					return (begin());
				return (_end);
			}
			const_iterator				end(void) const
			{
				if (empty())
					return(begin());
				return (_end);
			}
			reverse_iterator			rbegin(){return(reverse_iterator(this->end()));}
			const_reverse_iterator	rbegin() const {return(const_reverse_iterator(this->end()));}
			reverse_iterator			rend(){return(reverse_iterator(this->begin()));}
			const_reverse_iterator	rend() const {return(const_reverse_iterator(this->begin()));}
			
			//	CAPACITY
			size_type			size(void) const {return(_end - _start);}
			size_type			max_size(void) const {return(_alloc.max_size());}
			void				resize(size_type n, value_type val = value_type())
			{
				
				if (n > this->max_size())
					throw (std::length_error("error: length error"));
				else if	(n < this->size())
				{
					while (this->size() > n)
					{
						_end--;
						_alloc.destroy(_end);
					}
				}
				else
					this->insert(this->end(), n - this->size(), val);
			}
			size_type			capacity(void) const {return(_endCapacity - _start);}
			bool				empty(void) const {return(size() == 0 ? true : false);}
			void				reserve(size_type n)
			{
				if (n > this->max_size())
					throw (std::length_error("vector::reserve"));
				else if (n > this->capacity())
				{
					pointer		tmp_start = _start;
					size_type	tmp_size = this->size();
					size_type	tmp_capacity = this->capacity();

					_start = _alloc.allocate(n);
					_endCapacity = _start + n;
					_end = _start;
					for (size_type i = 0; i < tmp_size; i++)
					{
						_alloc.construct(_start + i, *tmp_start);
						_alloc.destroy(tmp_start);
						tmp_start++;
						_end++;
					}
					if (tmp_start != NULL)
						_alloc.deallocate(tmp_start - tmp_size, tmp_capacity);
				}
			}

			//	ELEMENT ACCESS
			reference		operator[](size_type n){return(*(_start + n));}
			const_reference	operator[](size_type n) const{return(*(_start + n));}

			reference		at(size_type n)
			{
				if (n >= this->size())
					throw(std::out_of_range("error: calling function at() out of range"));
				return ((*this)[n]);
			}

			const_reference	at(size_type n) const
			{
				if (n >= this->size())
					throw(std::out_of_range("error: calling function at() out of range"));
				return ((*this)[n]);
			}

			reference		front(void){return(*_start);}
			const_reference	front(void) const{return(*_start);}
			reference		back(void){return(*(_end - 1));}
			const_reference	back(void) const{return(*(_end - 1));}

			//	MODIFIERS
			template<typename InputIterator>
				void	assign(InputIterator first, InputIterator last)
				{
					
					this->clear();
					insert(this->_start, first, last);
				}
			
			void		assign(size_type n, const value_type &val)
			{
				this->clear();
				this->insert(this->_start, n, val);
			}

			void	push_back(const value_type &val)
			{
				if (_end == _endCapacity)
				{
					size_type	newCapacity;

					if (this->size() > 0)
						newCapacity = size() * 2;
					else
						newCapacity = 1;
					this->reserve(newCapacity);
				}
				_alloc.construct(_end, val);
				_end++;
			}

			void		pop_back(void)
			{
				_alloc.destroy(_end - 1);
				_end--;
			}

			iterator	insert(iterator pos, const value_type &val)
			{
				difference_type	range = pos - this->begin();

				if (this->_end == this->_endCapacity)
					reserve(this->capacity() + 1);
				pointer	p_pos = this->begin() + range;
				pointer	tmp_end = _end;
				while (tmp_end != p_pos)
				{
					tmp_end--;
					_alloc.construct(tmp_end + 1, *tmp_end);
					_alloc.destroy(tmp_end);
				}
				_alloc.construct(p_pos, val);
				_end++;
				return (iterator(this->begin() + range));
			}

			void		insert(iterator pos, size_type n, const value_type &val)
			{
				if (n == 0)
					return ;
				difference_type	range = pos - this->begin();
				if (this->size() + n > this->capacity())
					reserve(this->size() + n);
				pointer	p_pos = this->begin() + range;
				pointer	tmp_end = _end;
				while (tmp_end != p_pos)
				{
					tmp_end--;
					this->_alloc.construct(tmp_end + n, *(tmp_end));
					this->_alloc.destroy(tmp_end);
				}
				size_type	i = 0;
				while (i < n)
				{
					this->_alloc.construct(p_pos, val);
					i++;
					p_pos++;
				}
				this->_end += n;

				/*if (n == 0)
					return ;
				ft::vector<value_type> tmp(n, val);
				this->insert(pos, tmp.begin(), tmp.end());*/
			}

			template<typename InputIterator>
				void	insert(iterator pos, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				{
					ft::vector<value_type> myArr;
					while (first != last)
					{
						myArr.push_back(*first);
						first++;
					}
					difference_type	r = pos - this->begin();
					size_type	n = myArr.size();
					if (this->capacity() < this->size() + n)
						reserve(this->capacity() + (n));
					pointer	p_pos = this->begin() + r;
					pointer	tmp_end = _end;
					if (!(this->empty()))
					{
						while (tmp_end != p_pos)
						{
							tmp_end--;
							_alloc.construct(tmp_end + n, *tmp_end);
							_alloc.destroy(tmp_end);
						}
					}
					size_type i = 0;
					while (i < n)
					{
						_alloc.construct(p_pos, myArr[i]);
						p_pos++;
						_end++;
						i++;
					}
				}

			void	swap(vector &x)
			{
				if (x == *this)
					return ;
				allocator_type	tmp_alloc = x._alloc;
				pointer			tmp_start = x._start;
				pointer			tmp_end = x._end;
				pointer			tmp_endCapacity = x._endCapacity;

				x._alloc = this->_alloc;
				x._start = this->_start;
				x._end = this->_end;
				x._endCapacity = this->_endCapacity;

				this->_alloc = tmp_alloc;
				this->_start = tmp_start;
				this->_end = tmp_end;
				this->_endCapacity = tmp_endCapacity;
			}

			void	clear(void)
			{
				size_type	actual_size = this->size();

				if (this->empty())
					return ;
				for (size_type i = 0; i < actual_size; i++)
				{
					_end--;
					_alloc.destroy(_end);
				}
			}

			iterator	erase(iterator pos)
			{
				difference_type	marker = pos - this->begin();
				pointer	p_pos = this->begin() + marker;
				pointer	tmp_start = p_pos;
				pointer	tmp_end = this->_end;

				while (tmp_end != this->_start)
				{
					tmp_end--;
					if (tmp_end == p_pos)
					{
						_alloc.destroy(p_pos);
						while (tmp_end != this->_end)
						{
							tmp_end++;
							if (tmp_end != this->_end)
								_alloc.construct(tmp_start, *tmp_end);
							if (tmp_end != this->_end)
								_alloc.destroy(tmp_end);
							tmp_start++;
						}
						_end--;
						return (iterator(p_pos));
					}
				}
				return (iterator(p_pos));
			}

			iterator erase(iterator first, iterator last)
        	{
            	if (first == last)
                	return (first);
            	for (iterator tmp_first = first; tmp_first != last && tmp_first != end(); tmp_first++)
                	_alloc.destroy(tmp_first);
            	iterator	tmp_first = first;
            	while (tmp_first + (last - first) < end())
            	{
                	_alloc.construct(tmp_first, *(tmp_first + (last - first)));
					_alloc.destroy((tmp_first + (last - first)));
                	tmp_first++;
            	}
            	_end -= (last - first);
            	return (first);
        	}

			allocator_type	get_allocator() const{return (_alloc);}

		private :
			allocator_type											_alloc;
			pointer													_start;
			pointer													_end;
			pointer													_endCapacity;
	}; //vector_class

	template <class T, class Alloc>
		bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			typename ft::vector<T>::const_iterator first1 = lhs.begin();
			typename ft::vector<T>::const_iterator first2 = rhs.begin();
			while (first1 != lhs.end())
			{
				if (first2 == rhs.end() || *first1 != *first2)
					return (false);
				++first1;
				++first2;
			}
			return (true);
		}

	template <class T, class Alloc>
		bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}
	
	template <class T, class Alloc>
		bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class T, class Alloc>
		bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}

	template <class T, class Alloc>
		bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (rhs < lhs);
		}

	template <class T, class Alloc>
		bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}
	
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
		{
			x.swap(y);
		}
}

#endif
