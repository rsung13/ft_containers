/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:10:09 by rsung             #+#    #+#             */
/*   Updated: 2022/11/21 22:15:40 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "../include/vector.hpp"

namespace	ft
{
	template<typename T, class Container = ft::vector<T> >
		class	stack
		{
			protected:
				Container	c;

			public:

				/*
				/	MEMBER TYPES
				*/
				typedef	Container								container_type;
				typedef typename Container::value_type			value_type;
				typedef typename Container::size_type			size_type;
				typedef typename Container::reference			reference;
				typedef typename Container::const_reference		const_reference;

				/*
				/	CONSTRUCTOR/DESTRUCTOR
				*/
				explicit	stack(const Container& cont = Container()) {c = cont;}
				~stack() {};
				stack& operator=(const stack& other)
				{
					c = other.c;
					return (*this);
				}

				/*
				/	ELEMENT ACCESS
				*/
				reference	top() {return (c.back());}
				const_reference top() const {return (c.back());}

				/*
				/	CAPACITY
				*/
				bool		empty() const {return (c.empty());}
				size_type	size() const {return (c.size());}

				/*
				/	MODIFIERS
				*/
				void	push(const value_type& value) {c.push_back(value);}
				void	pop(void)
				{
					c.pop_back();
					return ;
				}

				/*
				/	NON-MEMBER FUNCTIONS
				*/
				template<typename Type, class Cont>
					friend bool	operator==(const ft::stack<Type, Cont>& lhs, const ft::stack<Type, Cont>& rhs);

				template<typename Type, class Cont>
					friend bool operator<(const ft::stack<Type, Cont>& lhs, const ft::stack<Type, Cont>& rhs);

		};

		template<typename T, class Container>
			inline bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (lhs.c == rhs.c);}

		template<typename T, class Container>
			inline bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (lhs.c < rhs.c);}

		template<typename T, class Container>
			inline bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (!(lhs == rhs));}

		template<typename T, class Container>
			inline bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (!(rhs < lhs));}

		template<typename T, class Container>
			inline bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (rhs < lhs);}

		template<typename T, class Container>
			inline bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (!(lhs < rhs));}
}

#endif
