#include "../include/ThreadSafeVector.h"

void ThreadSafeVector::push(int elem){

	mut.lock();
	vec.push_back(elem);
	mut.unlock();

}

void ThreadSafeVector::sendToAllInQueue(int timestamp, int tag){

	mut.lock();

	for_each (vec.begin(), vec.end(), [&](int i){
		MPI_Send(&timestamp, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
	});

	vec.clear();
	
	mut.unlock();

}
int ThreadSafeVector::getSize(){
	return vec.size();
}

int ThreadSafeVector::getElem(int x){

	if(x>=0 && x<vec.size())
		return vec[x];
}

void ThreadSafeVector::clear(){
	vec.clear();
}