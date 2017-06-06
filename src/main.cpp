#include "mpi.h" //mpi

#include <thread> //threads
#include <iostream> //output
#include <unistd.h> //sleep

#include "../include/Process.h"
#include "../include/constants.h"

using namespace std;

void receive(Process* process, int p, int s){

	int timestampRecv;
	MPI_Status status;

	while(true){

		MPI_Recv(&timestampRecv, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		//cout<<process->getRank()<<":Odebrano od "<<status.MPI_SOURCE<<" tag "<< status.MPI_TAG<<" my ts: "<<process->getTimestamp()<<" ts " <<timestampRecv<<endl;
		
		switch(status.MPI_TAG){
			case REQUEST_P:
				process->handleRequestP(timestampRecv, status.MPI_SOURCE);
				break;
			case REQUEST_S:
				process->handleRequestS(timestampRecv, status.MPI_SOURCE);
				break;
			case ALLOW_P:
				process->handleAllowP(timestampRecv, status.MPI_SOURCE, ALLOW_P, p);
				break;
			case TAKEN_P:
				process->handleAllowP(timestampRecv, status.MPI_SOURCE, TAKEN_P, p);
				break;
			case RELEASED_P:
				process->handleReleaseP(status.MPI_SOURCE, p);
				break;
			case ALLOW_S:
				process->handleAllowS(timestampRecv, status.MPI_SOURCE, ALLOW_S, s);
				break;
			case TAKEN_S:
				process->handleAllowS(timestampRecv, status.MPI_SOURCE, TAKEN_S, s);
				break;
			case RELEASED_S:
				process->handleReleaseS(status.MPI_SOURCE, s);
				break;
		}
		process->setTimestamp(max(process->getTimestamp(), timestampRecv));
		
	}
}
void sendToAll(Process* process, int n, TAG tag){

	process->timestampIncrement();

	for(int i = 0; i < n; i++){

		if(i == process->getRank())continue;
		MPI_Send(process->getTimestampRef(), 1, MPI_INT, i, tag, MPI_COMM_WORLD);
	}
	
}
void prepareLanding(Process* process, int n, int p, int s){
	
	process->setState_P(WANTED_P);
	sendToAll(process, n, REQUEST_P);
	while(process->getState_P() != HELD_P){

	}
	process->setState_S(WANTED_S);
	sendToAll(process, n, REQUEST_S);
	while(process->getState_S() != HELD_S){

	}

}
void land(){

	sleep(10);

}

void releaseLandingSpot(Process* process){

	process->setState_S(NOT_INTERESTED);

	process->sendToAllInQueueS(RELEASED_S);

}
void stop(){

	sleep(10);

}

void prepareStarting(Process* process,int n, int s){

	process->setState_S(WANTED_S);
	sendToAll(process, n, REQUEST_S);
	while(process->getState_S() != HELD_S){

	}

}

void start(){

	sleep(10);

}

void releaseBoth(Process* process){

	process->setState_P(NOT_INTERESTED);

	process->sendToAllInQueueP(RELEASED_P);


	process->setState_S(NOT_INTERESTED);

	process->sendToAllInQueueS(RELEASED_S);


}
void fly(){

	sleep(10);

}
int main( int argc, char **argv )
{
	if(argc != 4){
		cout << "Provide 3 parameters: n, p, s" << endl;
		return 1;
	}

	int n = atoi(argv[1]);
	int p = atoi(argv[2]);
	int s = atoi(argv[3]);
	int rank;

	int provided;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

	MPI_Comm_rank( MPI_COMM_WORLD, &rank);

	Process process(rank, n);

	thread(receive, &process,p,s).detach();

		while(true){

			prepareLanding(&process,n,p,s);

			land();

			releaseLandingSpot(&process);

			stop();

			prepareStarting(&process,n, s);

			start();

			releaseBoth(&process);

			fly();

		}
	MPI_Finalize();
	return 0;
}
