#pragma once

#include <mutex>
#include <vector>
template <class T>
class ThreadSafeVector{

	std::mutex mut;
	std::vector<T> vec;
public:
	void push(T elem);

};

template <class T>
void ThreadSafeVector<T>::push(T elem){

	mut.lock();
	vec.push_back(elem);
	mut.unlock();

}