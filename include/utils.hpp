/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:34:08 by rsung             #+#    #+#             */
/*   Updated: 2022/12/16 12:41:33 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

//#include <type_traits>

namespace	ft
{
	/*
	/	ENABLE_IF
	*/
	template <bool Cond, typename T = void>
	struct	enable_if {};

	template <typename T>
	struct	enable_if<true, T> {typedef T	type;};

	/*
	/	IS_INTEGRAL
	*/
	template <bool is_integral, typename T>
	struct is_integral_res
	{
		typedef T type;
		static const bool value = is_integral;
	};
	template <typename>
		struct	is_integral_type : public is_integral_res<false, bool> {};
	template <>
		struct is_integral_type<bool> : public is_integral_res<true, bool> {};
	template <>
		struct is_integral_type<char> : public is_integral_res<true, char> {};
	template <>
		struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
	template <>
		struct is_integral_type<short int> : public is_integral_res<true, short int> {};
	template <>
		struct is_integral_type<int> : public is_integral_res<true, int> {};
	template <>
		struct is_integral_type<long int> : public is_integral_res<true, long int> {};
	template <>
		struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
	template <>
		struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
	template <>
		struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
	template <>
		struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
	template <>
		struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
	template <>
		struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};
	template <typename T>
		struct is_integral : public is_integral_type<T> {};

	/*
	/	LEXICOGRAPHICAL_COMPARE
	*/
	template <typename InputIterator1, typename InputIterator2>
		bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return false;
				else if (*first1 < *first2)
					return true;
				first1++;
				first2++;
			}
			return (first2 != last2);
		}

	template <typename InputIterator1, typename InputIterator2, typename Compare>
		bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
		{
			for(; (first1 != last1) & (first2 != last2); first1++, (void)first2++)
			{
				if (comp(*first1, *first2))
					return true;
				if (comp(*first2, *first1))
					return false;
			}
			return (first1 == last1) && (first2 != last2);
		}

	/*
	/	PAIR/MAKE_PAIR
	*/
	template <class T1, class T2>
		struct	pair
		{
			typedef	T1	first_type;
			typedef T2	second_type;
			first_type	first;
			second_type	second;

			/*
			/	MEMBER FUNCTIONS
			*/
			pair() : first(), second() {}
			pair(const pair& p) : first(p.first), second(p.second) {}
			pair(const first_type& x, const second_type& y) : first(x), second(y) {}
			template <class U1, class U2>
				pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
			pair& operator=(const pair& other)
			{
				if (this != &other)
				{
					first = other.first;
					second = other.second;
				}
				return (*this);
			}
		};

	template <class T1, class T2>
		ft::pair<T1, T2> make_pair(T1 t, T2 u) {return (pair<T1, T2>(t, u));}

	template <class T1, class T2>
		bool	operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (lhs.first == rhs.first && lhs.second == rhs.second);}

	template <class T1, class T2>
		bool	operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (!(lhs == rhs));}

	template <class T1, class T2>
		bool	operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));}

	template <class T1, class T2>
		bool	operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (rhs < lhs);}

	template <class T1, class T2>
		bool	operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (!(rhs < lhs));}

	template <class T1, class T2>
		bool	operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {return (!(lhs < rhs));}

	/*
	/	BINARY FUNCTION
	*/
	template <typename Arg1, typename Arg2, typename Res>
	struct binary_function
	{
		typedef Arg1		first_argType;
		typedef Arg2		second_argType;
		typedef Res			result_type;
	};
}

#endif
