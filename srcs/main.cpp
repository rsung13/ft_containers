/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:54:27 by rsung             #+#    #+#             */
/*   Updated: 2022/12/23 14:54:14 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.hpp"
#include "../include/utils.hpp"
#include "../include/map.hpp"
#include "../include/map_iterator.hpp"
#include <vector>
#include <sstream>

int main(void)
{
	ft::vector<int>	a(6, 1);
	std::vector<int> true_a(6, 1);
	ft::vector<int> c(a.begin(), a.end());
	std::vector<int> true_c(true_a.begin(), true_a.end());
	ft::vector<int>	e(7, 3);
	std::vector<int> true_e(7, 3);

	if (!(a.empty() && !(true_a.empty())))
	{
		std::cout << "CONSTRUCTOR TESTS: " << std::endl;
		std::cout << "my Vector: " << a.max_size() <<std::endl;
		for(ft::vector<int>::iterator	i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl;
		std::cout << "og Vector: " << true_a.max_size() << std::endl;
		for(std::vector<int>::iterator i = true_c.begin(); i != true_c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;


		/*c.push_back(9);
		true_c.push_back(9);
		std::cout << "This is front: " << c.front() << " and this is back after push_back(9): " << c.back() << std::endl;
		std::cout << "This is front: " << true_c.front() << " and this is back after push_back(9): " << true_c.back() << std::endl;
		c.pop_back();
		true_c.pop_back();
		for(ft::vector<int>::iterator	i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl;
		for(std::vector<int>::iterator i = true_c.begin(); i != true_c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;




		c.push_back(91);
		std::cout << "Testing function at(): " << c.at(6) << std::endl;
		c.pop_back();

		std::cout << "TRUE C CAPACITY = " << true_c.capacity() << std::endl;
		std::cout << "MY C CAPACiTY = " << c.capacity() << std::endl;

		true_c.insert(true_c.begin()+2, 99);
		for(std::vector<int>::iterator i = true_c.begin(); i != true_c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;

		c.insert(c.begin()+2, 99);
		for(ft::vector<int>::iterator i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;



		true_c.insert(true_c.begin()+4, true_e.begin(), true_e.end());
		for(std::vector<int>::iterator i = true_c.begin(); i != true_c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;

		c.insert(c.begin()+4, e.begin(), e.end());
		for(ft::vector<int>::iterator i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;

		true_c.insert(true_c.begin()+4, 3, 19);
		for(std::vector<int>::iterator i = true_c.begin(); i != true_c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;

		c.insert(c.begin()+4, 3, 19);
		for(ft::vector<int>::iterator i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;*/

		c.push_back(42);
		c.push_back(21);
		true_c.push_back(42);
		true_c.push_back(21);

		for(std::vector<int>::iterator i = true_c.begin(); i != true_c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl;
		for(ft::vector<int>::iterator i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;

		//std::cout << *c.erase(c.end() - 3) << std::endl;
		//std::cout << *true_c.erase(true_c.end()) << std::endl;

		/*for(std::vector<int>::iterator i = true_c.begin(); i != true_c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;*/
		//std::cout << "THIS TRUEEEE IS SIZE: " << true_c.size() << std::endl;
		/*for(ft::vector<int>::iterator i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;*/
		//std::cout << "THIS IS SIZE: " << c.size() << std::endl;

		std::cout << "THE TRUE POINTER IS: " <<*true_c.erase(true_c.begin() + 1, true_c.end() - 2) << std::endl;
		std::cout << "MY POINTER IS: " << *c.erase(c.begin() + 1, c.end() - 2) << std::endl;

		for(std::vector<int>::iterator i = true_c.begin(); i != true_c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl;
		for(ft::vector<int>::iterator i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;

		//std::cout << "THIS TRUEEEE IS SIZE: " << true_c.size() << std::endl;
		/*for(ft::vector<int>::iterator i = c.begin(); i != c.end(); i++)
			std::cout << *i << "| ";*/
		//std::cout << std::endl << std::endl;
		//std::cout << "THIS IS SIZE: " << c.size() << std::endl;
		//std::cout << "Testing real function at(): " << true_c.at(55) << std::endl;
		/*c.clear();
		true_c.clear();
		if (c.empty() && true_c.empty())
			std::cout << "function clear() is working" << std::endl;*/

		// This test checks if vector works with iterators tagged as std::input_iterator_tag
        ft::vector<char> v;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        v.assign(it, end);
		for(ft::vector<char>::iterator i = v.begin(); i != v.end(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;

		std::vector<char> v1;

        std::istringstream str2("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it1(str2), end1;
        v1.assign(it1, end1);
		for(std::vector<char>::iterator i1 = v1.begin(); i1 != v1.end(); i1++)
			std::cout << *i1 << "| ";
		std::cout << std::endl << std::endl;



		ft::vector<int>	z;
		for (int u = 1; u < 10; u++)
			z.push_back(u);
		ft::vector<int>::iterator iit = z.begin() + 1;
		//ft::vector<int>::iterator iiit = z.end() - 1;

		std::vector<int>	z1;
		for (int u1 = 1; u1 < 10; u1++)
			z1.push_back(u1);
		std::vector<int>::iterator iit1 = z1.begin() + 1;
		//std::vector<int>::iterator iiit1 = z1.end() - 1;*/
	

		if (iit < iit)
			std::cout << "HELLO THERE FROM FT::" << std::endl;
		else
			std::cout << "GOODBYE THERE FROM FT::" << std::endl;

		if (iit1 < iit1)
			std::cout << "HELLO THERE FROM STD::" << std::endl;
		else
			std::cout << "GOODBYE THERE FROM STD::" << std::endl;

		for(ft::vector<int>::reverse_iterator i = z.rbegin(); i != z.rend(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;

		for(std::vector<int>::reverse_iterator i = z1.rbegin(); i != z1.rend(); i++)
			std::cout << *i << "| ";
		std::cout << std::endl << std::endl;


		std::cout << "CONTAINER MAP" << std::endl;

		ft::map<int, char>	myMap;
		/*myMap.insert(ft::pair<int, char>(50, 'A'));
		myMap.insert(ft::pair<int, char>(60, 'B'));
		myMap.insert(ft::pair<int, char>(55, 'C'));
		myMap.insert(ft::pair<int, char>(12, 'D'));
		myMap.insert(ft::pair<int, char>(45, 'E'));
		myMap.insert(ft::pair<int, char>(99, 'F'));
		myMap.insert(ft::pair<int, char>(1, 'G'));
		myMap.insert(ft::pair<int, char>(46, 'H'));

		myMap.erase(myMap.begin());
		myMap.erase(60);*/
		myMap.insert(ft::pair<int, char>(1, 'B'));
		myMap.insert(ft::pair<int, char>(2, 'C'));
		myMap.insert(ft::pair<int, char>(3, 'D'));
		myMap.insert(ft::pair<int, char>(4, 'E'));
		myMap.insert(ft::pair<int, char>(5, 'F'));
		myMap.insert(ft::pair<int, char>(6, 'G'));
		myMap.insert(ft::pair<int, char>(7, 'G'));
		myMap.insert(ft::pair<int, char>(8, 'G'));

		myMap.erase(2);
		myMap.erase(3);
		ft::map<int, char>::iterator	tempo;
		tempo = myMap.find(5);
		myMap.erase(tempo, myMap.end());
		ft::map<int, char>::Node* tmpor;
		std::cout << std::endl << std::endl;
		for (ft::map<int, char>::iterator iter = myMap.begin(); iter != myMap.end(); iter++)
		{
			tmpor = iter.getNode();
					std::cout << "MYSELF: " <<(*iter).first << std::endl;
					if (tmpor->parent != NULL)
						std::cout << "PARENT: " << tmpor->parent->_pair.first << std::endl;
					if (tmpor->left != NULL)
						std::cout << "LEFT: " << tmpor->left->_pair.first << std::endl;
					if (tmpor->right != NULL)
						std::cout << "RIGHT: " << tmpor->right->_pair.first << std::endl;

		}
	}
	
}
