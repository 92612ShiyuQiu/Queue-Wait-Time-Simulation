#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include "Queue.hpp"
#include <vector>
#include <iostream>
//#include "cashier.hpp"

class customer
{
public:
	customer(int arr_sec)
		: arrive_seconds(arr_sec)
	{
	}
	int get_arrive_seconds() const
	{
		return arrive_seconds;
	}
	void make_it_lost()
	{
		lost = true;
	}
	bool whether_lost() const
	{
		return lost;
	}
	int getWaitTime(int current_seconds) const
	{
		return current_seconds - arrive_seconds;
	}
private:
	bool lost = false;
	int arrive_seconds;
};

#endif