/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 10:25:11 by rsung             #+#    #+#             */
/*   Updated: 2022/12/29 16:13:31 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.hpp"
#include "../include/utils.hpp"
#include "../include/map.hpp"
#include "../include/map_iterator.hpp"
#include "../include/stack.hpp"

#define COLOR "\033[4;32m"
#define ENDCOLOR "\033[0m"
#define BLUE "\033[4;34m"
#define ENDBLUE "\033[0m"
#define CYAN "\033[4;36m"
#define ENDCYAN "\033[0m"

template<typename T>
void	print_arr(ft::vector<T> vector, int mode)
{
	if (mode == 0)
	{
		for(typename ft::vector<T>::iterator	i = vector.begin(); i != vector.end(); i++)
			std::cout << *i << " ";
		std::cout << "vector size is: " << vector.size() << std::endl;
	}
	else
	{
		for(typename ft::vector<T>::reverse_iterator	i = vector.rbegin(); i != vector.rend(); i++)
			std::cout << *i << " ";
		std::cout << "vector size is: " << vector.size() << std::endl;
	}
}

template<typename T, typename T1>
void	print_map(ft::map<T, T1>	map)
{
	for(typename ft::map<T, T1>::iterator	i = map.begin(); i != map.end(); i++)
		std::cout << "The key is: " << i->first << " and the value is: " << i->second << std::endl;
	std::cout << "map size is: " << map.size() << std::endl;
}

int main(void)
{
	/*///////////////////.*/
	//	CONTAINER VECTOR
	/*///////////////////.*/
	ft::vector<int> default_vector;
	ft::vector<int>	sv_vector(12, 42);
	ft::vector<int>	range_vector(sv_vector.begin(), sv_vector.begin() + 4);

	std::cout << COLOR << "CONSTRUCTORS TESTS" ENDCOLOR << std::endl;
	print_arr(default_vector, 0);
	print_arr(sv_vector, 0);
	print_arr(range_vector, 0);
	default_vector = sv_vector;
	print_arr(default_vector, 0);
	ft::vector<int> copy_vector(range_vector);
	print_arr(copy_vector, 0);

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
	ft::vector<int>	empty_vector;
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
		std::cout << "after clear() " << "range_vector is now empty" << std::endl;
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
	std::cout << std::endl << std::endl;

	/*///////////////////.*/
	//	CONTAINER STACK
	/*///////////////////.*/
	std::cout << CYAN << "ELEMENTS ACCESS TESTS" << ENDCYAN << std::endl;
	ft::stack<int>	default_stack;
	default_stack.push(3);
	std::cout << default_stack.top() << std::endl;
	default_stack.push(5);
	ft::stack<int>	copy_stack(default_stack);
	std::cout << copy_stack.top() << std::endl;

	std::cout << CYAN << "CAPACITY TESTS" << ENDCYAN << std::endl;
	ft::stack<int>	empty_stack;
	if (empty_stack.empty())
		std::cout << "empty_stack is empty" << std::endl;
	if (!(default_stack.empty()))
		std::cout << "default_stack is not empty" << std::endl;
	std::cout << "The size of default_stack is: " << default_stack.size() << std::endl;

	std::cout << CYAN << "MODIFIERS TESTS" << ENDCYAN << std::endl;
	empty_stack.push(9);
	std::cout << empty_stack.top() << std::endl;
	empty_stack.pop();
	//std::cout << empty_stack.top() << std::endl;
	std::cout << std::endl << std::endl;

	/*///////////////////.*/
	//	CONTAINER MAP
	/*///////////////////.*/
	std::cout << BLUE << "CONSTRUCTORS TESTS" << ENDBLUE << std::endl;
	ft::map<int, char>	default_map;
	default_map.insert(ft::pair<int, char>(3, 'a'));
	default_map.insert(ft::pair<int, char>(7, 'b'));
	default_map.insert(ft::pair<int, char>(32, 'c'));
	default_map.insert(ft::pair<int, char>(1, 'd'));
	default_map.insert(ft::pair<int, char>(5, 'e'));
	default_map.insert(ft::pair<int, char>(19, 'f'));
	default_map.insert(ft::pair<int, char>(66, 'g'));
	default_map.insert(ft::pair<int, char>(42, 'h'));
	ft::map<int, char>	copy_map(default_map);
	print_map(default_map);
	ft::map<int, char>	range_map(default_map.begin(), default_map.end());
	print_map(default_map);

	std::cout << BLUE << "ELEMENT ACCESS TESTS" << ENDBLUE << std::endl;
	std::cout << default_map.at(3) << std::endl;
	try
	{
		std::cout << default_map.at(99) << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		std::cout << e.what();
	}
	std::cout << default_map[35] << std::endl;
	print_map(default_map);
	ft::map<int, char>::iterator it = default_map.find(35);
	it->second = 'z';
	print_map(default_map);

	std::cout << BLUE << "CAPACITY TESTS" << ENDBLUE << std::endl;
	ft::map<int, char>	empty_map;
	if (empty_map.empty())
		std::cout << "empty_map is empty" << std::endl;
	empty_map.insert(ft::pair<int, char>(1, 'o'));
	if (!(empty_map.empty()))
		std::cout << "empty_map is not empty anymore" << std::endl;
	std::cout << default_map.size() << std::endl;
	std::cout << default_map.max_size() << std::endl;

	std::cout << BLUE << "MODIFIERS TESTS" << ENDBLUE << std::endl;
	empty_map.clear();
	if (empty_map.empty())
		std::cout << "after clear() empty_map is empty again" << std::endl;
	copy_map.erase(copy_map.begin());
	print_map(copy_map);
	copy_map.erase(19);
	print_map(copy_map);
	copy_map.erase(copy_map.begin(), copy_map.end());
	print_map(copy_map);
	empty_map.insert(ft::pair<int, char>(1, 'y'));
	empty_map.insert(ft::pair<int, char>(5, 't'));
	empty_map.insert(ft::pair<int, char>(6, 'w'));
	default_map.swap(empty_map);
	std::cout << "THIS IS EMPTY_MAP NOW after swap: " << std::endl;
	print_map(empty_map);
	std::cout << "THIS IS DEFAULT_MAP NOW after swap: " << std::endl;
	print_map(default_map);
}
