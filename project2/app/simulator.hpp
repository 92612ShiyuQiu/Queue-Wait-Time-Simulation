#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include "cashier.hpp"
#include "customer.hpp"
#include <vector>
#include <string>
#include <iostream>

class simulator
{
public:
	simulator(std::vector<std::string> newfile)
		:file(newfile)
	{
		minutes = std::stoi(file[0]);
		num_cashiers = std::stoi(file[1]);
		maxlen = std::stoi(file[2]);
		if (file[3] == "M") {S_M = true;}
		if (file[3] == "S") {S_M = false;}

	}

	
	void setupcashiers()
	{
		for (int i = 1; i<=num_cashiers; ++i)
		{
			all_cashiers.push_back(cashier(std::stoi(file[i+3]), true, i));
		}
	}

	void setupcustomers()
	{
		for (int i = 4+num_cashiers; i<file.size()-1; ++i)
		{
			int amount = std::stoi(file[i].substr(0,file[i].find(" ")));
			int seconds = std::stoi(file[i].substr(file[i].find(" ")+1, file[i].find("\n")));
			//std::cout<<amount<<" "<<seconds<<std::endl;
			for (int j = 1; j <= amount; ++j)
			{
				all_customer.push_back(customer(seconds));
			}
		}
	}

	void simulate()
	{
		setupcashiers();
		setupcustomers();
		std::cout<<"LOG"<<std::endl;
		std::cout<<seconds_run<<" start"<<std::endl;
		if (S_M) { simulate_M();}
		else {simulate_S();}
		std::cout<<seconds_run<<" end"<<std::endl;
		std::cout<<std::endl;
	}

	int findshortestindex()
	{
		int minIndex = 0;

		for (int i = 0; i < all_cashiers.size(); i++)
		{
			if (all_cashiers[i].queuesize() < all_cashiers[minIndex].queuesize())
			{
				minIndex = i;
			}
		}

		return minIndex;
	}


	void simulate_M()
	{
		for (seconds_run; seconds_run < minutes*60; ++seconds_run)
		{
			for (int i = 0; i < all_customer.size(); ++i)
			{
				if (seconds_run == all_customer[i].get_arrive_seconds())
				{
					int shortest = findshortestindex();
					if (all_cashiers[shortest].queuesize() >= maxlen)
					{
						all_customer[i].make_it_lost();
						num_lost += 1;
						std::cout<<seconds_run<<" lost"<<std::endl;

					}
					else
					{
						//std::cout<<shortest<<std::endl;
						all_cashiers[shortest].Enterqueue(all_customer[i]);
						num_enterline += 1;
						std::cout<<seconds_run<<" Entered line "<<all_cashiers[shortest].getindex()
							<<" length "<<all_cashiers[shortest].queuesize()<<std::endl;
						//num_enterline += 1;
						
					}
				}
			}

			for (int j = 0; j < all_cashiers.size(); ++j)
			{
				if (all_cashiers[j].get_availability())
				{
					if (all_cashiers[j].queuesize() > 0)
					{
						int wait = all_cashiers[j].getfront().getWaitTime(seconds_run);
						std::cout<<seconds_run<<" exited line "<<all_cashiers[j].getindex()<<" length "
							<<all_cashiers[j].queuesize()-1<<" wait time "<<wait<<std::endl;
						std::cout<<seconds_run<<" entered register "<<all_cashiers[j].getindex()<<std::endl;
						total_wait_seconds += wait;
						all_cashiers[j].Exitqueue();
						num_exitline += 1;
						all_cashiers[j].mark_start(seconds_run);
					}
				}
				else
				{
					//std::cout<<"checkinig to exit: "<<j<<std::endl;
					if (seconds_run == all_cashiers[j].get_start_seconds()+all_cashiers[j].get_process_seconds())
					{
						all_cashiers[j].mark_end();
						num_exitcashier += 1;
						if (all_cashiers[j].queuesize() > 0)
						{
							//std::cout<<all_cashiers.size()<<" "<<j<<" "<<all_cashiers[j].queuesize()<<std::endl;	
							//std::cout<<"the front of the queue is: "<<all_cashiers[j].getfront().get_arrive_seconds()<<std::endl;
							int wait = all_cashiers[j].getfront().getWaitTime(seconds_run);
							std::cout<<seconds_run<<" exited register "<<all_cashiers[j].getindex()<<std::endl;
							std::cout<<seconds_run<<" exited line "<<all_cashiers[j].getindex()<<" length "
								<<all_cashiers[j].queuesize()-1<<" wait time "<<wait<<std::endl;
							std::cout<<seconds_run<<" entered register "<<all_cashiers[j].getindex()<<std::endl;
							total_wait_seconds += wait;
							all_cashiers[j].Exitqueue();
							num_exitline += 1;
							all_cashiers[j].mark_start(seconds_run);
						}
					}
				}
			
			}
		}
	}
	void simulate_S()
	{
		Queue<customer> OneLine;
		for (seconds_run; seconds_run < minutes*60; ++seconds_run)
		{
			for (int i = 0; i < all_customer.size(); ++i)
			{

				if (seconds_run == all_customer[i].get_arrive_seconds())
				{
					if (OneLine.size() >= maxlen) 
					{
						all_customer[i].make_it_lost();
						num_lost+=1;
						std::cout<<seconds_run<<" lost"<<std::endl;
					}
					else
					{
						OneLine.enqueue(all_customer[i]);
						num_enterline += 1;
						std::cout<<seconds_run<<" entered line; length "<<OneLine.size()<<std::endl;
					}
				}
			}

			for (int j = 0; j < all_cashiers.size(); ++j)
			{
				if (all_cashiers[j].get_availability())
				{
					if (OneLine.isEmpty() == false)
					{
						customer first = OneLine.front();
						int wait = first.getWaitTime(seconds_run);
						total_wait_seconds += wait;
						OneLine.dequeue();
						num_exitline += 1;
						all_cashiers[j].mark_start(seconds_run);
						std::cout<<seconds_run<<" exited line; length "<<OneLine.size()<<" wait time "<<wait<<std::endl;
						std::cout<<seconds_run<<" entered register "<<all_cashiers[j].getindex()<<std::endl;
					}
				}
				else
				{
					if (seconds_run == all_cashiers[j].get_start_seconds()+all_cashiers[j].get_process_seconds())
					{
						all_cashiers[j].mark_end();
						std::cout<<seconds_run<<" exited register "<<all_cashiers[j].getindex()<<std::endl;
						num_exitcashier += 1;
						if (OneLine.isEmpty() == false)
						{
							customer first = OneLine.front();
							int wait = first.getWaitTime(seconds_run);
							total_wait_seconds += wait;
							OneLine.dequeue();
							std::cout<<seconds_run<<" exited line; length "<<OneLine.size()<<" wait time "<<wait<<std::endl;
							std::cout<<seconds_run<<" entered register "<<all_cashiers[j].getindex()<<std::endl;
							num_exitline += 1;
							all_cashiers[j].mark_start(seconds_run);
						}
					}
				}
			}
		} 
	}
	int getnum_enterline()
	{
		return num_enterline;
	}
	int getnum_exitline()
	{
		return num_exitline;
	}
	int getnum_lost()
	{
		return num_lost;
	}
	int getnum_exitcashier()
	{
		return num_exitcashier;
	}
	int gettotal_wait_seconds()
	{
		return total_wait_seconds;
	}
	int left_in_cashier()
	{
		int left = 0;
		for (int c = 0; c < all_cashiers.size(); ++c)
		{
			if (all_cashiers[c].get_availability() == false)
			{
				left+=1;
			}
		}
		return left;
	}
private:
	int num_enterline = 0;
	int num_exitline = 0;
	int num_exitcashier = 0;
	int num_lost = 0;
	int minutes;
	int seconds_run = 0;
	int num_cashiers;
	int maxlen;
	float total_wait_seconds = 0.00;
	std::vector<std::string> file;
	bool S_M;
	std::vector<cashier> all_cashiers;
	std::vector<customer> all_customer;
};

#endif
