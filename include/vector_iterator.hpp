/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:16:35 by rsung             #+#    #+#             */
/*   Updated: 2022/11/16 18:28:35 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#pragma clang diagnostic ignored "-Wtautological-compare"
#include <cstddef>
#include <iterator>

namespace ft
{
	/*
	/	ITERATOR_TRAITS
	*/
	template <typename Iterator>
		struct iterator_traits
		{
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::iterator_category	iterator_category;
		};

	template <typename T>
		struct iterator_traits<T*>
		{
			typedef std::ptrdiff_t						difference_type;
			typedef T									*pointer;
			typedef T									&reference;
			typedef T									value_type;
			typedef std::random_access_iterator_tag		iterator_category;
		};

	template <typename T>
		struct iterator_traits<const T*>
		{
			typedef std::ptrdiff_t						difference_type;
			typedef const T								*pointer;
			typedef const T								&reference;
			typedef T									value_type;
			typedef std::random_access_iterator_tag		iterator_category;
		};

	/*
	/	REVERSE_ITERATOR
	*/
	template <typename Iter>
		class	reverse_iterator
		{
			protected:
				Iter	current;

			public:
				/*
				/	MEMBER TYPES
				*/
				typedef Iter												iterator_type;
				typedef typename iterator_traits<Iter>::difference_type		difference_type;
				typedef typename iterator_traits<Iter>::pointer				pointer;
				typedef typename iterator_traits<Iter>::reference			reference;
				typedef typename iterator_traits<Iter>::value_type			value_type;
				typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
				
				/*
				/	MEMBER FUNCTIONS
				*/
				reverse_iterator(){};

				explicit	reverse_iterator(iterator_type x) : current(x){};

				template <typename U>
					reverse_iterator(const reverse_iterator<U>& other) : current(other.base()){};

				template <class U>
					reverse_iterator& operator=(const reverse_iterator<U>& other)
					{
						current = other.base();
						return (*this);
					}
	
				iterator_type	base() const {return (current);};

				reference	operator*() const
				{
					Iter	temp(current);
					return (*(--temp));
				}

				pointer		operator->() const {return (&(operator*()));}

				reference	operator[](difference_type n) const {return (current[-n - 1]);}

				reverse_iterator& operator++()
				{
					--current;
					return (*this);
				}

				reverse_iterator operator++(int)
				{
					reverse_iterator	tmp(*this);
					--current;
					return (tmp);
				}

				reverse_iterator& operator--()
				{
					++current;
					return (*this);
				}

				reverse_iterator operator--(int)
				{
					reverse_iterator	tmp(*this);
					++current;
					return (tmp);
				}

				reverse_iterator& operator+=(difference_type n)
				{
					current -= n;
					return (*this);
				}

				reverse_iterator& operator -=(difference_type n)
				{
					current += n;
					return (*this);
				}

				reverse_iterator operator+(difference_type n) const
				{
					return reverse_iterator(current - n);
				} // add n to iterator

				reverse_iterator operator-(difference_type n) const
				{
					return reverse_iterator(current + n);
				} // subtract n from iterator

				difference_type operator+(const reverse_iterator& other) const
				{
					return (-(current + other.base()));
				} // difference between two iterators

				difference_type operator-(const reverse_iterator& other) const
				{
					return (other.base() - current);
				} // difference between two iterators

		};

		/*
		/	NON-MEMBER FUNCTIONS
		*/
		template <class Iterator1, class Iterator2>
			bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() == rhs.base(); }

		template <class Iterator1, class Iterator2>
			bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return !(lhs.base() == rhs.base()); }

		template <class Iterator1, class Iterator2>
			bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() > rhs.base(); }

		template <class Iterator1, class Iterator2>
			bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() < rhs.base(); }

		template <class Iterator1, class Iterator2>
			bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() >= rhs.base(); }

		template <class Iterator1, class Iterator2>
			bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() <= rhs.base(); }

		template <class Iter>
			reverse_iterator<Iter>
			operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) { return (it + n); }

		template <class Iterator>
			typename reverse_iterator<Iterator>::difference_type
			operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (rhs.base() - lhs.base()); }
}

#endif
