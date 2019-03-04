
/*#ifndef SIMULATOR_HPP
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
			all_cashiers.enqueue(cashier(std::stoi(file[i+3]), true, i));
		}
	}

	void setupcustomers()
	{
		for (int i = 4+num_cashiers; i<file.size()-1; ++i)
		{
			int num = 0;
			for (num; file[i][num] != ' '; ++num) {}
			int time = num+1;
			for (time; file[i][time] != '\n'; ++time) {}
			time = time-num-1;
			std::string amount = file[i].substr(0,num);
			std::string seconds = file[i].substr(num+1, time);
			int a = std::stoi(amount);
			int s = std::stoi(seconds);
			std::cout<<"amount: "<<amount<<"seconds: "<<seconds<<std::endl;
			for (int j = 1; j <= a; ++j)
			{
				all_customer.enqueue(customer(s));
			}
		}
	}
	int getminutes()
	{
		return minutes;
	}
	int getseconds_run()
	{
		return seconds_run;
	}
	int getmaxlen()
	{
		return maxlen;
	}
	void simulate()
	{
		setupcashiers();
		setupcustomers();
		std::cout<<seconds_run<<" The simulation started."<<std::endl;
		if (S_M) { simulate_M();}
		//else {simulate_S();}
		std::cout<<seconds_run<<" The simulation ended."<<std::endl;
	}*/

	/*void sortcashiers()
	{
		std::sort(all_cashiers.begin(), all_cashiers.end());
	}*/
	/*int findshortest(Queue<cashier> all_cashiers, Queue<cashier>::ConstIterator cashier_iterator)
	{
		int min = 999;
		for (int reg = 0; reg < all_cashiers.size(); ++reg)
		{
			if (cashier_iterator.value().queuesize() < min)
			{
				min = cashier_iterator.value().queuesize();
			}
			cashier_iterator.moveToNext();
		}

		for (int i = 0; i < all_cashiers.size(); ++i)
		{
			cashier_iterator.moveToPrevious();
		}
		return min;
	}

	void shortestiterator(int min, Queue<cashier> all_cashiers, Queue<cashier>::ConstIterator cashier_iterator)
	{
		for (int m = 0; m < all_cashiers.size(); ++m)
		{
			if (cashier_iterator.value().queuesize() > min)
			{
				cashier_iterator.moveToNext();
			}
		}
	}

	void simulate_M()
	{
		for (seconds_run; seconds_run < minutes*60; ++seconds_run)
		{
			Queue<cashier>::ConstIterator cashier_iterator = all_cashiers.constIterator();
			Queue<customer>::ConstIterator customer_iterator = all_customer.constIterator();
			for (int cus = 0; cus < all_customer.size(); ++cus)
			{
				if (customer_iterator.value().get_arrive_seconds() == seconds_run)
				{
					int min = findshortest(all_cashiers, cashier_iterator);
					shortestiterator(min, all_cashiers, cashier_iterator);
					if (cashier_iterator.value().queuesize() >= maxlen)
					{
						customer_iterator.value().make_it_lost();
						num_lost += 1;
						std::cout<<seconds_run<<" lost"<<std::endl;
					}
					else
					{
						cashier_iterator.value().Enterqueue(customer_iterator.value());
						std::cout<<seconds_run<<" Entered line "<<cashier_iterator.value().get_index()
							<<" length "<<cashier_iterator.value().queuesize()<<std::endl;
						num_enterline += 1;
					}
				}
				customer_iterator.moveToNext();
			}

			for (int cas = 0; cas < all_cashiers.size(); ++cas)
			{
				if (cashier_iterator.value().get_availability())
				{
					if (cashier_iterator.value().queuesize() > 0)
					{
						int wait = cashier_iterator.value().getfront().getWaitTime(seconds_run);
						std::cout<<seconds_run<<" exited line "<<cashier_iterator.value().get_index()<<" length "
							<<cashier_iterator.value().queuesize()-1<<" wait time "<<wait<<std::endl;
						std::cout<<seconds_run<<" entered register "<<cashier_iterator.value().get_index()<<std::endl;
						total_wait_seconds += wait;
						cashier_iterator.value().Exitqueue();
						num_exitline += 1;
						cashier_iterator.value().mark_start(seconds_run);
					}
				}
				else
				{
					if (seconds_run == cashier_iterator.value().get_start_seconds()+cashier_iterator.value().get_process_seconds())
					{
						cashier_iterator.value().mark_end();
						num_exitcashier += 1;
						if (cashier_iterator.value().queuesize() > 0)
						{
							int wait = cashier_iterator.value().getfront().getWaitTime(seconds_run);
							std::cout<<seconds_run<<" exited register "<<cashier_iterator.value().get_index()<<std::endl;
							std::cout<<seconds_run<<" exited line "<<cashier_iterator.value().get_index()<<" length "
								<<cashier_iterator.value().queuesize()-1<<" wait time "<<wait<<std::endl;
							std::cout<<seconds_run<<" entered register "<<cashier_iterator.value().get_index()<<std::endl;
							total_wait_seconds += wait;
							cashier_iterator.value().Exitqueue();
							num_exitline += 1;
							cashier_iterator.value().mark_start(seconds_run);
						}
					}
				}
				cashier_iterator.moveToNext();
			}
		}
	}*/

	/*int getshortestindex(std::vector<cashier> all_cashiers)
	{
		std::cout<<"getting index"<<std::endl;
		int min = 999;
		std::cout<<min<<std::endl;
		for (int i = 0; i < all_cashiers.size(); ++i)
		{
			std::cout<<min<<std::endl;
			if (all_cashiers[i].queuesize()<min)
			{
				min = all_cashiers[i].queuesize();
			}
		}
		for (int j = 0; j < all_cashiers.size(); ++j)
		{
			if (all_cashiers[j].queuesize() == min)
			{
				return all_cashiers[j].get_index();
			}
		}
		//return min;
	}*/

	/*void simulate_M()
	{
		for (seconds_run; seconds_run < minutes*60; ++seconds_run)
		{
			for (int i = 0; i < all_customer.size(); ++i)
			{
				if (seconds_run == all_customer[i].get_arrive_seconds())
				{
					std::cout << "Before:" << all_cashiers.size() << std::endl;
					sortcashiers();
					
					std::cout << "After:" << all_cashiers.size() << std::endl;
					if (all_cashiers[0].queuesize() >= maxlen)
					{
						
						all_customer[i].make_it_lost();
						num_lost += 1;
						std::cout<<seconds_run<<" lost"<<std::endl;

					}
					else
					{
						all_cashiers[0].Enterqueue(all_customer[i]);
						std::cout<<seconds_run<<" Entered line "<<all_cashiers[0].get_index()
							<<" length "<<all_cashiers[0].queuesize()<<std::endl;
						num_enterline += 1;
						
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
						std::cout<<seconds_run<<" exited line "<<all_cashiers[j].get_index()<<" length "
							<<all_cashiers[j].queuesize()-1<<" wait time "<<wait<<std::endl;
						std::cout<<seconds_run<<" entered register "<<all_cashiers[j].get_index()<<std::endl;
						total_wait_seconds += wait;
						all_cashiers[j].Exitqueue();
						num_exitline += 1;
						all_cashiers[j].mark_start(seconds_run);
					}
				}
				else
				{
					if (seconds_run == all_cashiers[j].get_start_seconds()+all_cashiers[j].get_process_seconds())
					{
						all_cashiers[j].mark_end();
						num_exitcashier += 1;
						if (all_cashiers[j].queuesize() > 0)
						{
							int wait = all_cashiers[j].getfront().getWaitTime(seconds_run);
							std::cout<<seconds_run<<" exited register "<<all_cashiers[j].get_index()<<std::endl;
							std::cout<<seconds_run<<" exited line "<<all_cashiers[j].get_index()<<" length "
								<<all_cashiers[j].queuesize()-1<<" wait time "<<wait<<std::endl;
							std::cout<<seconds_run<<" entered register "<<all_cashiers[j].get_index()<<std::endl;
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
		for (seconds_run; seconds_run <= minutes*60; ++seconds_run)
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
						std::cout<<" entered line; length "<<OneLine.size()<<std::endl;
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
						std::cout<<seconds_run<<" entered register "<<all_cashiers[j].get_index()<<std::endl;
					}
				}
				else
				{
					if (seconds_run == all_cashiers[j].get_start_seconds()+all_cashiers[j].get_process_seconds())
					{
						all_cashiers[j].mark_end();
						std::cout<<seconds_run<<" exited register "<<all_cashiers[j].get_index()<<std::endl;
						num_exitcashier += 1;
						if (OneLine.isEmpty() == false)
						{
							customer first = OneLine.front();
							int wait = first.getWaitTime(seconds_run);
							total_wait_seconds += wait;
							OneLine.dequeue();
							std::cout<<seconds_run<<" exited line; length "<<OneLine.size()<<" wait time "<<wait<<std::endl;
							std::cout<<seconds_run<<" entered register "<<all_cashiers[j].get_index()<<std::endl;
							num_exitline += 1;
							all_cashiers[j].mark_start(seconds_run);
						}
					}
				}
			}
		} 
	}*/
	/*int getnum_enterline()
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
			if (cashier_iterator.value().get_availability() == false)
			{
				left+=1;
			}
		}
		return left;
	}
private:
	int num_enterline;
	int num_exitline;
	int num_exitcashier;
	int num_lost;
	int minutes;
	int seconds_run = 0;
	int num_cashiers;
	int maxlen;
	int total_wait_seconds;
	std::vector<std::string> file;
	bool S_M;
	Queue<cashier> all_cashiers;
	Queue<customer> all_customer;
};

#endif
*/