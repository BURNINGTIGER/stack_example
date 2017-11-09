#ifndef STACK_HPP 
#define STACK_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <mutex>
#include <utility>
#include <new>
#include <thread>
#include <memory>

template <typename T>

class stack

{

public:

	void swap(stack<T>&);//noexcept;

	stack();//noexcept;

	~stack();//noexcept;

	stack(const stack<T>&);//strong;

	stack<T>& operator=(stack<T> const& other);//strong;

	size_t count() const;//noexcept;

	void push(T const &);//strong;

	std::shared_ptr<T> pop();//strong;
	
	//T top();//strong;

	void printall() const;//strong;

	void print();//noexcept;

private:

	T * array_;

	size_t array_size_;

	size_t count_;
	
	mutable std::mutex mutex_;

};

template <typename T>
void stack<T>::swap(stack<T>& other)
{
	std::lock(mutex_, other.mutex_);
	std::swap(array_, other.array_);
	std::swap(array_size_, other.array_size_);
	std::swap(count_, other.count_);
	mutex_.unlock();
	other.mutex_.unlock();
}

template <typename T>
stack<T>::stack()
{
	array_size_ = 0;
	count_ = 0;
	array_ = nullptr;
}

template <typename T>
stack<T>::~stack()
{
	count_ = 0;
	array_size_ = 0;
	delete[] array_;
}

template<typename T>
stack<T>::stack(const stack<T>& other) 
{
	std::lock_guard<std::mutex> lock(other.mutex_);
	T *tmp = new T[other.array_size_];
	array_size_ = other.array_size_;
	count_ = other.count_;
	array_ = tmp;
	try
	{
		std::copy(other.array_, other.array_ + count_, array_);
	}
	catch(...)
	{
		delete[] array_;
	}
}

template<typename T>
stack<T>& stack<T>::operator=(stack<T> const& other)
{
	if (this != &other) 
	{
		stack(other).swap(*this);
	}
	return *this;
}

template <typename T>
void stack<T>::push(T const & value)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (array_size_ == 0)
	{
		array_size_ = 1;
		array_ = new T[array_size_];
	}
	if (array_size_ == count_)
	{
		array_size_ = array_size_ * 2;
		T * new_array = new T[array_size_]();
		try
		{
		std::copy(array_, array_ + count_, new_array);
		}
		catch(...)
		{
			   delete[] array_;
			   throw;
		}
		delete[] array_;
		array_ = new_array;
	}
	array_[count_] = value;
	++count_;
}

template <typename T>
auto stack<T>::pop() -> std::shared_ptr<T>
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (count_ == 0)
	{
		throw std::logic_error( "Stack is empty!");
	}
	auto top = std::make_shared<T>(array_[count_ - 1]);
	--count_;
	return top;
}

/*template <typename T>
T stack<T>::top()
{
	mutex_.lock();
	if (empty())
	{
		throw std::logic_error( "Stack is empty!");
	}
	return array_[count_ - 1];
	mutex_.unlock();
}*/


template <typename T>
size_t stack<T>::count() const
{
	std::lock_guard<std::mutex> lock(mutex_);
	return count_;
	
}

template<typename T>
void stack<T>::printall() const
{
	std::lock_guard<std::mutex> lock(mutex_);
	for (int i = 0; i < count_; i++)
		std::cout << array_[i];
}

template<typename T>
void stack<T>::print()
{
	std::lock_guard<std::mutex> lock(mutex_);
	std::cout << array_[count_ - 1];
}
#endif
