// main.cpp
//
// ICS 46 Spring 2018
// Project #2: Time Waits for No One
//
// This is the entry point for your simulation application.
//
// All of the code that makes up your simulation -- which is everything
// except for your DoublyLinkedList and Queue implementations -- should
// be in the "app" directory, though, naturally, it shouldn't all be in
// this file.  A design that keeps separate things separate is always
// part of the requirements.
#include <vector>
#include <iostream>
#include "Queue.hpp"
#include "cashier.hpp"
#include "customer.hpp"
#include "simulator.hpp"


std::vector<std::string> readfile()
{
	std::vector<std::string> file;
	std::string input;
	while (getline(std::cin, input))
	{
		file.push_back(input);
		//std::cout<<input<<std::endl;
	}
	return file;
}

int main()
{
	std::vector<std::string> file_input = readfile();
	simulator main_simulator{file_input};

	main_simulator.simulate();

	std::cout<<"STATS"<<std::endl;
	std::cout<<"Entered Line    : "<<main_simulator.getnum_enterline()<<std::endl;
	std::cout<<"Exited Line     : "<<main_simulator.getnum_exitline()<<std::endl;
	std::cout<<"Exited Register : "<<main_simulator.getnum_exitcashier()<<std::endl;
	float ave_wait = (float)main_simulator.gettotal_wait_seconds()/main_simulator.getnum_exitline();
	std::cout<<"Avg Wait Time   : ";
	printf("%.2f", ave_wait);
	std::cout<<std::endl;
	std::cout<<"Left In Line    : "<<main_simulator.getnum_enterline()-main_simulator.getnum_exitline()<<std::endl;
	std::cout<<"Left In Register: "<<main_simulator.left_in_cashier()<<std::endl;
	std::cout<<"Lost            : "<<main_simulator.getnum_lost()<<std::endl;

    return 0;
}
