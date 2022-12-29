/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:31:46 by rsung             #+#    #+#             */
/*   Updated: 2022/12/29 12:37:07 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

#define COLOR "\033[4;32m"
#define ENDCOLOR "\033[0m"

template<typename T>
void	print_arr(std::vector<T> vector, int mode)
{
	if (mode == 0)
	{
		for(typename std::vector<T>::iterator	i = vector.begin(); i != vector.end(); i++)
			std::cout << *i << " ";
		std::cout << "vector size is: " << vector.size() << std::endl;
	}
	else
	{
		for(typename std::vector<T>::reverse_iterator	i = vector.rbegin(); i != vector.rend(); i++)
			std::cout << *i << " ";
		std::cout << "vector size is: " << vector.size() << std::endl;
	}
}

int main(void)
{
	std::vector<int>	empty_vector;
	std::vector<int>	default_vector;
	std::vector<int>	sv_vector(12, 42);
	std::vector<int>	range_vector(sv_vector.begin(), sv_vector.begin() + 4);

	std::cout << COLOR << "CONSTRUCTORS TESTS" ENDCOLOR << std::endl;
	print_arr(default_vector, 0);
	print_arr(sv_vector, 0);
	print_arr(range_vector, 0);
	default_vector = sv_vector;
	print_arr(default_vector, 0);
	std::vector<int> copy_vector(range_vector);
	print_arr(copy_vector, 0);

	/*clear and replace by arguments*/
	std::cout << COLOR << "ASSIGN FUNCTION TESTS" ENDCOLOR << std::endl;
	sv_vector.assign(range_vector.begin(), range_vector.end());
	print_arr(sv_vector, 0);
	sv_vector.assign(9, 21);
	print_arr(sv_vector, 0);
	/*std::cout << COLOR << "GET ALLOCATOR TEST" ENDCOLOR << std::endl;
	std::cout << sizeof(sv_vector.get_allocator()) << std::endl;*/

	std::cout << COLOR << "ELEMENT ACCESS TESTS" ENDCOLOR << std::endl;
	sv_vector.at(3) = 19;
	print_arr(sv_vector, 0);
	print_arr(sv_vector, 1);
	std::cout << sv_vector.front() << " " << sv_vector.back() << std::endl;

	std::cout << COLOR << "CAPACITY TESTS" << ENDCOLOR << std::endl;
	if (empty_vector.empty())
		std::cout << "empty_ector is empty" << std::endl;
	if (!(sv_vector.empty()))
		std::cout << "sv_vector is not empty" << std::endl;
	std::cout << sv_vector.max_size() << std::endl;
	std::cout << sv_vector.capacity() << std::endl;
	sv_vector.reserve(20);
	std::cout << "after reserve() capacity is now: "<<sv_vector.capacity() << std::endl;

	std::cout << COLOR << "MODIFIERS TESTS" << ENDCOLOR << std::endl;
	range_vector.clear();
	if (range_vector.empty())
		std::cout << "after clear() "<< "range_vector is now empty" << std::endl;
	sv_vector.insert(sv_vector.end(), 66);
	print_arr(sv_vector, 0);
	sv_vector.insert(sv_vector.begin() + 5, 2, 95);
	print_arr(sv_vector, 0);
	default_vector.insert(default_vector.begin(), sv_vector.begin(), sv_vector.end());
	print_arr(default_vector, 0);
	default_vector.erase(default_vector.end() - 1);
	print_arr(default_vector, 0);
	default_vector.erase(default_vector.begin(), default_vector.end());
	print_arr(default_vector, 0);
	default_vector.push_back(5);
	default_vector.push_back(4);
	default_vector.push_back(3);
	default_vector.push_back(2);
	default_vector.push_back(1);
	print_arr(default_vector, 0);
	default_vector.pop_back();
	default_vector.pop_back();
	print_arr(default_vector, 0);
	default_vector.resize(10, 1);
	print_arr(default_vector, 0);
	default_vector.resize(3, 3721987);
	print_arr(default_vector, 0);
	default_vector.swap(sv_vector);
	std::cout << "default_vector is now: ";
	print_arr(default_vector, 0);
	std::cout << "sv_vector is now: ";
	print_arr(sv_vector, 0);
}
