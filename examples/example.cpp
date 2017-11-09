#include "stack.hpp"
#include <string>
#include <chrono>
#include <thread>

void producer(stack<int> &Stack)
{
	for (;;)
	{
		Stack.push(std::rand() % 100);
		std::this_thread::sleep_for(std::chrono::seconds(std::rand() % (3) + 1));
	}
}

void consumer(stack<int> &Stack)
{
	for (;;)
	{
		try
		{
			Stack.pop();
		}
		catch (std::logic_error)
		{
			std::this_thread::sleep_for(std::chrono::seconds(std::rand() % (3) + 2));
		}
		std::this_thread::sleep_for(std::chrono::seconds(std::rand() % (3) + 2));
	}
}

int main()
{
	srand(time(NULL));
	stack<int> Stack;

	std::thread pr(producer, std::ref(Stack));
	std::thread cn(consumer, std::ref(Stack));

	pr.join();
	cn.join();


	return 0;
}
