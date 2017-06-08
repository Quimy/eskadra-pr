#include "../include/Process.h"

void Process::handleRequestP(int timestampRecv, int from){

	mut.lock();

	TAG tag;
	if(isProcessInterestedInP(timestampRecv,from)){
		tag = TAKEN_P;
		waitReqP.push(from);
	}else{
		tag = ALLOW_P;
	}

	MPI_Send(&timestamp, 1, MPI_INT, from, tag, MPI_COMM_WORLD);

	mut.unlock();

}
void Process::handleRequestS(int timestampRecv, int from){

	mut.lock();

	TAG tag;	
	if(isProcessInterestedInS(timestampRecv,from)){
		tag = TAKEN_S;
		waitReqS.push(from);
	}else {
		tag = ALLOW_S;
	}
	MPI_Send(&timestamp, 1, MPI_INT, from, tag, MPI_COMM_WORLD);
	
	mut.unlock();
}
void Process::handleAllowP(int timestampRecv, int from, TAG tag, int p){

	mut.lock();
		if(state_P == WANTED_P){ //przetwórz tylko jeśli proces chciał wejść do sekcji
			responses.add(from, tag);
			if(responses.numberOfResponses() == (numberOfProcesses-1)){
				int nrOfTaken = responses.getNumberOfTag(TAKEN_P);
				if(nrOfTaken == p){
					state_P = CHOSEN_P;

				}else if(nrOfTaken < p){
					state_P = HELD_P;
					cv.notify_one();
					responses.clear();
				}
			}
		}
	mut.unlock();
}
void Process::handleAllowS(int timestampRecv, int from, TAG tag, int s){

	mut.lock();
		if(state_S == WANTED_S){ //przetwórz tylko jeśli proces chciał wejść do sekcji
			responses.add(from, tag);
			if(responses.numberOfResponses() == (numberOfProcesses-1)){
				int nrOfTaken = responses.getNumberOfTag(TAKEN_S);
				if(nrOfTaken == s){
					state_S = CHOSEN_S;
				}else if(nrOfTaken < s){
					state_S = HELD_S;
					responses.clear();
					cv.notify_one();
				}
			}
		}

	
	mut.unlock();
}
void Process::handleReleaseBoth(int from,int p, int s){

	mut.lock();

	if(responses.getElem(from) == TAKEN_P){ //jeśli poprzednia wiadomość była TAKEN_*
		
		if(state_P == CHOSEN_P){
			state_P = HELD_P;
		}else{
			responses.add(from, ALLOW_P);
			if(responses.numberOfResponses() == (numberOfProcesses-1)){
				int nrOfTaken = responses.getNumberOfTag(TAKEN_P);
				state_P = nrOfTaken == p ? CHOSEN_P : nrOfTaken < p ? HELD_P : state_P;
			}
		}
	}else if(responses.getElem(from) == TAKEN_S){
		if(state_S == CHOSEN_S){
			state_S = HELD_S;
		}else{
			responses.add(from, ALLOW_S);
			if(responses.numberOfResponses() == (numberOfProcesses-1)){
				int nrOfTaken = responses.getNumberOfTag(TAKEN_S);
				state_S = nrOfTaken == s ? CHOSEN_S : nrOfTaken < s ? HELD_S : state_S;
			}
		}
	}
	if(state_P == HELD_P || state_S == HELD_S){
		cv.notify_one();
		responses.clear();
	}
	mut.unlock();
}

void Process::handleReleaseS(int from, int s){

	mut.lock();
	if(responses.getElem(from) == TAKEN_S){
		if(state_S == CHOSEN_S){
			state_S = HELD_S;
		}else{
			responses.add(from, ALLOW_S);
			if(responses.numberOfResponses() == (numberOfProcesses-1)){
				int nrOfTaken = responses.getNumberOfTag(TAKEN_S);
				state_S = nrOfTaken == s ? CHOSEN_S : nrOfTaken < s ? HELD_S : state_S;
			}
		}
	}

	if(state_S == HELD_S){
		cv.notify_one();
		responses.clear();
	}
	
	mut.unlock();
}

void Process::setState_P(STATE s){
	mut.lock();
	state_P = s;
	mut.unlock();
}

void Process::setState_S(STATE s){

	mut.lock();
	state_S = s;
	mut.unlock();

}
int Process::getState_P(){

	return state_P;

}
int Process::getState_S(){

	return state_S;

}
int Process::getRank(){
	return rank;
}
int Process::getTimestamp(){
	return timestamp;
}
int* Process::getTimestampRef(){
	return &timestamp;
}
int Process::setTimestamp(int ts){
	timestamp = ts;
}
void Process::timestampIncrement(){
	mut.lock();
	timestamp++;
	mut.unlock();
}
bool Process::compareTimestamps(int ts_j, int j){
	return timestamp < ts_j ? true : timestamp == ts_j && rank < j ? true : false;
}

bool Process::isProcessInterestedInP(int timestampRecv, int from){
	return state_P == HELD_P || (((state_P == WANTED_P) ||(state_P == CHOSEN_P))  && compareTimestamps(timestampRecv, from));
}
bool Process::isProcessInterestedInS(int timestampRecv, int from){
	return state_S == HELD_S || (((state_S == WANTED_S) || (state_S == CHOSEN_S))&& compareTimestamps(timestampRecv, from));
}
void Process::sendToAllInQueueBoth(int tag){
	mut.lock();
	waitReqP.sendToAllInQueue(timestamp, tag);
	waitReqP.clear();
	waitReqS.sendToAllInQueue(timestamp, tag);
	waitReqS.clear();
	mut.unlock();
}

void Process::sendToAllInQueueS(int tag){
	mut.lock();
	waitReqS.sendToAllInQueue(timestamp, tag);
	waitReqS.clear();
	mut.unlock();
}
void Process::waitForP(){

    unique_lock<mutex> lk(m);
    cv.wait(lk, [this]{return state_P == HELD_P;});
	lk.unlock();
}

void Process::waitForS(){

    unique_lock<mutex> lk(m);
    cv.wait(lk, [this]{return state_S == HELD_S;});
	lk.unlock();
}