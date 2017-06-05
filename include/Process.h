#pragma once

#include <mutex> //mutex
#include <iostream> //output
#include "constants.h"
#include "ThreadSafeVector.h"
#include "Responses.h"

using namespace std;
/**
 * Klasa stworząca procesy i obsługuje ich
 */
class Process{

	//status procesu do zasobu P
	int state_P;
	//status procesu do zasobu S
	int state_S;
	//timestamp znacznik czasowy procesu
	int timestamp;
	//kolejka oczekujących na zasób P
	ThreadSafeVector waitReqP;
	//kolejka oczekujących na zasób S
	ThreadSafeVector waitReqS;
	//id procesu
	int rank;
	//liczba procesów
	int numberOfProcesses;
	//odpowiedzi otrzymane od innych procesów
	Responses responses;

	mutex mut;
	/**
	 *zwraca true w przypadku gdy moj znacznik czasowy jest mniejszy lub kiedy znaczniku są równe a mój id jest
	 * mniejszy
	 */
	bool compareTimestamps(int ts_j,int j);

public:
	Process(int r, int n): rank{r}, numberOfProcesses{n}, state_S{NOT_INTERESTED}, state_P{NOT_INTERESTED}, timestamp{0}, waitReqP{}, waitReqS{}, responses(n){};

	void setState_P(STATE s);
	void setState_S(STATE s);
	int getState_P();
	int getState_S();
	int getRank();
	int* getTimestampRef();
	int getTimestamp();
	int setTimestamp(int ts);

	void timestampIncrement();

	/**
	 * wysyłanie do wszystkich procesów, które mam w kolejce P\S wiadomość o tagu tag
	 */
	void sendToAllInQueueP(int tag);
	void sendToAllInQueueS(int tag);

	/**
	 *zwraca true w przypadku, gdy proces ma przydzielony zasob P\S, lub gdy proces ma  żądanie do zasobu i ma wiekszy
	 *priorytet od drugiego procesu
	 *timestampRecv znacznik czasowy żądający proces
	 *from id żądający proces
	 */
	bool isProcessInterestedInP(int timestampRecv, int from);
	bool isProcessInterestedInS(int timestampRecv, int from);

	/**
	 * obsługuje żądanie dostawanych od innych procesów, w przypadku gdy ten proces wysyłał żądanie i ma wiekszy priorytet
	 * to zmienia swój stan na TAKEN i dodaje drugi proces żądający do swojej kolejki, w przeciwnym przypadku wysyła
	 * pozwolenie
	 */
	void handleRequestP(int timestampRecv, int from);
	void handleRequestS(int timestampRecv, int from);

	/**
	 * obsługuje komunikaty ALLOW_*
	 *
	 */
	void handleAllowP(int timestampRecv, int from, TAG tag, int p);
	void handleAllowS(int timestampRecv, int from, TAG tag, int s);

	/**
	 *obsługuje komunikaty Release_*
	 *
	 */
	void handleReleaseP(int from,int p);
	void handleReleaseS(int from, int s);
};