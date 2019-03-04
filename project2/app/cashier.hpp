#ifndef CASHIER_HPP
#define CASHIER_HPP
#include <vector>
#include "Queue.hpp" 
#include "customer.hpp"
#include <iostream>


class cashier
{
public:
	cashier(int p_t, bool ava, int newindex)
		:process_seconds(p_t), availability(ava), index(newindex)
	{
	}
	int get_process_seconds() const
	{
		return process_seconds;
	}
	int get_start_seconds() const
	{
		return start_seconds;
	}
	bool get_availability() const
	{
		return availability;
	}
	void mark_start(int current_seconds)
	{
		start_seconds = current_seconds;
		availability = false;
	}
	void mark_end() 
	{
			availability = true;
	}
	int queuesize() const
	{
		return own_queue.size();
	}
	void Enterqueue(customer c)
	{
		own_queue.enqueue(c);
	}
	void Exitqueue()
	{
		own_queue.dequeue();
	}
	customer getfront() const
	{
		return own_queue.front();
	}
	int getindex() const
	{
		return index;
	}
private:
	int process_seconds;
	int start_seconds;
	Queue<customer> own_queue;
	bool availability;
	int index;
};

#endif