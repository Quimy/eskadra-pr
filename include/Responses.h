#pragma once
#include <vector>
#include <algorithm>

#include <iostream>
#include "constants.h"
using namespace std;

/**
 * Klasa obsługująca odpowiedzi od procesów
 */
class Responses{
	/**
	 * tablica przechuwująca odpowiedzi dla każdego procesu
	 */
	vector<int> responses;
	/*
	* tag procesu
	*/
	int tag;
	/*
	* numer procesu
	*/
	int number;
public:

	Responses(int n): number{n}, responses(n,-1){};

	/**
	 * dodawanie odpowiedzi
	 * where indeks w tablicy
	 * what rodzaj dostawanej odpowiedzi
	 */
	void add(int where,int what);

	/**
	 * zwraca liczba tagów t w tablicy responses
	 */
	int getNumberOfTag(int t);

	/**
	 * zwraca rozmiar tablicy
	 */
	int getSize();

	/**
	 * zwraca liczba otrzymanych odpowiedzi
	 */
	int numberOfResponses();

	/**
	 *zwraca element o indeksie n w tablicy responses
	 */
	int getElem(int n);
	
	void print();
	void clear();
};