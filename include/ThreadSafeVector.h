#pragma once

#include "mpi.h"
#include <mutex>
#include <vector>
#include <algorithm>

using namespace std;


/**
 *klasa odpowiadająca za kolejkę
 */
class ThreadSafeVector{
	/**
	 * mut symafor
	 * vec wektor kolejki
	 */
	mutex mut;
	vector<int> vec;
public:

	/**
	 * dodawanie nowego elementu elem
	 */
	void push(int elem);
	/**
	 * wysyłanie do wszsytkich procesów w kolejce timestamp i tag
	 */
	void sendToAllInQueue(int timestamp, int tag);

	/*
	* return size wektora
	*/
	int getSize();
	/*
	* return element wektora elem
	*/
	int getElem(int x);
	/*
	* czyści wektor
	*/
	void clear();
};